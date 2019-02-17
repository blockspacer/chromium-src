// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/bind.h"
#include "base/logging.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/shared_memory.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/strings/string_piece.h"
#include "chrome/browser/chromeos/diagnosticsd/mojo_utils.h"
#include "chrome/services/diagnosticsd/public/mojom/diagnosticsd.mojom.h"
#include "net/base/net_errors.h"
#include "net/http/http_status_code.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/cpp/weak_wrapper_shared_url_loader_factory.h"
#include "services/network/test/test_url_loader_factory.h"
#include "services/network/test/test_utils.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

#include "chrome/browser/chromeos/diagnosticsd/diagnosticsd_web_request_service.h"

namespace chromeos {

namespace {

constexpr char kFakeUrl[] = "https://fake.url.com";
constexpr char kLocalhostUrl[] = "https://localhost:8000/";
constexpr char kIncorrectHttpUrl[] = "http://fake.url.com";
constexpr char kInvalidUrl[] = "\0\0\1invalid_url";
constexpr char kFakeRequestBody[] = "Fake\0Request\11Body\n\0";
constexpr char kFakeResponseBody[] = "Fake\11Response\0\0\nBody";

// Tests for the DiagnosticsdWebRequestService class.
class DiagnosticsdWebRequestServiceTest : public testing::Test {
 protected:
  struct WebRequestResult {
    WebRequestResult(diagnosticsd::mojom::DiagnosticsdWebRequestStatus status,
                     int http_status,
                     mojo::ScopedHandle response_body_handle)
        : status(status), http_status(http_status) {
      if (!response_body_handle.is_valid()) {
        response_body = "";
        return;
      }
      std::unique_ptr<base::SharedMemory> shared_memory;
      response_body = std::string(GetStringPieceFromMojoHandle(
          std::move(response_body_handle), &shared_memory));
      if (!shared_memory) {
        response_body = "";
        return;
      }
    }

    diagnosticsd::mojom::DiagnosticsdWebRequestStatus status;
    int http_status;
    std::string response_body;
  };
  DiagnosticsdWebRequestServiceTest() {
    web_request_service_ = std::make_unique<DiagnosticsdWebRequestService>(
        base::MakeRefCounted<network::WeakWrapperSharedURLLoaderFactory>(
            &test_url_loader_factory_));
  }

  ~DiagnosticsdWebRequestServiceTest() override {}

  void TearDown() override { test_url_loader_factory_.ClearResponses(); }

  // Start new web request with the next parameters:
  // * web request parameters:
  //   * |http_method|
  //   * |url|
  //   * |request_body|
  // * |request_result| - once the request is complete, this structure contains
  //                      web response.
  // * |run_loop| - the current run loop.
  void StartWebRequest(
      diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod http_method,
      const std::string& url,
      const std::string& request_body,
      std::unique_ptr<WebRequestResult>* request_result,
      base::RunLoop* run_loop) {
    web_request_service()->PerformRequest(
        http_method, GURL(url), std::vector<base::StringPiece>() /* headers */,
        request_body,
        base::BindOnce(&DiagnosticsdWebRequestServiceTest::OnRequestComplete,
                       base::Unretained(this), request_result,
                       run_loop->QuitClosure()));
  }

  // Injects the web response for |url|.
  void InjectNetworkResponse(
      const std::string& url,
      std::unique_ptr<net::HttpStatusCode> response_status,
      net::Error net_error,
      const std::string& response_body) {
    network::ResourceResponseHead response_head;
    if (response_status)
      response_head = network::CreateResourceResponseHead(*response_status);
    test_url_loader_factory_.AddResponse(
        GURL(url), response_head, response_body,
        network::URLLoaderCompletionStatus(net_error));
  }

  void DestroyService() { web_request_service_.reset(); }

  DiagnosticsdWebRequestService* web_request_service() {
    return web_request_service_.get();
  }

 private:
  void OnRequestComplete(
      std::unique_ptr<WebRequestResult>* request_result,
      base::RepeatingClosure callback,
      diagnosticsd::mojom::DiagnosticsdWebRequestStatus status,
      int http_status,
      mojo::ScopedHandle response_body) {
    auto response = std::make_unique<WebRequestResult>(
        status, http_status, std::move(response_body));
    *request_result = std::move(response);
    std::move(callback).Run();
  }

  std::unique_ptr<DiagnosticsdWebRequestService> web_request_service_;
  network::TestURLLoaderFactory test_url_loader_factory_;
  base::MessageLoop message_loop_;
};

}  // namespace

TEST_F(DiagnosticsdWebRequestServiceTest, HttpMethodGetNonEmptyBody) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kGet,
                  kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
  // The test fails with a network error on the same thread.
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, HttpMethodHeadEmptyBody) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kHead,
                  kFakeUrl, "" /* request_body */, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(kFakeUrl,
                        std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                        net::OK, "" /* response_body */);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kOk);
  EXPECT_EQ(request_result->http_status, net::HTTP_OK);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, HttpMethodPostNonEmptyBody) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPost,
                  kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(kFakeUrl,
                        std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                        net::OK, kFakeResponseBody);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kOk);
  EXPECT_EQ(request_result->http_status, net::HTTP_OK);
  EXPECT_EQ(request_result->response_body, kFakeResponseBody);
}

TEST_F(DiagnosticsdWebRequestServiceTest, HttpMethodPutEmptyBody) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPut,
                  kFakeUrl, "" /* request_body */, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(kFakeUrl,
                        std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                        net::OK, "" /* response_body */);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kOk);
  EXPECT_EQ(request_result->http_status, net::HTTP_OK);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, ResponseCodeParsingError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPost,
                  kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(kFakeUrl, nullptr /* response_status */, net::OK,
                        "" /* response_body */);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kHttpError);
  EXPECT_EQ(request_result->http_status, net::HTTP_INTERNAL_SERVER_ERROR);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, ResponseCodeParsingErrorNetError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kGet,
                  kFakeUrl, "" /* request_body */, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(kFakeUrl, nullptr /* response_status */,
                        net::ERR_CERT_INVALID, kFakeResponseBody);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, HttpStatusOkNetError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPost,
                  kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(kFakeUrl,
                        std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                        net::ERR_CERT_INVALID, kFakeResponseBody);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, HttpErrorNetError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPost,
                  kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(
      kFakeUrl, std::make_unique<net::HttpStatusCode>(net::HTTP_BAD_REQUEST),
      net::ERR_CERT_INVALID, kFakeResponseBody);
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, DestroyServiceWithActiveWebRequest) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPost,
                  kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
  InjectNetworkResponse(kFakeUrl,
                        std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                        net::OK, kFakeResponseBody);
  EXPECT_FALSE(request_result);
  DestroyService();
  run_loop.Run();

  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, TwoWebRequests) {
  constexpr int kNumberOfRequests = 2;

  std::unique_ptr<WebRequestResult> request_results[kNumberOfRequests];
  base::RunLoop run_loops[kNumberOfRequests];

  for (int i = 0; i < kNumberOfRequests; ++i) {
    StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPut,
                    kFakeUrl, kFakeRequestBody, &request_results[i],
                    &run_loops[i]);
    InjectNetworkResponse(kFakeUrl,
                          std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                          net::OK, kFakeResponseBody);
    EXPECT_FALSE(request_results[i]);
  }

  // The first request is active and the second is in the queue.
  EXPECT_EQ(kNumberOfRequests - 1,
            web_request_service()->request_queue_size_for_testing());
  for (auto& run_loop : run_loops) {
    run_loop.Run();
  }
  EXPECT_EQ(0, web_request_service()->request_queue_size_for_testing());

  for (const auto& request_result : request_results) {
    ASSERT_TRUE(request_result);
    EXPECT_EQ(request_result->status,
              diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kOk);
    EXPECT_EQ(request_result->http_status, net::HTTP_OK);
    EXPECT_EQ(request_result->response_body, kFakeResponseBody);
  }
}

TEST_F(DiagnosticsdWebRequestServiceTest, RequestQueueOverflow) {
  // The number of requests in the queue is kDiagnosticsdRequestQueueMaxSize.
  // One is already pending.
  std::unique_ptr<WebRequestResult>
      request_results[kDiagnosticsdWebRequestQueueMaxSize + 1];
  base::RunLoop run_loops[kDiagnosticsdWebRequestQueueMaxSize + 1];

  for (int i = 0; i < kDiagnosticsdWebRequestQueueMaxSize + 1; ++i) {
    StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPut,
                    kFakeUrl, kFakeRequestBody, &request_results[i],
                    &run_loops[i]);
    InjectNetworkResponse(kFakeUrl,
                          std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                          net::OK, kFakeResponseBody);
    EXPECT_FALSE(request_results[i]);
  }
  EXPECT_EQ(kDiagnosticsdWebRequestQueueMaxSize,
            web_request_service()->request_queue_size_for_testing());

  // Try to add one more. Should fail with kNetworkError.
  {
    std::unique_ptr<WebRequestResult> request_result;
    base::RunLoop run_loop;
    StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kPut,
                    kFakeUrl, kFakeRequestBody, &request_result, &run_loop);
    InjectNetworkResponse(kFakeUrl,
                          std::make_unique<net::HttpStatusCode>(net::HTTP_OK),
                          net::OK, kFakeResponseBody);
    // The test fails with a network error on the same thread.
    EXPECT_TRUE(request_result);
    EXPECT_EQ(request_result->status,
              diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
    EXPECT_EQ(request_result->http_status, 0);
    EXPECT_EQ(request_result->response_body, "");
  }
  for (auto& run_loop : run_loops) {
    run_loop.Run();
  }
  for (const auto& request_result : request_results) {
    EXPECT_TRUE(request_result);
    EXPECT_EQ(request_result->status,
              diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kOk);
    EXPECT_EQ(request_result->http_status, net::HTTP_OK);
    EXPECT_EQ(request_result->response_body, kFakeResponseBody);
  }
}

TEST_F(DiagnosticsdWebRequestServiceTest, ResponseBodyMaxSize) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kHead,
                  kFakeUrl, "" /* request_body */, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(
      kFakeUrl, std::make_unique<net::HttpStatusCode>(net::HTTP_OK), net::OK,
      std::string(kDiagnosticsdWebResponseMaxSizeInBytes, 'A'));
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kOk);
  EXPECT_EQ(request_result->http_status, net::HTTP_OK);
  EXPECT_EQ(request_result->response_body,
            std::string(kDiagnosticsdWebResponseMaxSizeInBytes, 'A'));
}

TEST_F(DiagnosticsdWebRequestServiceTest, ResponseBodyOverflow) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kHead,
                  kFakeUrl, "" /* request_body */, &request_result, &run_loop);
  EXPECT_FALSE(request_result);
  InjectNetworkResponse(
      kFakeUrl, std::make_unique<net::HttpStatusCode>(net::HTTP_OK), net::OK,
      std::string(kDiagnosticsdWebResponseMaxSizeInBytes + 1, 'A'));
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, LocalhostRequestNetworkError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kHead,
                  kLocalhostUrl, "" /* request_body */, &request_result,
                  &run_loop);
  // The test fails with a network error on the same thread.
  run_loop.Run();
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, HttpUrlNetworkError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kHead,
                  kIncorrectHttpUrl, "" /* request_body */, &request_result,
                  &run_loop);
  // The test fails with a network error on the same thread.
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}

TEST_F(DiagnosticsdWebRequestServiceTest, InvalidUrlNetworkError) {
  std::unique_ptr<WebRequestResult> request_result;
  base::RunLoop run_loop;

  StartWebRequest(diagnosticsd::mojom::DiagnosticsdWebRequestHttpMethod::kHead,
                  kInvalidUrl, "" /* request_body */, &request_result,
                  &run_loop);
  // The test fails with a network error on the same thread.
  ASSERT_TRUE(request_result);
  EXPECT_EQ(request_result->status,
            diagnosticsd::mojom::DiagnosticsdWebRequestStatus::kNetworkError);
  EXPECT_EQ(request_result->http_status, 0);
  EXPECT_EQ(request_result->response_body, "");
}
}  // namespace chromeos
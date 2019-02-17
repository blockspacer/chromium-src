// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/policy/browser_dm_token_storage_mac.h"

#include <iostream>

#include "base/base64url.h"
#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/files/file_util.h"
#include "base/mac/foundation_util.h"
#include "base/macros.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/sha1.h"
#include "base/strings/utf_string_conversions.h"
#include "base/test/scoped_path_override.h"
#include "chrome/common/chrome_paths.h"
#include "content/public/test/test_browser_thread_bundle.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using ::testing::IsEmpty;

namespace policy {

namespace {

const char kDmTokenBaseDir[] =
    FILE_PATH_LITERAL("Google/Chrome Cloud Enrollment");

constexpr char kDMToken[] = "fake-dm-token";

}  // namespace

class BrowserDMTokenStorageMacTest : public testing::Test {
 private:
  content::TestBrowserThreadBundle thread_bundle_;
};

TEST_F(BrowserDMTokenStorageMacTest, InitClientId) {
  BrowserDMTokenStorageMac storage;
  EXPECT_FALSE(storage.InitClientId().empty());
}

class TestStoreDMTokenDelegate {
 public:
  TestStoreDMTokenDelegate() : called_(false), success_(true) {}
  ~TestStoreDMTokenDelegate() {}

  void OnDMTokenStored(bool success) {
    run_loop_.Quit();
    called_ = true;
    success_ = success;
  }

  bool WasCalled() {
    bool was_called = called_;
    called_ = false;
    return was_called;
  }

  bool success() { return success_; }

  void Wait() { run_loop_.Run(); }

 private:
  bool called_;
  bool success_;
  base::RunLoop run_loop_;
};

TEST_F(BrowserDMTokenStorageMacTest, SaveDMToken) {
  std::unique_ptr<base::ScopedPathOverride> path_override;
  base::ScopedTempDir fake_app_data_dir;

  ASSERT_TRUE(fake_app_data_dir.CreateUniqueTempDir());
  path_override.reset(new base::ScopedPathOverride(
      base::DIR_APP_DATA, fake_app_data_dir.GetPath()));

  TestStoreDMTokenDelegate delegate;
  BrowserDMTokenStorageMac storage;
  storage.StoreDMToken(
      kDMToken, base::BindOnce(&TestStoreDMTokenDelegate::OnDMTokenStored,
                               base::Unretained(&delegate)));

  delegate.Wait();
  ASSERT_TRUE(delegate.success());

  base::FilePath app_data_dir_path;
  ASSERT_TRUE(base::PathService::Get(base::DIR_APP_DATA, &app_data_dir_path));
  base::FilePath dm_token_dir_path = app_data_dir_path.Append(kDmTokenBaseDir);

  std::string filename;
  base::Base64UrlEncode(base::SHA1HashString(storage.InitClientId()),
                        base::Base64UrlEncodePolicy::OMIT_PADDING, &filename);

  base::FilePath dm_token_file_path = dm_token_dir_path.Append(filename);

  std::string dm_token;
  ASSERT_TRUE(base::ReadFileToString(dm_token_file_path, &dm_token));
  EXPECT_EQ(kDMToken, dm_token);
}

TEST_F(BrowserDMTokenStorageMacTest, InitDMTokenWithoutDirectory) {
  std::unique_ptr<base::ScopedPathOverride> path_override;
  base::ScopedTempDir fake_app_data_dir;

  ASSERT_TRUE(fake_app_data_dir.CreateUniqueTempDir());
  path_override.reset(new base::ScopedPathOverride(
      base::DIR_APP_DATA, fake_app_data_dir.GetPath()));

  TestStoreDMTokenDelegate delegate;
  BrowserDMTokenStorageMac storage;

  base::FilePath dm_token_dir_path =
      fake_app_data_dir.GetPath().Append(kDmTokenBaseDir);

  EXPECT_EQ(std::string(), storage.InitDMToken());
  EXPECT_FALSE(base::PathExists(dm_token_dir_path));
}

class BrowserDMTokenStorageMacCleanupTest : public testing::Test {
 protected:
  BrowserDMTokenStorageMacCleanupTest() = default;
  ~BrowserDMTokenStorageMacCleanupTest() override = default;

  void SetUp() override {
    ASSERT_TRUE(fake_app_data_dir_.CreateUniqueTempDir());
    path_override_.reset(new base::ScopedPathOverride(
        base::DIR_APP_DATA, fake_app_data_dir_.GetPath()));

    token_dir_path_ = fake_app_data_dir_.GetPath().Append(kDmTokenBaseDir);
  }

  base::ScopedTempDir fake_app_data_dir_;
  base::FilePath token_dir_path_;
  BrowserDMTokenStorageMac storage_;
  std::unique_ptr<base::ScopedPathOverride> path_override_;

 private:
  DISALLOW_COPY_AND_ASSIGN(BrowserDMTokenStorageMacCleanupTest);
};

TEST_F(BrowserDMTokenStorageMacCleanupTest, Success) {
  ASSERT_TRUE(base::CreateDirectory(token_dir_path_));

  ASSERT_TRUE(base::DirectoryExists(token_dir_path_));

  storage_.DeletePolicyDirectory();

  EXPECT_FALSE(base::PathExists(token_dir_path_));
  EXPECT_TRUE(base::DirectoryExists(token_dir_path_.DirName()));
}

TEST_F(BrowserDMTokenStorageMacCleanupTest, TokenDirNotEmpty) {
  ASSERT_TRUE(base::CreateDirectory(token_dir_path_));

  ASSERT_TRUE(base::DirectoryExists(token_dir_path_));

  base::FilePath tmp_file;
  ASSERT_TRUE(base::CreateTemporaryFileInDir(token_dir_path_, &tmp_file));

  storage_.DeletePolicyDirectory();

  EXPECT_TRUE(base::DirectoryExists(token_dir_path_));
}

TEST_F(BrowserDMTokenStorageMacCleanupTest, TokenDirNotExist) {
  ASSERT_FALSE(base::DirectoryExists(token_dir_path_));

  storage_.DeletePolicyDirectory();

  EXPECT_FALSE(base::PathExists(token_dir_path_));
  EXPECT_FALSE(base::PathExists(token_dir_path_.DirName()));
}

TEST_F(BrowserDMTokenStorageMacCleanupTest, TokenDirIsNotDir) {
  ASSERT_TRUE(base::CreateDirectory(token_dir_path_.DirName()));
  ASSERT_TRUE(base::DirectoryExists(token_dir_path_.DirName()));

  ASSERT_TRUE(base::CloseFile(base::OpenFile(token_dir_path_, "w")));

  ASSERT_TRUE(base::PathExists(token_dir_path_));

  storage_.DeletePolicyDirectory();

  EXPECT_TRUE(base::PathExists(token_dir_path_));
}

}  // namespace policy
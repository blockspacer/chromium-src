// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_APPCACHE_APPCACHE_BACKEND_IMPL_H_
#define CONTENT_BROWSER_APPCACHE_APPCACHE_BACKEND_IMPL_H_

#include <stdint.h>
#include <memory>

#include "content/browser/appcache/appcache_frontend_proxy.h"
#include "content/browser/appcache/appcache_host.h"
#include "content/common/content_export.h"
#include "third_party/blink/public/mojom/appcache/appcache.mojom.h"

namespace content {

class AppCacheServiceImpl;

class CONTENT_EXPORT AppCacheBackendImpl
    : public blink::mojom::AppCacheBackend {
 public:
  AppCacheBackendImpl(AppCacheServiceImpl* service, int process_id);
  ~AppCacheBackendImpl() override;

  int process_id() const { return process_id_; }

  // blink::mojom::AppCacheBackend
  void RegisterHost(blink::mojom::AppCacheHostRequest host_request,
                    int32_t host_id,
                    int32_t render_frame_id) override;
  void UnregisterHost(int32_t host_id);

  // Returns a pointer to a registered host. The backend retains ownership.
  AppCacheHost* GetHost(int host_id) {
    auto it = hosts_.find(host_id);
    return (it != hosts_.end()) ? (it->second.get()) : nullptr;
  }

  using HostMap = std::unordered_map<int, std::unique_ptr<AppCacheHost>>;
  const HostMap& hosts() { return hosts_; }

  void set_frontend_for_testing(blink::mojom::AppCacheFrontend* frontend) {
    frontend_ = frontend;
  }

 private:
  // Raw pointer is safe because instances of this class are owned by
  // |service_|.
  AppCacheServiceImpl* service_;
  AppCacheFrontendProxy frontend_proxy_;
  blink::mojom::AppCacheFrontend* frontend_;
  int process_id_;
  HostMap hosts_;

  DISALLOW_COPY_AND_ASSIGN(AppCacheBackendImpl);
};

}  // namespace

#endif  // CONTENT_BROWSER_APPCACHE_APPCACHE_BACKEND_IMPL_H_

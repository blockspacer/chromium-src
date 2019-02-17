// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/media/android/cdm/media_drm_storage_factory.h"

#include <utility>

#include "base/bind.h"
#include "base/callback.h"
#include "base/logging.h"
#include "chrome/browser/media/android/cdm/media_drm_origin_id_manager.h"
#include "chrome/browser/media/android/cdm/media_drm_origin_id_manager_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/cdm/browser/media_drm_storage_impl.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"
#include "media/base/android/media_drm_bridge.h"
#include "mojo/public/cpp/bindings/strong_binding.h"

namespace {

void CreateOriginId(Profile* profile,
                    MediaDrmOriginIdManager::ProvisionedOriginIdCB callback) {
  // Only need to origin IDs if MediaDrm supports it.
  DCHECK(media::MediaDrmBridge::IsPerOriginProvisioningSupported());

  auto* origin_id_manager =
      MediaDrmOriginIdManagerFactory::GetForProfile(profile);
  if (!origin_id_manager) {
    std::move(callback).Run(false, base::UnguessableToken());
    return;
  }

  origin_id_manager->GetOriginId(std::move(callback));
}

}  // namespace

void CreateMediaDrmStorage(content::RenderFrameHost* render_frame_host,
                           media::mojom::MediaDrmStorageRequest request) {
  DVLOG(1) << __func__;
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  DCHECK(render_frame_host);

  content::WebContents* web_contents =
      content::WebContents::FromRenderFrameHost(render_frame_host);
  DCHECK(web_contents) << "WebContents not available.";

  content::BrowserContext* browser_context = web_contents->GetBrowserContext();
  DCHECK(browser_context) << "BrowserContext not available.";

  Profile* profile = Profile::FromBrowserContext(browser_context);
  DCHECK(profile) << "Profile not available.";

  PrefService* pref_service = profile->GetPrefs();
  DCHECK(pref_service) << "PrefService not available.";

  if (render_frame_host->GetLastCommittedOrigin().opaque()) {
    DVLOG(1) << __func__ << ": Unique origin.";
    return;
  }

  // The object will be deleted on connection error, or when the frame navigates
  // away. See FrameServiceBase for details.
  new cdm::MediaDrmStorageImpl(render_frame_host, pref_service,
                               base::BindRepeating(&CreateOriginId, profile),
                               std::move(request));
}
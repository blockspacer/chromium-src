// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/services/patch/public/cpp/manifest.h"

#include "base/no_destructor.h"
#include "components/services/patch/public/interfaces/constants.mojom.h"
#include "components/services/patch/public/interfaces/file_patcher.mojom.h"
#include "services/service_manager/public/cpp/manifest_builder.h"

namespace patch {

const service_manager::Manifest& GetManifest() {
  static base::NoDestructor<service_manager::Manifest> manifest{
      service_manager::ManifestBuilder()
          .WithServiceName(mojom::kServiceName)
          .WithDisplayName("Patch Service")
          .WithOptions(service_manager::ManifestOptionsBuilder()
                           .WithSandboxType("utility")
                           .WithInstanceSharingPolicy(
                               service_manager::Manifest::
                                   InstanceSharingPolicy::kSharedAcrossGroups)
                           .Build())
          .ExposeCapability(
              "patch_file",
              service_manager::Manifest::InterfaceList<mojom::FilePatcher>())

          .Build()};
  return *manifest;
}

}  // namespace patch

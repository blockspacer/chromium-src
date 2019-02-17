// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_PUBLIC_CPP_IMMERSIVE_IMMERSIVE_FULLSCREEN_CONTROLLER_TEST_API_H_
#define ASH_PUBLIC_CPP_IMMERSIVE_IMMERSIVE_FULLSCREEN_CONTROLLER_TEST_API_H_

#include "base/macros.h"

namespace ash {

class ImmersiveFullscreenController;

// Use by tests to access private state of ImmersiveFullscreenController.
class ImmersiveFullscreenControllerTestApi {
 public:
  explicit ImmersiveFullscreenControllerTestApi(
      ImmersiveFullscreenController* controller);
  ~ImmersiveFullscreenControllerTestApi();

  // Disables animations for any ImmersiveFullscreenControllers created while
  // GlobalAnimationDisabler exists.
  class GlobalAnimationDisabler {
   public:
    GlobalAnimationDisabler();
    ~GlobalAnimationDisabler();

   private:
    DISALLOW_COPY_AND_ASSIGN(GlobalAnimationDisabler);
  };

  // Disables animations and moves the mouse so that it is not over the
  // top-of-window views for the sake of testing. |wait_for_mouse_move| should
  // normally be true to wait for the generated mouse events to go through under
  // mash. It is provided for tests that call SetupForTest under the scope of
  // TestMockTimeTaskRunner::ScopedContext that does not allow RunLoop::Run().
  void SetupForTest(bool wait_for_mouse_event = true);

  bool IsTopEdgeHoverTimerRunning() const;

 private:
  ImmersiveFullscreenController* immersive_fullscreen_controller_;

  DISALLOW_COPY_AND_ASSIGN(ImmersiveFullscreenControllerTestApi);
};

}  // namespace ash

#endif  // ASH_PUBLIC_CPP_IMMERSIVE_IMMERSIVE_FULLSCREEN_CONTROLLER_TEST_API_H_
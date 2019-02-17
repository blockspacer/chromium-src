// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/public/cpp/immersive/immersive_fullscreen_controller_test_api.h"

#include "ash/public/cpp/immersive/immersive_fullscreen_controller.h"
#include "ash/public/cpp/immersive/immersive_fullscreen_controller_delegate.h"
#include "base/run_loop.h"
#include "ui/aura/env.h"
#include "ui/aura/event_injector.h"
#include "ui/aura/window.h"
#include "ui/events/base_event_utils.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/views/widget/widget.h"

namespace {

// Update mouse location for |window|. For local window, update its aura::Env
// directly. For remote window, update aura::Env by injecting a mouse move
// event. EventInjector is used so that the Window Service side code under mash
// sees the updated mouse location as well.
void UpdateMouseLocation(aura::Window* window,
                         const gfx::Point& screen_location,
                         bool wait) {
  if (window->env()->mode() == aura::Env::Mode::LOCAL) {
    window->env()->SetLastMouseLocation(screen_location);
    return;
  }

  ui::MouseEvent event(ui::ET_MOUSE_MOVED, screen_location, screen_location,
                       ui::EventTimeForNow(), ui::EF_NONE, 0);
  if (!wait) {
    aura::EventInjector().Inject(window->GetHost(), &event);
    return;
  }

  // Ensure the mouse event goes through when |wait| is set.
  aura::EventInjector event_injector;
  base::RunLoop run_loop;
  event_injector.Inject(window->GetHost(), &event, run_loop.QuitClosure());
  run_loop.Run();
}

}  // namespace

namespace ash {

ImmersiveFullscreenControllerTestApi::ImmersiveFullscreenControllerTestApi(
    ImmersiveFullscreenController* controller)
    : immersive_fullscreen_controller_(controller) {}

ImmersiveFullscreenControllerTestApi::~ImmersiveFullscreenControllerTestApi() =
    default;

void ImmersiveFullscreenControllerTestApi::SetupForTest(
    bool wait_for_mouse_event) {
  immersive_fullscreen_controller_->animations_disabled_for_test_ = true;

  // Move the mouse off of the top-of-window views so that it does not keep the
  // top-of-window views revealed.
  std::vector<gfx::Rect> bounds_in_screen(
      immersive_fullscreen_controller_->delegate_->GetVisibleBoundsInScreen());
  DCHECK(!bounds_in_screen.empty());
  int bottommost_in_screen = bounds_in_screen[0].bottom();
  for (size_t i = 1; i < bounds_in_screen.size(); ++i) {
    if (bounds_in_screen[i].bottom() > bottommost_in_screen)
      bottommost_in_screen = bounds_in_screen[i].bottom();
  }
  gfx::Point cursor_pos(0, bottommost_in_screen + 10);
  UpdateMouseLocation(
      immersive_fullscreen_controller_->widget()->GetNativeView(), cursor_pos,
      wait_for_mouse_event);
  immersive_fullscreen_controller_->UpdateLocatedEventRevealedLock();
}

bool ImmersiveFullscreenControllerTestApi::IsTopEdgeHoverTimerRunning() const {
  return immersive_fullscreen_controller_->top_edge_hover_timer_.IsRunning();
}

ImmersiveFullscreenControllerTestApi::GlobalAnimationDisabler::
    GlobalAnimationDisabler() {
  // Nesting isn't supported.
  DCHECK(
      !ImmersiveFullscreenController::value_for_animations_disabled_for_test_);
  ImmersiveFullscreenController::value_for_animations_disabled_for_test_ = true;
}

ImmersiveFullscreenControllerTestApi::GlobalAnimationDisabler::
    ~GlobalAnimationDisabler() {
  ImmersiveFullscreenController::value_for_animations_disabled_for_test_ =
      false;
}

}  // namespace ash
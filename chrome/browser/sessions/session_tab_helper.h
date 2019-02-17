// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SESSIONS_SESSION_TAB_HELPER_H_
#define CHROME_BROWSER_SESSIONS_SESSION_TAB_HELPER_H_

#include "base/macros.h"
#include "chrome/common/buildflags.h"
#include "components/sessions/core/session_id.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "extensions/buildflags/buildflags.h"

// This class keeps the extension API's windowID up to date with the current
// window of the tab and observes navigation events.
class SessionTabHelper : public content::WebContentsObserver,
                         public content::WebContentsUserData<SessionTabHelper> {
 public:
  ~SessionTabHelper() override;

  // Returns the identifier used by session restore for this tab.
  const SessionID& session_id() const { return session_id_; }

  // Identifier of the window the tab is in.
  void SetWindowID(const SessionID& id);
  const SessionID& window_id() const { return window_id_; }

  // If the specified WebContents has a SessionTabHelper (probably because it
  // was used as the contents of a tab), returns a tab id. This value is
  // immutable for a given tab. It will be unique across Chrome within the
  // current session, but may be re-used across sessions. Returns
  // SessionID::InvalidValue() for a NULL WebContents or if the WebContents has
  // no SessionTabHelper.
  static SessionID IdForTab(const content::WebContents* tab);

  // If the specified WebContents has a SessionTabHelper (probably because it
  // was used as the contents of a tab), and has ever been attached to a Browser
  // window, returns Browser::session_id().id() for that Browser. If the tab is
  // being dragged between Browser windows, returns the old window's id value.
  // If the WebContents has a SessionTabHelper but has never been attached to a
  // Browser window, returns an id value that is different from that of any
  // Browser. Returns SessionID::InvalidValue() for a NULL WebContents or if the
  // WebContents has no SessionTabHelper.
  static SessionID IdForWindowContainingTab(const content::WebContents* tab);

  // content::WebContentsObserver:
#if BUILDFLAG(ENABLE_SESSION_SERVICE)
  void UserAgentOverrideSet(const std::string& user_agent) override;
  void NavigationEntryCommitted(
      const content::LoadCommittedDetails& load_details) override;
  void NavigationListPruned(
      const content::PrunedDetails& pruned_details) override;
  void NavigationEntriesDeleted() override;
  void NavigationEntryChanged(
      const content::EntryChangedDetails& change_details) override;
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
  void SetTabExtensionAppID(const std::string& extension_app_id);
#endif

 private:
  explicit SessionTabHelper(content::WebContents* contents);
  friend class content::WebContentsUserData<SessionTabHelper>;

  // Unique identifier of the tab for session restore. This id is only unique
  // within the current session, and is not guaranteed to be unique across
  // sessions.
  const SessionID session_id_;

  // Unique identifier of the window the tab is in.
  SessionID window_id_;

  WEB_CONTENTS_USER_DATA_KEY_DECL();

  DISALLOW_COPY_AND_ASSIGN(SessionTabHelper);
};

#endif  // CHROME_BROWSER_SESSIONS_SESSION_TAB_HELPER_H_
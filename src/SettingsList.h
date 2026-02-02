#pragma once
#include <vector>

#include "CrossPointSettings.h"
#include "KOReaderCredentialStore.h"
#include "activities/settings/CategorySettingsActivity.h"

// Returns the list of all settings, used by both the device UI and the web API.
// Categories match the device UI grouping. Settings with categories that don't
// match a device UI category (e.g. "KOReader Sync", "OPDS Browser") are
// web-only — they correspond to device sub-screens accessed via Action items.
inline std::vector<SettingInfo> getSettingsList() {
  return {
      // Display
      SettingInfo::Enum("sleepScreen", "Sleep Screen", "Display", &CrossPointSettings::sleepScreen,
                        {"Dark", "Light", "Custom", "Cover", "None"}),
      SettingInfo::Enum("sleepScreenCoverMode", "Sleep Screen Cover Mode", "Display",
                        &CrossPointSettings::sleepScreenCoverMode, {"Fit", "Crop"}),
      SettingInfo::Enum("sleepScreenCoverFilter", "Sleep Screen Cover Filter", "Display",
                        &CrossPointSettings::sleepScreenCoverFilter, {"None", "Contrast", "Inverted"}),
      SettingInfo::Enum("statusBar", "Status Bar", "Display", &CrossPointSettings::statusBar,
                        {"None", "No Progress", "Full w/ Percentage", "Full w/ Progress Bar", "Progress Bar"}),
      SettingInfo::Enum("hideBatteryPercentage", "Hide Battery %", "Display",
                        &CrossPointSettings::hideBatteryPercentage, {"Never", "In Reader", "Always"}),
      SettingInfo::Enum("refreshFrequency", "Refresh Frequency", "Display", &CrossPointSettings::refreshFrequency,
                        {"1 page", "5 pages", "10 pages", "15 pages", "30 pages"}),

      // Reader
      SettingInfo::Enum("fontFamily", "Font Family", "Reader", &CrossPointSettings::fontFamily,
                        {"Bookerly", "Noto Sans", "Open Dyslexic"}),
      SettingInfo::Enum("fontSize", "Font Size", "Reader", &CrossPointSettings::fontSize,
                        {"Small", "Medium", "Large", "X Large"}),
      SettingInfo::Enum("lineSpacing", "Line Spacing", "Reader", &CrossPointSettings::lineSpacing,
                        {"Tight", "Normal", "Wide"}),
      SettingInfo::Value("screenMargin", "Screen Margin", "Reader", &CrossPointSettings::screenMargin, {5, 40, 5}),
      SettingInfo::Enum("paragraphAlignment", "Paragraph Alignment", "Reader",
                        &CrossPointSettings::paragraphAlignment, {"Justify", "Left", "Center", "Right"}),
      SettingInfo::Toggle("hyphenationEnabled", "Hyphenation", "Reader", &CrossPointSettings::hyphenationEnabled),
      SettingInfo::Enum("orientation", "Reading Orientation", "Reader", &CrossPointSettings::orientation,
                        {"Portrait", "Landscape CW", "Inverted", "Landscape CCW"}),
      SettingInfo::Toggle("extraParagraphSpacing", "Extra Paragraph Spacing", "Reader",
                          &CrossPointSettings::extraParagraphSpacing),
      SettingInfo::Toggle("textAntiAliasing", "Text Anti-Aliasing", "Reader", &CrossPointSettings::textAntiAliasing),

      // Controls
      SettingInfo::Enum(
          "frontButtonLayout", "Front Button Layout", "Controls", &CrossPointSettings::frontButtonLayout,
          {"Bck, Cnfrm, Lft, Rght", "Lft, Rght, Bck, Cnfrm", "Lft, Bck, Cnfrm, Rght", "Bck, Cnfrm, Rght, Lft"}),
      SettingInfo::Enum("sideButtonLayout", "Side Button Layout (reader)", "Controls",
                        &CrossPointSettings::sideButtonLayout, {"Prev, Next", "Next, Prev"}),
      SettingInfo::Toggle("longPressChapterSkip", "Long-press Chapter Skip", "Controls",
                          &CrossPointSettings::longPressChapterSkip),
      SettingInfo::Enum("shortPwrBtn", "Short Power Button Click", "Controls", &CrossPointSettings::shortPwrBtn,
                        {"Ignore", "Sleep", "Page Turn"}),

      // System
      SettingInfo::Enum("sleepTimeout", "Time to Sleep", "System", &CrossPointSettings::sleepTimeout,
                        {"1 min", "5 min", "10 min", "15 min", "30 min"}),

      // KOReader Sync (device sub-screen accessed via System > KOReader Sync action)
      SettingInfo::DynamicString(
          "koUsername", "Username", "KOReader Sync", [] { return KOREADER_STORE.getUsername(); },
          [](const std::string& v) { KOREADER_STORE.setCredentials(v, KOREADER_STORE.getPassword()); }, 64),
      SettingInfo::DynamicString(
          "koPassword", "Password", "KOReader Sync", [] { return KOREADER_STORE.getPassword(); },
          [](const std::string& v) { KOREADER_STORE.setCredentials(KOREADER_STORE.getUsername(), v); }, 64),
      SettingInfo::DynamicString(
          "koServerUrl", "Sync Server URL", "KOReader Sync", [] { return KOREADER_STORE.getServerUrl(); },
          [](const std::string& v) { KOREADER_STORE.setServerUrl(v); }, 128),
      SettingInfo::DynamicEnum(
          "koMatchMethod", "Document Matching", "KOReader Sync",
          [] { return static_cast<uint8_t>(KOREADER_STORE.getMatchMethod()); },
          [](uint8_t v) { KOREADER_STORE.setMatchMethod(static_cast<DocumentMatchMethod>(v)); },
          {"Filename", "Binary"}),

      // OPDS Browser (device sub-screen accessed via System > OPDS Browser action)
      SettingInfo::String("opdsServerUrl", "Server URL", "OPDS Browser", SETTINGS.opdsServerUrl,
                          sizeof(SETTINGS.opdsServerUrl) - 1),
      SettingInfo::String("opdsUsername", "Username", "OPDS Browser", SETTINGS.opdsUsername,
                          sizeof(SETTINGS.opdsUsername) - 1),
      SettingInfo::String("opdsPassword", "Password", "OPDS Browser", SETTINGS.opdsPassword,
                          sizeof(SETTINGS.opdsPassword) - 1),
  };
}

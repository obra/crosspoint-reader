#pragma once
#include <vector>

#include "CrossPointSettings.h"
#include "activities/settings/CategorySettingsActivity.h"

// Returns the flat list of all settings for the web API.
// This is used by CrossPointWebServer to expose settings over HTTP.
// Categories match the device UI grouping for consistency.
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

      // Calibre / OPDS
      SettingInfo::String("opdsServerUrl", "OPDS Server URL", "Calibre", SETTINGS.opdsServerUrl,
                          sizeof(SETTINGS.opdsServerUrl) - 1),
      SettingInfo::String("opdsUsername", "OPDS Username", "Calibre", SETTINGS.opdsUsername,
                          sizeof(SETTINGS.opdsUsername) - 1),
      SettingInfo::String("opdsPassword", "OPDS Password", "Calibre", SETTINGS.opdsPassword,
                          sizeof(SETTINGS.opdsPassword) - 1),
  };
}

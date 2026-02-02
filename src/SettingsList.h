#pragma once
#include <vector>

#include "CrossPointSettings.h"
#include "activities/settings/CategorySettingsActivity.h"

// Returns the flat list of all settings for the web API.
// This is used by CrossPointWebServer to expose settings over HTTP.
inline std::vector<SettingInfo> getSettingsList() {
  return {
      // Display
      SettingInfo::Enum("sleepScreen", "Sleep Screen", &CrossPointSettings::sleepScreen,
                        {"Dark", "Light", "Custom", "Cover", "None"}),
      SettingInfo::Enum("sleepScreenCoverMode", "Sleep Screen Cover Mode", &CrossPointSettings::sleepScreenCoverMode,
                        {"Fit", "Crop"}),
      SettingInfo::Enum("sleepScreenCoverFilter", "Sleep Screen Cover Filter",
                        &CrossPointSettings::sleepScreenCoverFilter, {"None", "Contrast", "Inverted"}),
      SettingInfo::Enum("statusBar", "Status Bar", &CrossPointSettings::statusBar,
                        {"None", "No Progress", "Full w/ Percentage", "Full w/ Progress Bar", "Progress Bar"}),
      SettingInfo::Enum("hideBatteryPercentage", "Hide Battery %", &CrossPointSettings::hideBatteryPercentage,
                        {"Never", "In Reader", "Always"}),
      SettingInfo::Enum("refreshFrequency", "Refresh Frequency", &CrossPointSettings::refreshFrequency,
                        {"1 page", "5 pages", "10 pages", "15 pages", "30 pages"}),

      // Reader
      SettingInfo::Enum("fontFamily", "Font Family", &CrossPointSettings::fontFamily,
                        {"Bookerly", "Noto Sans", "Open Dyslexic"}),
      SettingInfo::Enum("fontSize", "Font Size", &CrossPointSettings::fontSize,
                        {"Small", "Medium", "Large", "X Large"}),
      SettingInfo::Enum("lineSpacing", "Line Spacing", &CrossPointSettings::lineSpacing, {"Tight", "Normal", "Wide"}),
      SettingInfo::Value("screenMargin", "Screen Margin", &CrossPointSettings::screenMargin, {5, 40, 5}),
      SettingInfo::Enum("paragraphAlignment", "Paragraph Alignment", &CrossPointSettings::paragraphAlignment,
                        {"Justify", "Left", "Center", "Right"}),
      SettingInfo::Toggle("hyphenationEnabled", "Hyphenation", &CrossPointSettings::hyphenationEnabled),
      SettingInfo::Enum("orientation", "Reading Orientation", &CrossPointSettings::orientation,
                        {"Portrait", "Landscape CW", "Inverted", "Landscape CCW"}),
      SettingInfo::Toggle("extraParagraphSpacing", "Extra Paragraph Spacing",
                          &CrossPointSettings::extraParagraphSpacing),
      SettingInfo::Toggle("textAntiAliasing", "Text Anti-Aliasing", &CrossPointSettings::textAntiAliasing),

      // Controls
      SettingInfo::Enum(
          "frontButtonLayout", "Front Button Layout", &CrossPointSettings::frontButtonLayout,
          {"Bck, Cnfrm, Lft, Rght", "Lft, Rght, Bck, Cnfrm", "Lft, Bck, Cnfrm, Rght", "Bck, Cnfrm, Rght, Lft"}),
      SettingInfo::Enum("sideButtonLayout", "Side Button Layout (reader)", &CrossPointSettings::sideButtonLayout,
                        {"Prev, Next", "Next, Prev"}),
      SettingInfo::Toggle("longPressChapterSkip", "Long-press Chapter Skip", &CrossPointSettings::longPressChapterSkip),
      SettingInfo::Enum("shortPwrBtn", "Short Power Button Click", &CrossPointSettings::shortPwrBtn,
                        {"Ignore", "Sleep", "Page Turn"}),

      // System
      SettingInfo::Enum("sleepTimeout", "Time to Sleep", &CrossPointSettings::sleepTimeout,
                        {"1 min", "5 min", "10 min", "15 min", "30 min"}),
      SettingInfo::String("opdsServerUrl", "OPDS Server URL", SETTINGS.opdsServerUrl,
                          sizeof(SETTINGS.opdsServerUrl) - 1),
  };
}

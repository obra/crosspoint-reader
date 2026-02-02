#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include <functional>
#include <string>
#include <vector>

#include "activities/ActivityWithSubactivity.h"

class CrossPointSettings;

enum class SettingType { TOGGLE, ENUM, ACTION, VALUE, STRING };

struct SettingInfo {
  const char* key;                         // JSON key for web API (nullptr for ACTION types)
  const char* name;                        // Display name of the setting
  SettingType type;
  uint8_t CrossPointSettings::* valuePtr;  // Pointer to member in CrossPointSettings (for TOGGLE/ENUM/VALUE)
  char* stringPtr;                         // Pointer to char array (for STRING type)
  size_t stringMaxLen;                     // Max length for STRING type
  std::vector<std::string> enumValues;

  struct ValueRange {
    uint8_t min;
    uint8_t max;
    uint8_t step;
  };
  ValueRange valueRange;

  static SettingInfo Toggle(const char* key, const char* name, uint8_t CrossPointSettings::* ptr) {
    return {key, name, SettingType::TOGGLE, ptr, nullptr, 0, {}, {}};
  }

  static SettingInfo Enum(const char* key, const char* name, uint8_t CrossPointSettings::* ptr,
                          std::vector<std::string> values) {
    return {key, name, SettingType::ENUM, ptr, nullptr, 0, std::move(values), {}};
  }

  static SettingInfo Action(const char* name) {
    return {nullptr, name, SettingType::ACTION, nullptr, nullptr, 0, {}, {}};
  }

  static SettingInfo Value(const char* key, const char* name, uint8_t CrossPointSettings::* ptr,
                           const ValueRange valueRange) {
    return {key, name, SettingType::VALUE, ptr, nullptr, 0, {}, valueRange};
  }

  static SettingInfo String(const char* key, const char* name, char* ptr, size_t maxLen) {
    return {key, name, SettingType::STRING, nullptr, ptr, maxLen, {}, {}};
  }
};

class CategorySettingsActivity final : public ActivityWithSubactivity {
  TaskHandle_t displayTaskHandle = nullptr;
  SemaphoreHandle_t renderingMutex = nullptr;
  bool updateRequired = false;
  int selectedSettingIndex = 0;
  const char* categoryName;
  const SettingInfo* settingsList;
  int settingsCount;
  const std::function<void()> onGoBack;

  static void taskTrampoline(void* param);
  [[noreturn]] void displayTaskLoop();
  void render() const;
  void toggleCurrentSetting();

 public:
  CategorySettingsActivity(GfxRenderer& renderer, MappedInputManager& mappedInput, const char* categoryName,
                           const SettingInfo* settingsList, int settingsCount, const std::function<void()>& onGoBack)
      : ActivityWithSubactivity("CategorySettings", renderer, mappedInput),
        categoryName(categoryName),
        settingsList(settingsList),
        settingsCount(settingsCount),
        onGoBack(onGoBack) {}
  void onEnter() override;
  void onExit() override;
  void loop() override;
};

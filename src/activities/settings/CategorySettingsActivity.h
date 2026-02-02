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
  const char* category;                    // Category for grouping in web UI (nullptr = uncategorized)
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

  // Dynamic accessors for settings not in CrossPointSettings
  std::function<uint8_t()> valueGetter;
  std::function<void(uint8_t)> valueSetter;
  std::function<std::string()> stringGetter;
  std::function<void(const std::string&)> stringSetter;

  static SettingInfo Toggle(const char* key, const char* name, const char* category,
                            uint8_t CrossPointSettings::* ptr) {
    return {key, name, category, SettingType::TOGGLE, ptr, nullptr, 0, {}, {}};
  }

  static SettingInfo Enum(const char* key, const char* name, const char* category,
                          uint8_t CrossPointSettings::* ptr, std::vector<std::string> values) {
    return {key, name, category, SettingType::ENUM, ptr, nullptr, 0, std::move(values), {}};
  }

  static SettingInfo Action(const char* name) {
    return {nullptr, name, nullptr, SettingType::ACTION, nullptr, nullptr, 0, {}, {}};
  }

  static SettingInfo Value(const char* key, const char* name, const char* category,
                           uint8_t CrossPointSettings::* ptr, const ValueRange valueRange) {
    return {key, name, category, SettingType::VALUE, ptr, nullptr, 0, {}, valueRange};
  }

  static SettingInfo String(const char* key, const char* name, const char* category, char* ptr, size_t maxLen) {
    return {key, name, category, SettingType::STRING, nullptr, ptr, maxLen, {}, {}};
  }

  static SettingInfo DynamicEnum(const char* key, const char* name, const char* category,
                                 std::function<uint8_t()> getter, std::function<void(uint8_t)> setter,
                                 std::vector<std::string> values) {
    SettingInfo info{};
    info.key = key;
    info.name = name;
    info.category = category;
    info.type = SettingType::ENUM;
    info.enumValues = std::move(values);
    info.valueGetter = std::move(getter);
    info.valueSetter = std::move(setter);
    return info;
  }

  static SettingInfo DynamicString(const char* key, const char* name, const char* category,
                                   std::function<std::string()> getter,
                                   std::function<void(const std::string&)> setter, size_t maxLen) {
    SettingInfo info{};
    info.key = key;
    info.name = name;
    info.category = category;
    info.type = SettingType::STRING;
    info.stringMaxLen = maxLen;
    info.stringGetter = std::move(getter);
    info.stringSetter = std::move(setter);
    return info;
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

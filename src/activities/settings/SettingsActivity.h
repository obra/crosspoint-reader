#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include <functional>
#include <string>
#include <vector>

#include "CategorySettingsActivity.h"
#include "activities/ActivityWithSubactivity.h"

class SettingsActivity final : public ActivityWithSubactivity {
  static constexpr int categoryCount = 4;
  static const char* categoryNames[categoryCount];

  TaskHandle_t displayTaskHandle = nullptr;
  SemaphoreHandle_t renderingMutex = nullptr;
  bool updateRequired = false;
  int selectedCategoryIndex = 0;  // Currently selected category
  const std::function<void()> onGoHome;
  std::vector<SettingInfo> categorySettings[categoryCount];

  static void taskTrampoline(void* param);
  [[noreturn]] void displayTaskLoop();
  void render() const;
  void enterCategory(int categoryIndex);

 public:
  explicit SettingsActivity(GfxRenderer& renderer, MappedInputManager& mappedInput,
                            const std::function<void()>& onGoHome)
      : ActivityWithSubactivity("Settings", renderer, mappedInput), onGoHome(onGoHome) {}
  void onEnter() override;
  void onExit() override;
  void loop() override;
};

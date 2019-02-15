#include <Arduino.h>

#include <BLEDevice.h>
#include <soc/rtc_cntl_reg.h>
#include <soc/soc.h>

#include "conf.h"
#include "log.h"

#include "BLEKeyboard.h"
#include "Button.h"

Button leftTurn(LEFT_TURN_PIN);
Button rightTurn(RIGHT_TURN_PIN);
Button FTPup(FTP_UP_PIN);
Button FTPdown(FTP_DOWN_PIN);
Button Screenshoot(SCREENSHOOT_PIN);

unsigned long lastActiveTime = 0;

void activate() {
  lastActiveTime = millis();
}

void updateButtons() {
  leftTurn.update();
  rightTurn.update();
  FTPup.update();
  FTPdown.update();
  Screenshoot.update();
  }

void deepSleep() {
  esp_deep_sleep_start();
}

void setup() {
  // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  Serial.println();

  LOG_I("zwift_Shortcut - An ESP32 based BLE Keynote remote controller.");
  LOG_I("based on a design by Henry Li <henry1943@163.com>.");
  LOG_I("Copyright %d. All rights reserved.", 2018);

  // Initialize buttons and laser emitter.
  leftTurn.onPress([]() {
    LOG_D("<<");
    BLEKeyboard.strokeKey(KEY_CODE_LEFT_ARROW);
    activate();
  });
  leftTurn.begin();

  rightTurn.onPress([]() {
    LOG_D(">>");
    BLEKeyboard.strokeKey(KEY_CODE_RIGHT_ARROW);
    activate();
  });
  rightTurn.begin();

  FTPup.onPress([]() {
    LOG_D(">>");
    BLEKeyboard.strokeKey(KEY_CODE_PAGE_UP);
    activate();
  });
  FTPup.begin();

  FTPdown.onPress([]() {
    LOG_D(">>");
    BLEKeyboard.strokeKey(KEY_CODE_PAGEDOWN);
    activate();
  });
  FTPdown.begin();

  Screenshoot.onPress([]() {
    LOG_D(">>");
    BLEKeyboard.strokeKey(KEY_CODE_F10);
    activate();
  });
  Screenshoot.begin();


  LOG_I("Initializing BLE Device '%s'...", DEVICE_NAME);
  BLEDevice::init(DEVICE_NAME);
  LOG_I("Initializing BLE HID services...");
  BLEKeyboard.begin();

  BLEKeyboard.startAdvertising();

  LOG_I("Initialization has been <DONE>.");
}

void loop() {
  updateButtons();

  if (millis() - lastActiveTime > MAX_ACTIVE_TIME) {
    deepSleep();
  }
}

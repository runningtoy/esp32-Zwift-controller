#include <Arduino.h>

#include "conf.h"
#include "log.h"

#include <BleKeyboard.h>

#include "Button.h"

BleKeyboard bleKeyboard(DEVICE_NAME,"Espressif",100);

Button leftTurn(LEFT_TURN_PIN);
Button rightTurn(RIGHT_TURN_PIN);
Button FTPup(FTP_UP_PIN);
Button FTPdown(FTP_DOWN_PIN);
Button Screenshot(SCREENSHOOT_PIN);



unsigned long lastActiveTime = 0;

void activate() {
  lastActiveTime = millis();
}

void updateButtons() {
  leftTurn.update();
  rightTurn.update();
  FTPup.update();
  FTPdown.update();
  Screenshot.update();
  }

void deepSleep() {
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  LOG_I("Initializing BLE HID services...");
  bleKeyboard.begin();
  LOG_I("Initialization has been <DONE>.");

  // Initialize buttons and laser emitter.
  leftTurn.onPress([]() {
    LOG_D("KEY_CODE_LEFT_ARROW");
    bleKeyboard.write(KEY_LEFT_ARROW);
    activate();
  });
  leftTurn.begin();

  rightTurn.onPress([]() {
    LOG_D("KEY_CODE_RIGHT_ARROW");
    bleKeyboard.write(KEY_RIGHT_ARROW);
    activate();
  });
  rightTurn.begin();

  FTPup.onPress([]() {
    LOG_D("KEY_CODE_PAGE_UP");
    bleKeyboard.write(KEY_PAGE_UP);
    activate();
  });
  FTPup.begin();

  FTPdown.onPress([]() {
    LOG_D("KEY_CODE_PAGEDOWN");
    bleKeyboard.write(KEY_PAGE_DOWN);
    activate();
  });
  FTPdown.begin();

  Screenshot.onPress([]() {
    LOG_D("KEY_CODE_F10");
    bleKeyboard.write(KEY_F10);
    activate();
  });
  Screenshot.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    updateButtons();
  }
}

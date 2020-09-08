#include <Arduino.h>

#include "conf.h"
#include "log.h"

#include <BleKeyboard.h>

#include "OneButton.h"

#include <Ticker.h>

BleKeyboard bleKeyboard(DEVICE_NAME, "Espressif", 100);

OneButton leftTurn(LEFT_TURN_PIN, true, true);
OneButton rightTurn(RIGHT_TURN_PIN, true, true);
OneButton FTPup(FTP_UP_PIN, true, true);
OneButton FTPdown(FTP_DOWN_PIN, true, true);
// Button Screenshot(SCREENSHOOT_PIN);

Ticker watchDOG;
#define watchdogMAXCounter 60 * 60 // 60minuten
static uint32_t watchdogCounter = watchdogMAXCounter;


unsigned long lastActiveTime = 0;

void activate() {
  lastActiveTime = millis();
}

void fct_powerdown(){
  LOG_D("PowerOFF...");
    digitalWrite(LED, LOW);
    digitalWrite(POWERLATCH, LOW);
}
void fct_Watchdog() {
  watchdogCounter--;
  if (watchdogCounter < 1) {
    fct_powerdown();
  }
}

void fct_WatchdogReset() {
  watchdogCounter = watchdogMAXCounter;
}

void updateButtons() {
  leftTurn.tick();
  rightTurn.tick();
  FTPup.tick();
  FTPdown.tick();
  // Screenshot.tick();
}

void click_leftTurn() {
  LOG_D("KEY_CODE_LEFT_ARROW");
  fct_WatchdogReset();
  bleKeyboard.write(KEY_LEFT_ARROW);
}
void doubleclick_leftTurn() {
  LOG_D("KEY_CODE_SPACE");
  fct_WatchdogReset();
  bleKeyboard.print(" ");
}

void click_rightTurn() {
  LOG_D("KEY_CODE_RIGHT_ARROW");
  fct_WatchdogReset();
  bleKeyboard.write(KEY_RIGHT_ARROW);
}
void doubleclick_rightTurn() {
  LOG_D("KEY_CODE_SPACE");
  fct_WatchdogReset();
  bleKeyboard.print(" ");
}

void click_FTPup() {
  LOG_D("KEY_CODE_PAGE_UP");
  fct_WatchdogReset();
  bleKeyboard.write(KEY_PAGE_UP);
}

void doubleclick_FTPup() {
  LOG_D("KEY_CODE_F10");
  fct_WatchdogReset();
  bleKeyboard.write(KEY_F10);
}

void LongPressStart_FTPUp(){
    fct_powerdown();
}

void click_FTPdown() {
  LOG_D("KEY_CODE_PAGEDOWN");
  fct_WatchdogReset();
  bleKeyboard.write(KEY_PAGE_DOWN);
}
void doubleclick_FTPdown() {
  LOG_D("KEY_CODE_F10");
  fct_WatchdogReset();
  bleKeyboard.write(KEY_F10);
}

void setup() {
  pinMode(POWERLATCH, OUTPUT);
  pinMode(LED, OUTPUT);
  // Keeps the circuit on
  digitalWrite(POWERLATCH, HIGH);
  digitalWrite(LED, HIGH);

  watchDOG.attach(1, fct_Watchdog);

  Serial.begin(115200);
  Serial.println();

  LOG_I("Initializing BLE HID services...");
  bleKeyboard.begin();
  LOG_I("Initialization has been <DONE>.");

  leftTurn.attachClick(click_leftTurn);
  leftTurn.attachDoubleClick(doubleclick_leftTurn);

  rightTurn.attachClick(click_rightTurn);
  rightTurn.attachDoubleClick(doubleclick_rightTurn);

  FTPup.attachClick(click_FTPup);
  FTPup.attachDoubleClick(doubleclick_FTPup);
  FTPup.attachLongPressStart(LongPressStart_FTPUp);

  FTPdown.attachClick(click_FTPdown);
  FTPdown.attachDoubleClick(doubleclick_FTPdown);
}

void loop() {
  if (bleKeyboard.isConnected()) {
    updateButtons();
  }
  FTPup.tick();
}

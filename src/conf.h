#pragma once

#include <BLEHIDDevice.h>

#define DEVICE_NAME "zwift_Shortcut"

#define RIGHT_TURN_PIN 25
#define LEFT_TURN_PIN 4
#define FTP_UP_PIN 4
#define FTP_DOWN_PIN 4
#define SCREENSHOOT_PIN 4

// Sleep after 5 minutes
#define MAX_ACTIVE_TIME 5 * 60 * 1000

/*
 * HOME  - 0x4a
 * END   - 0x4d
 * RIGHT - 0x4f
 * LEFT  - 0x50
 * DOWN  - 0x51
 * UP    - 0x52
 */
#define KEY_CODE_LEFT_ARROW 0x50
#define KEY_CODE_RIGHT_ARROW 0x4f
#define KEY_CODE_PAGE_UP 0x4B
#define KEY_CODE_PAGEDOWN 0x4E
#define KEY_CODE_F10 0x43

//https://zwiftinsider.com/keyboard-shortcuts/

const uint8_t KEYBOARD_REPORT_MAP[] PROGMEM = {
    USAGE_PAGE(1),
    0x01, // Generic Desktop Ctrls
    USAGE(1),
    0x06, // Keyboard
    COLLECTION(1),
    0x01, // Application
    REPORT_ID(1),
    0x01, // REPORTID
    USAGE_PAGE(1),
    0x07, //   Kbrd/Keypad
    USAGE_MINIMUM(1),
    0xE0,
    USAGE_MAXIMUM(1),
    0xE7,
    LOGICAL_MINIMUM(1),
    0x00,
    LOGICAL_MAXIMUM(1),
    0x01,
    REPORT_SIZE(1),
    0x01, //   1 byte (Modifier)
    REPORT_COUNT(1),
    0x08,
    HIDINPUT(1),
    0x02, //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position
    REPORT_COUNT(1),
    0x01, //   1 byte (Reserved)
    REPORT_SIZE(1),
    0x08,
    HIDINPUT(1),
    0x01, //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
    REPORT_COUNT(1),
    0x05, //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
    REPORT_SIZE(1),
    0x01,
    USAGE_PAGE(1),
    0x08, //   LEDs
    USAGE_MINIMUM(1),
    0x01, //   Num Lock
    USAGE_MAXIMUM(1),
    0x05, //   Kana
    HIDOUTPUT(1),
    0x02, //   Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
    REPORT_COUNT(1),
    0x01, //   3 bits (Padding)
    REPORT_SIZE(1),
    0x03,
    HIDOUTPUT(1),
    0x01, //   Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile
    REPORT_COUNT(1),
    0x06, //   6 bytes (Keys)
    REPORT_SIZE(1),
    0x08,
    LOGICAL_MINIMUM(1),
    0x00,
    LOGICAL_MAXIMUM(1),
    0x65, //   101 keys
    USAGE_PAGE(1),
    0x07, //   Kbrd/Keypad
    USAGE_MINIMUM(1),
    0x00,
    USAGE_MAXIMUM(1),
    0x65,
    HIDINPUT(1),
    0x00, //   Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
    END_COLLECTION(0)};

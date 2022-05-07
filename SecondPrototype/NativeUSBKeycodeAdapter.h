#ifndef NATIVEUSBKEYCODEADAPTER_H
#define NATIVEUSBKEYCODEADAPTER_H

#include "USBKeycodeAdapter.h"
#include "usb_hid_keys.h"

/* many ideas, some code and inspiratiosn from  Keyboard.cpp From Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett
*/

#include "HID.h"

#if !defined(_USING_HID)
#error "Must compile for an USB HID Board (Leonardo, Pro Micro, etc.)
#endif

typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class NativeUSBKeycodeAdapter : public USBKeycodeAdapter {
  public:
    NativeUSBKeycodeAdapter();
    void setup() {
    }

    void scanKeyCallback(keycode_t keycode, bool value, bool prevValue) {
      if(value) { // false = pressed 1 = release
        release(keycode);
      } else {
        press(keycode);
      }
    }

    void scanEndCallback() {
      sendReport(&_keyReport);
    };

  private:
    KeyReport _keyReport;
    void sendReport(KeyReport* keys);
    size_t press(keycode_t k);
    size_t release(keycode_t k);
};

#endif

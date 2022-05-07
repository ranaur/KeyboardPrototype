#ifndef USBKEYCODEKEYBOARD_H
#define USBKEYCODEKEYBOARD_H

#include "usb_hid_keys.h"

/* many ideas, some code and inspiratiosn from  Keyboard.cpp From Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett
*/

#include "HID.h"

#if !defined(_USING_HID)
#error "Must compile for an USB HID Board (Leonardo, Pro Micro, etc.)
#endif

typedef uint8_t keycode_t;

typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class USBKeycodeKeyboard {
  public:
    USBKeycodeKeyboard();
    size_t press(keycode_t k);
    size_t release(keycode_t k);
    void send() { sendReport(&_keyReport); }
    
  private:
    KeyReport _keyReport;
    void sendReport(KeyReport* keys);
};

#endif

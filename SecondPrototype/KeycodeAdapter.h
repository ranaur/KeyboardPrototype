#ifndef KEYCODE_MKA
#define KEYCODE_MKA

//#include "usb_hid_keys.h"

typedef uint8_t keycode_t;

class KeycodeAdapter {
  public:
    virtual void scanKeyCallback(keycode_t keycode, bool value, bool prevValue);
    virtual void scanEndCallback();
};

#endif

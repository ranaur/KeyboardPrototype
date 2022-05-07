#ifndef USBKEYCODEADAPTER_H
#define USBKEYCODEADAPTER_H

#include "KeycodeAdapter.h"

class USBKeycodeAdapter : public KeycodeAdapter {
  public:
    virtual void setup();
    virtual void scanKeyCallback(keycode_t keycode, bool value, bool prevValue);
    virtual void scanEndCallback();
};

#endif

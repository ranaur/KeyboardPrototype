#ifndef USBHIDMATRIXKEYBOARDDRIVER_H
#define USBHIDMATRIXKEYBOARDDRIVER_H

#include <HID-Project.h>
#include "MatrixKeyboardDriver.h"
#include "usb_hid_keys.h"
#include "debug.h"

class USBHIDMatrixKeyboardDriver : MatrixKeyboardDriver {
  public:
    static void setup();
    static void OnDown(uint8_t row, uint8_t column, void *obj);
    static void OnUp(uint8_t row, uint8_t column, void *obj);
    static void OnCycleEnd(void *obj);
};

#define matrixKeyboardDriver USBHIDMatrixKeyboardDriver
extern uint16_t rowColumnMap(uint8_t row, uint8_t column);

#endif

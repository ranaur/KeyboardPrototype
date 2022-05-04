#ifndef USBNATIVEMATRIXKEYBOARDDRIVER_H
#define USBNATIVEMATRIXKEYBOARDDRIVER_H

#include <Keyboard.h>
#include "MatrixKeyboardDriver.h"
#include "usb_hid_keys.h"
#include "debug.h"


class USBNativeMatrixKeyboardDriver : MatrixKeyboardDriver {
  public:
    static void setup(MatrixKeyboard *mk);
    static void OnDown(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj);
    static void OnUp(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj);
    static void OnCycleEnd(MatrixKeyboard *mk, void *obj);
};

#define matrixKeyboardDriver USBNativeMatrixKeyboardDriver
extern uint16_t rowColumnMap(uint8_t row, uint8_t column);

#endif

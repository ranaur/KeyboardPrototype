#ifndef USBNATIVEMATRIXKEYBOARDDRIVER_H
#define USBNATIVEMATRIXKEYBOARDDRIVER_H

#include <Keyboard.h>
#include "MatrixKeyboardDriver.h"
#include "debug.h"


class USBNativeMatrixKeyboardDriver : MatrixKeyboardDriver {
  public:
    static void setup();
    static void OnDown(uint8_t row, uint8_t column, void *obj);
    static void OnUp(uint8_t row, uint8_t column, void *obj);
    static void OnCycleEnd(void *obj);
};

#define matrixKeyboardDriver USBNativeMatrixKeyboardDriver
extern uint16_t rowColumnMap(uint8_t row, uint8_t column);

#endif

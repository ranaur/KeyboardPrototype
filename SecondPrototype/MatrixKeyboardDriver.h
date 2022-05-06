#ifndef MATRIXKEYBOARDDRIVER_H
#define MATRIXKEYBOARDDRIVER_H

#include "MatrixKeyboard.h"

class MatrixKeyboardDriver {
  public:
    MatrixKeyboardDriver() {};
    static void setup() {};
    static void OnDown(uint8_t row, uint8_t column, void *obj) {};
    static void OnUp(uint8_t row, uint8_t column, void *obj) {};
    static void OnCycleEnd(void *obj) {};
};

#endif

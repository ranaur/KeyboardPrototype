#ifndef MATRIXKEYBOARDDRIVER_H
#define MATRIXKEYBOARDDRIVER_H

#include "MatrixKeyboard.h"

class MatrixKeyboard;

class MatrixKeyboardDriver {
  public:
    MatrixKeyboardDriver() {};
    static void setup(MatrixKeyboard *mk) {};
    static void OnDown(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj) {};
    static void OnUp(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj) {};
    static void OnCycleEnd(MatrixKeyboard *mk, void *obj) {};
};

#endif

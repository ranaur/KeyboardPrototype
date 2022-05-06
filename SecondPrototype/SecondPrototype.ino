#include "MatrixKeyboard.h"

#include "USBNative.h"
/*
const char *rowColumnMappings[nRows][nColumns] = {
  { KEY_KP1, KEY_KP2, KEY_KP3 }, 
  { KEY_KP4, KEY_KP5, KEY_KP6 }, 
  { KEY_KP7, KEY_KP8, KEY_KP9 }, 
  { KEY_LEFTALT, KEY_KP0, KEY_KPENTER }
};
*/

MatrixKeyboard<nRows, nColumns> matrix;

void setup() {
  
#ifdef DEBUG
  Serial.begin(9600);

  // Wait for USB Serial (Leonardo)
  while (!Serial) {
    yield();
  }
#endif

  matrix.setup(rowsPins, columnsPins);
  matrix.setDownEvent(matrixKeyboardDriver::OnDown);
  matrix.setUpEvent(matrixKeyboardDriver::OnUp);
  matrix.setCycleEndEvent(matrixKeyboardDriver::OnCycleEnd);
}

void loop() {
  matrix.loop((void *)0);
}

const uint8_t nRows = 4;
const uint8_t nColumns = 3;
const uint8_t rowsPins[nRows] = { 11, 10, 9, 8 };
const uint8_t columnsPins[nColumns] = { 7, 6, 5 };

#include "MatrixKeyboard.h"
#include "DebouncerMatrixKeyboardAdapter.h"
#include "DebuggerMatrixKeyboardAdapter.h"
#include "TransitionMatrixKeyboardAdapter.h"
#include "RowColumMapperAdapter.h"

#include "usb_hid_keys.h"
//#include "USBNative.h"

const keycode_t rowColumnMappings[nRows][nColumns] = {
  { KEY_KP1, KEY_KP2, KEY_KP3 }, 
  { KEY_KP4, KEY_KP5, KEY_KP6 }, 
  { KEY_KP7, KEY_KP8, KEY_KP9 }, 
  { KEY_LEFTALT, KEY_KP0, KEY_KPENTER }
};

MatrixKeyboard<nRows, nColumns> matrix;
DebouncerMatrixKeyboardAdapter<nRows, nColumns> debouncer;
TransitionMatrixKeyboardAdapter<nRows, nColumns> transition;
DebuggerMatrixKeyboardAdapter<nRows, nColumns> debugger;
RowColumnMapperMatrixKeyboardAdapter<nRows, nColumns> mapper;

void setup() {
  
//#ifdef DEBUG
  Serial.begin(9600);

  // Wait for USB Serial (Leonardo)
  while (!Serial) {
    yield();
  }
//#endif

  matrix.setup(rowsPins, columnsPins);
  matrix.setAdapter(&transition);
  debouncer.setAdapter(&transition);
  transition.setAdapter(&mapper);
  mapper.setAdapter(&debugger);
  mapper.setMap(&rowColumnMappings);
}

void loop() {
  matrix.loop();
}

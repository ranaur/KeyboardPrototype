#include "USBNativeMatrixKeyboardDriver.h"


void USBNativeMatrixKeyboardDriver::OnDown(uint8_t row, uint8_t column, void *obj) {
  const char *keyText = rowColumnMap(row, column);

  debug("DOWN ");
  
  for(int i = 0; keyText[i] != '\0'; i++) {
    Keyboard.press(keyText[i]);
    debug(keyText[i]);
  }
  debugln("");  
}

void USBNativeMatrixKeyboardDriver::OnUp(uint8_t row, uint8_t column, void *obj) {
  const char *keyText = rowColumnMap(row, column);

  debug("UP ");
  
  for(int i = 0; keyText[i] != '\0'; i++) {
    Keyboard.release(keyText[i]);
    debug(keyText[i]);
  }
  debugln("");  
}

void USBNativeMatrixKeyboardDriver::OnCycleEnd(void *obj) {
  debug("CYCLE END ");
  
  debugln("");  
}

void USBNativeMatrixKeyboardDriver::setup() {
  //mk->setDownEvent(USBNativeMatrixKeyboardDriver::OnDown);
  //mk->setUpEvent(USBNativeMatrixKeyboardDriver::OnUp);
  //mk->setCycleEndEvent(USBNativeMatrixKeyboardDriver::OnCycleEnd);
}

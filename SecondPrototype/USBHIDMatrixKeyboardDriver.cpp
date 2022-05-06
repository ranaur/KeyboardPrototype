#include "USBHIDMatrixKeyboardDriver.h"

void USBHIDMatrixKeyboardDriver::OnDown(uint8_t row, uint8_t column, void *obj) {
  const char *keyText = rowColumnMap(row, column);

  debug("DOWN ");
  
  for(int i = 0; keyText[i] != '\0'; i++) {
    //Keyboard.press(keyText[i]);
    debug(keyText[i]);
  }
  debugln("");  
}

void USBHIDMatrixKeyboardDriver::OnUp(uint8_t row, uint8_t column, void *obj) {
  const char *keyText = rowColumnMap(row, column);

  debug("UP ");
  
  for(int i = 0; keyText[i] != '\0'; i++) {
    //Keyboard.release(keyText[i]);
    debug(keyText[i]);
  }
  debugln("");  
}

void USBHIDMatrixKeyboardDriver::OnCycleEnd(void *obj) {
  debug("CYCLE END ");
  
  debugln("");  
}

void USBHIDMatrixKeyboardDriver::setup() {
  debugln("SETUP");

  //mk->setDownEvent(USBHIDMatrixKeyboardDriver::OnDown);
  //mk->setUpEvent(USBHIDMatrixKeyboardDriver::OnUp);
  //mk->setCycleEndEvent(USBHIDMatrixKeyboardDriver::OnCycleEnd);
}

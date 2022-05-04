// INC
#include "USBNativeMatrixKeyboardDriver.h"

typedef uint8_t pin_t;
typedef int state_t;

const pin_t columnsPins[] = { 7, 6, 5 };
const int8_t nColumns = sizeof(columnsPins) / sizeof(pin_t);

const pin_t rowsPins[] = { 11, 10, 9, 8 };
const int8_t nRows = sizeof(rowsPins) / sizeof(pin_t);

const char *rowColumnMappings[nRows][nColumns] = {
  { '1', '2', '3' }, 
  { '4', '5', '6' }, 
  { '7', '8', '8' }, 
  { '*', '0', '#' }
};

uint16_t rowColumnMap(uint8_t row, uint8_t column) {
  return rowColumnMappings[row][column];
}

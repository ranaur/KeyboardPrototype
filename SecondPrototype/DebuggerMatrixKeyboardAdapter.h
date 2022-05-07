#ifndef DEBUGGER_MKA_H
#define DEBUGGER_MKA_H

#include "MatrixKeyboard.h"
#include "RowColumMapperAdapter.h"

template <uint8_t nRows, uint8_t nColumns> class DebuggerMatrixKeyboardAdapter : public MatrixKeyboardAdapter<nRows, nColumns>, public KeycodeKeyboardAdapter<nRows, nColumns> {
  public:
    DebouncerMatrixKeyboardAdapter() {};
        // KeycodeKeyboardAdapter
    void scanKeyCallback(keycode_t keycode, bool value, bool prevValue) {
      Serial.print("KEYCODE: [");
      Serial.print(keycode, HEX);
      Serial.print("] = ");
      Serial.print(value);
      Serial.print(" (prev: ");
      Serial.print(prevValue);
      Serial.println(")");
    }
    void scanEndCallback() {
      Serial.println("END SCAN:");
    }
        // MatrixKeyboardAdapter
    void scanKeyCallback(uint8_t row, uint8_t column, bool value, bool prevValue) {
      Serial.print("ROW/COLUMN: [");
      Serial.print(row);
      Serial.print(", ");
      Serial.print(column);
      Serial.print("] = ");
      Serial.print(value);
      Serial.print(" (prev: ");
      Serial.print(value);
      Serial.println(")");
    }
    
    void scanEndCallback(MatrixDataType *bdata) {
      Serial.println("END SCAN:");
    }

    
};

#endif

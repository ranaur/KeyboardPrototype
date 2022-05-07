#ifndef ROWCOLUMN_MKA_H
#define ROWCOLUMN_MKA_H

#include "MatrixKeyboard.h"

typedef uint8_t keycode_t;

template <uint8_t nRows, uint8_t nColumns> class KeycodeKeyboardAdapter {
  public:
    virtual void scanKeyCallback(keycode_t keycode, bool value, bool prevValue);
    virtual void scanEndCallback();
};

template <uint8_t nRows, uint8_t nColumns> class RowColumnMapperMatrixKeyboardAdapter : public MatrixKeyboardAdapter<nRows, nColumns> {
  public:
    RowColumnMapperMatrixKeyboardAdapter(){};
    
    void setMap(const keycode_t (*rcmap)[nRows][nColumns]) {
      _rcmap = rcmap;
/*
      Serial.println("setMap:");
      for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nColumns; col++) {
          Serial.print( (*_rcmap)[row][col], HEX );
          Serial.print("\t");
        }
        Serial.println("");
      }
*/    };
  
    void scanKeyCallback(uint8_t row, uint8_t column, bool value, bool prevValue) {
      _adapter->scanKeyCallback(mapRowColumn(row, column), value, prevValue);
    }
    
    void scanEndCallback(MatrixDataType *bdata) {
      _adapter->scanEndCallback();
    }
    void setAdapter(KeycodeKeyboardAdapter<nRows, nColumns> *adapter) { 
      _adapter = adapter;
    };

  private:
    KeycodeKeyboardAdapter<nRows, nColumns> *_adapter;
    
    keycode_t mapRowColumn(uint8_t row, uint8_t column) {
      return (*_rcmap)[row % nRows][column % nColumns];
    }
    const keycode_t (*_rcmap)[nRows][nColumns];
};

#endif

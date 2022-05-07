#ifndef ROWCOLUMN_MKA_H
#define ROWCOLUMN_MKA_H

#include "MatrixKeyboard.h"
#include "KeycodeAdapter.h"

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
    void setAdapter(KeycodeAdapter *adapter) { 
      _adapter = adapter;
    };

  private:
    KeycodeAdapter *_adapter;
    
    keycode_t mapRowColumn(uint8_t row, uint8_t column) {
      return (*_rcmap)[row % nRows][column % nColumns];
    }
    const keycode_t (*_rcmap)[nRows][nColumns];
};

#endif

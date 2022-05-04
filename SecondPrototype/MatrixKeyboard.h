#ifndef MATRIX_KEYBORAD_H
#define MATRIX_KEYBORAD_H
/*  TODO:
 * row to column vs columns to row: allow both (today row: output, column input)
 * allow three presses: put everythiing on pullup, but the row/column being tested. if gets signal on columns, it is a three key press
 */

#include "Debounce.h"
#include "arduino.h"
#include "MatrixKeyboardDriver.h"

class MatrixKeyboard {
  public:
    MatrixKeyboard(uint8_t nRows, uint8_t nColumns);
    void setup( const uint8_t *rowPins, const uint8_t *columnPins);
    void setDownEvent( void (*callback)(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj) ) { _DownEventCallback = callback; };
    void setUpEvent( void (*callback)(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj) ) { _UpEventCallback = callback; };
    void setCycleEndEvent( void (*callback)(MatrixKeyboard *mk, void *obj) ) { _CycleEndEventCallback = callback; };
    void loop(void *obj);

  private:
    uint8_t rowPin(int index) {
      while(index < 0) index += _nRows;
      return _rowPins[index % _nRows];
    }
    uint8_t columnPin(int index) {
      while(index < 0) index += _nColumns;
      return _columnPins[index % _nColumns];
    }

    uint8_t _row;
    uint8_t _column;

    Debounce **debounceHandlers;    
    
    uint8_t _nRows;
    uint8_t _nColumns;
    uint8_t *_rowPins;
    uint8_t *_columnPins;

    void (*_DownEventCallback)(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj);
    void (*_UpEventCallback)(MatrixKeyboard *mk, uint8_t row, uint8_t column, void *obj);
    void (*_CycleEndEventCallback)(MatrixKeyboard *mk, void *obj);

    uint8_t *matrixRC;
    void setRC(uint8_t row, uint8_t column, bool value) { 
      uint16_t pos = row * column;
      uint8_t bitMask = 0x01 << (pos % 8);
      if(value) {
        matrixRC[pos / 8] |= bitMask;
      } else {
        matrixRC[pos / 8] &= ~bitMask;
      }
    }
    bool getRC(uint8_t row, uint8_t column) {
      uint16_t pos = row * column;
      return matrixRC[pos / 8] >> (pos % 8) & 0x01 == 0x01;
    }
};
#endif

#ifndef MATRIX_KEYBORAD_H
#define MATRIX_KEYBORAD_H
/*  TODO:
 * row to column vs columns to row: allow both (today row: output, column input)
 * allow three presses: put everythiing on pullup, but the row/column being tested. if gets signal on columns, it is a three key press
 */

#include "arduino.h"

template <uint8_t nRows, uint8_t nColumns> class MatrixKeyboard;
//template <uint8_t nRows, uint8_t nColumns> class DebouncerMatrixKeyboardAdapter;

#include "Bidimensional.h"

#define MatrixDataType BidimensionalData<bool, nRows, nColumns>

template <uint8_t nRows, uint8_t nColumns> class MatrixKeyboardAdapter {
  public:
    MatrixKeyboardAdapter() {};
    virtual void scanKeyCallback(uint8_t row, uint8_t column, bool value, bool prevValue);
    virtual void scanEndCallback(MatrixDataType *bdata);
};

template <uint8_t nRows, uint8_t nColumns> class MatrixKeyboard {
  public:
    MatrixKeyboard(); 
    void setup(const uint8_t *rowPins, const uint8_t *columnPins);
    void loop();
    void setAdapter(MatrixKeyboardAdapter<nRows, nColumns> *adapter) { _adapter = adapter; };

  private:
    MatrixKeyboardAdapter<nRows, nColumns> *_adapter;
    uint8_t *_rowPins;
    uint8_t *_columnPins;
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

    uint8_t _nRows;
    uint8_t _nColumns;

    MatrixDataType matrix;
};

template <uint8_t nRows, uint8_t nColumns> MatrixKeyboard<nRows, nColumns>::MatrixKeyboard() : 
    _nRows(nRows), 
    _nColumns(nColumns), 
    _adapter((MatrixKeyboardAdapter<nRows, nColumns> *)0),
    _rowPins((uint8_t *)0),
    _columnPins((uint8_t *)0),
    _row(0), 
    _column(0) {
      matrix.setAll(HIGH);
};

template <uint8_t nRows, uint8_t nColumns> void MatrixKeyboard<nRows, nColumns>::setup(const uint8_t *rowPins, const uint8_t *columnPins) {
  _rowPins = rowPins;
  _columnPins = columnPins;

  // Setup pins
  for(uint8_t r = 0; r < _nRows; r++) {
    pinMode(rowPin(r), INPUT_PULLUP);
  }

  for(uint8_t c = 0; c < _nColumns; c++) {
    pinMode(columnPin(c), INPUT_PULLUP);
  }
};

template <uint8_t nRows, uint8_t nColumns> void MatrixKeyboard<nRows, nColumns>::loop() {
  bool reading = digitalRead(rowPin(_row)) == HIGH ? true : false;
  bool prevReading = matrix.getData(_row, _column);
/*
      Serial.print("RAW: [");
      Serial.print(_row);
      Serial.print(", ");
      Serial.print(_column);
      Serial.print("] = ");
      Serial.print(reading);
      Serial.print(" (prev: ");
      Serial.print(prevReading);
      Serial.print(", pin(r/c): ");
      Serial.print(rowPin(_row));
      Serial.print("/");
      Serial.print(columnPin(_column));
      Serial.println(")");
 */ 
  _adapter->scanKeyCallback(_row, _column, reading, prevReading);
  matrix.setData(_row, _column, reading);
  
  _row++; // Next Key in column
  if(_row >= _nRows) { // Next Column
    digitalWrite(columnPin(_column), HIGH);
    pinMode(columnPin(_column), INPUT_PULLUP);
    _column++;
    pinMode(columnPin(_column), OUTPUT);
    digitalWrite(columnPin(_column), LOW);
    _row = 0;
    
    if(_column >= _nColumns) { // End of matrix scan
      _adapter->scanEndCallback(&matrix);
      _column = 0;
    }
  }
};
#endif

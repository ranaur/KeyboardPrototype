#include "MatrixKeyboard.h"

MatrixKeyboard::MatrixKeyboard(uint8_t nRows, uint8_t nColumns) : 
    _nRows(nRows), 
    _nColumns(nColumns), 
    _DownEventCallback((void (*)(MatrixKeyboard *, uint8_t, uint8_t, void*))0),
    _UpEventCallback((void (*)(MatrixKeyboard *, uint8_t, uint8_t, void*))0),
    _CycleEndEventCallback((void (*)(MatrixKeyboard *, void*))0),
    _row(0), 
    _column(0) {
  uint16_t nElements = (uint16_t)nRows * (uint16_t)nColumns;
  matrixRC = (uint8_t *)malloc((nElements / (uint16_t)8) + (uint16_t)1);

  debounceHandlers = (Debounce **)malloc(nElements * sizeof(Debounce *));
  for (int i=0; i < nElements; i++) {
    debounceHandlers[i] = new Debounce();
  }
};


void MatrixKeyboard::setup(const uint8_t *rowPins, const uint8_t *columnPins) {
  _rowPins = rowPins;
  _columnPins = columnPins;

  // Setup pins
  for(uint8_t r = 0; r < _nRows; r++) {
    pinMode(rowPin(r), INPUT_PULLUP);
  }

  for(uint8_t c = 0; c < _nColumns; c++) {
    pinMode(columnPin(c), INPUT_PULLUP);
  }
}

void MatrixKeyboard::loop(void *obj) {
  bool reading = digitalRead(rowPin(_row)) == HIGH ? true : false;
  bool prevReading = getRC(_row, _column);
  if(reading != prevReading) {
    if(reading) {
      if(_DownEventCallback) _DownEventCallback(this, _row, _column, obj);
    } else {
      if(_UpEventCallback) _UpEventCallback(this, _row, _column, obj);
    }
    setRC(_row, _column, reading);  
  }

  // Next Key
  _row++;
  if(_row >= _nRows) {
    // Next Column
    digitalWrite(columnPin(_column), HIGH);
    pinMode(columnPin(_column), INPUT_PULLUP);
    _column++;
    pinMode(columnPin(_column), OUTPUT);
    digitalWrite(columnPin(_column), LOW);
    _row = 0;
    
    _column++;
    if(_column>= _nColumns) {
      // End of matrix scan
      if(_CycleEndEventCallback) _CycleEndEventCallback(this, obj);
    }
  }
}

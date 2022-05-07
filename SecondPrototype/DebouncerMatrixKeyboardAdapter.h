#ifndef DEBOUNCER_MKA_H
#define DEBOUNCER_MKA_H

#include "MatrixKeyboard.h"

#define DEBOUNCE_DELAY (unsigned long)50

template <uint8_t nRows, uint8_t nColumns> class DebouncerMatrixKeyboardAdapter : public MatrixKeyboardAdapter<nRows, nColumns> {
  public:
    DebouncerMatrixKeyboardAdapter() {};
  
    void scanKeyCallback(uint8_t row, uint8_t column, bool value, bool prevValue) {
      if (value != prevValue) {
        debouncedTimes.setData(row, column, millis());
        return;
      }
    
      if (millis() > debouncedTimes.getData(row, column) + DEBOUNCE_DELAY) {
        _adapter->scanKeyCallback(row, column, value, matrix.getData(row, column));
        matrix.setData(row, column, value);
      }
    }
    
    void scanEndCallback(MatrixDataType *bdata) {
      _adapter->scanEndCallback(&matrix);
    }
    void setAdapter(MatrixKeyboardAdapter<nRows, nColumns> *adapter) { _adapter = adapter; };

  private:
    MatrixKeyboardAdapter<nRows, nColumns> *_adapter;
    BidimensionalData<unsigned long, nRows, nColumns> debouncedTimes;
    MatrixDataType matrix;

};

#endif

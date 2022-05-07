#ifndef TRANSITION_MKA_H
#define TRANSITION_MKA_H

#include "MatrixKeyboard.h"

template <uint8_t nRows, uint8_t nColumns> class TransitionMatrixKeyboardAdapter : public MatrixKeyboardAdapter<nRows, nColumns> {
  public:
    TransitionMatrixKeyboardAdapter() : _changed(false) {};
  
    void scanKeyCallback(uint8_t row, uint8_t column, bool value, bool prevValue) {
      if(value != prevValue) {
        _adapter->scanKeyCallback(row, column, value, prevValue);
        _changed = true;
      }
    }
    
    void scanEndCallback(MatrixDataType *bdata) {
      if(_changed) {
        _changed = false;
        _adapter->scanEndCallback(bdata);
      }
    }

    void setAdapter(MatrixKeyboardAdapter<nRows, nColumns> *adapter) { _adapter = adapter; };
  private:
    MatrixKeyboardAdapter<nRows, nColumns> *_adapter;
    bool _changed;
};

#endif

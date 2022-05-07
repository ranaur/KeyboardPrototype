#ifndef BIDIMENSIONAL_H
#define BIDIMENSIONAL_H

template <typename T, uint8_t nRows, uint8_t nColumns> class BidimensionalData {
  private:
  T _data[nRows][nColumns];
  public:
  MatrixKeyboardData() { memset((byte *)_data, '\0', sizeof(_data) / sizeof(_data[0][0])); };
  T getData(uint8_t row, uint8_t column) { return _data[row][column]; };
  void setData(uint8_t row, uint8_t column, T value) { _data[row % nRows][column % nColumns] = value; };
  void setAll(T value) {
    for(int row = 0; row < nRows; row++) {
      for(int col = 0; col < nColumns; col++) {
        setData(row, col, value);
      }
    }
  }
};

template <uint8_t nRows, uint8_t nColumns> class BidimensionalBitfield {
  private:
  uint8_t _data[((nRows * nColumns - 1)/ sizeof(uint8_t)) + 1];
  public:
  MatrixKeyboardData() { memset((byte *)_data, '\0', sizeof(_data) / sizeof(_data[0][0])); };
  bool getData(uint8_t row, uint8_t column) { 
    uint16_t pos = (row % nRows) * nColumns + (column % nColumns);
    return _data[pos / sizeof(uint8_t)] >> (pos % sizeof(uint8_t)) & 0x01 == 0x01;
  };
  void setData(uint8_t row, uint8_t column, bool value) { 
    uint16_t pos = (row % nRows) * nColumns + (column % nColumns);
    uint8_t bitMask = 0x01 << (pos % 8);
    if(value) {
      _data[pos / 8] |= bitMask;
    } else {
      _data[pos / 8] &= ~bitMask;
    }
  };
};

#endif

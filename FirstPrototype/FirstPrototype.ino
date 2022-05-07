#include "USBKeycodeKeyboard.h"

//#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define debug(a) { Serial.print(a); }
#define debugln(a) { Serial.println(a); }
#else
#define debug(a)
#define debugln(a)
#endif

typedef int8_t pin_t;
typedef int state_t;

unsigned long debounceDelay = 50;

const pin_t columnsPins[] = { 7, 6, 5 };
const int8_t nColumns = sizeof(columnsPins) / sizeof(pin_t);

const pin_t rowsPins[] = { 11, 10, 9, 8 };
const int8_t nRows = sizeof(rowsPins) / sizeof(pin_t);

const uint8_t rowColumnMappings[nRows][nColumns] = {
  { KEY_KP1, KEY_KP2, KEY_KP3 }, 
  { KEY_KP4, KEY_KP5, KEY_KP6 }, 
  { KEY_KP7, KEY_KP8, KEY_KP9 }, 
  { KEY_LEFTALT, KEY_KP0, KEY_KPENTER }
};

state_t rowColumnDebouncingState[nRows][nColumns];
state_t rowColumnState[nRows][nColumns];
unsigned long rowColumnDebouncingTime[nRows][nColumns];

USBKeycodeKeyboard driver;

const uint8_t rowColumnMap(int row, int column) {
  return rowColumnMappings[row][column];
}

int8_t columnPin(int index) {
  while(index < 0) index += nColumns;
  return columnsPins[index % nColumns];
}

int8_t rowPin(int index) {
  while(index < 0) index += nRows;
  return rowsPins[index % nRows];
}

void setup() {
  
#ifdef DEBUG
  Serial.begin(9600);

  // Wait for USB Serial (Leonardo)
  while (!Serial) {
    yield();
  }
#endif

  // Initialize state
  for(int c = 0; c < nColumns; c++) {
    for(int r = 0; r < nRows; r++) {
      rowColumnState[r][c] = HIGH;
      rowColumnDebouncingState[r][c] = HIGH;
      rowColumnDebouncingTime[r][c] = 0;
    }
  }
}

void loop() {
  // Re-intialize the row pins. Allows sharing these pins with other hardware.
  for(int c = 0; c < nColumns; c++) {
    pinMode(columnPin(c), OUTPUT);
    digitalWrite(columnPin(c), HIGH);
    pinMode(columnPin(c), INPUT_PULLUP);
  }
  for(int r = 0; r < nRows; r++) {
    pinMode(rowPin(r), INPUT_PULLUP);
  }

  for(int c = 0; c < nColumns; c++) {
    pinMode(columnPin(c), OUTPUT);
    digitalWrite(columnPin(c), LOW);

    for(int r = 0; r < nRows; r++) {
      int reading = digitalRead(rowsPins[r]);
      
      // debouncing
      if (reading != rowColumnDebouncingState[r][c]) {
        // reset the debouncing timer
        rowColumnDebouncingTime[r][c] = millis();
      }

      if ((millis() - rowColumnDebouncingTime[r][c]) > debounceDelay) {
        if (reading != rowColumnState[r][c]) {
          rowColumnState[r][c] = reading;
          if(reading == LOW) {
            rowColumnDown(r, c);
          } else {
            rowColumnUp(r, c);
          }
        }
      }

      rowColumnDebouncingState[r][c] = reading;
      
    }
    digitalWrite(columnPin(c), HIGH);
    pinMode(columnPin(c), INPUT);
  }
}

void rowColumnDown(int row, int column) {
  Serial.print("DOWN: ");
  Serial.println(rowColumnMap(row, column), HEX);
  driver.press(rowColumnMap(row, column));
  driver.send();
}

void rowColumnUp(int row, int column) {
  Serial.print("UP: ");
  Serial.println(rowColumnMap(row, column), HEX);
  driver.release(rowColumnMap(row, column));
  driver.send();
}

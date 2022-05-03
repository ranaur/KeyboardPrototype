#include "Keyboard.h"

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

const char *rowColumnMappings[nRows][nColumns] = {
  { "1", "2", "3" }, 
  { "4", "5", "6" }, 
  { "7", "8", "9" }, 
  { "*", "0", "#" }
};

state_t rowColumnDebouncingState[nRows][nColumns];
state_t rowColumnState[nRows][nColumns];
unsigned long rowColumnDebouncingTime[nRows][nColumns];

const char *rowColumnMap(int row, int column) {
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

  // Setup pins
  for(int c = 0; c < nColumns; c++) {
    pinMode(columnPin(c), OUTPUT);
    digitalWrite(columnPin(c), HIGH);
  }
  for(int r = 0; r < nRows; r++) {
    pinMode(rowPin(r), INPUT_PULLUP);
  }

  // Initialize state
  for(int c = 0; c < nColumns; c++) {
    for(int r = 0; r < nRows; r++) {
      rowColumnState[r][c] = HIGH;
      rowColumnDebouncingState[r][c] = HIGH;
      rowColumnDebouncingTime[r][c] = 0;
    }
  }

  Keyboard.begin();
}

void loop() {
  //debugln("NEW LOOP");
  for(int c = 0; c < nColumns; c++) {
    digitalWrite(columnPin(c - 1), HIGH);
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
  }
}

void rowColumnDown(int row, int column) {
  const char *keyText = rowColumnMap(row, column);

  debug("DOWN ");
  
  for(int i = 0; keyText[i] != '\0'; i++) {
    Keyboard.press(keyText[i]);
    debug(keyText[i]);
  }
  debugln("");  
}

void rowColumnUp(int row, int column) {
  const char *keyText = rowColumnMap(row, column);

  debug("UP ");
  
  for(int i = 0; keyText[i] != '\0'; i++) {
    Keyboard.release(keyText[i]);
    debug(keyText[i]);
  }
  debugln("");  
}

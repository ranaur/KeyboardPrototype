#include "Debounce.h"
#include "arduino.h"

unsigned long debounceDelay = 50;

bool Debounce::ok(bool reading) {
  if (reading != _state) {
    _debounceTime = millis();
    return false;
  }

  if ((millis() - _debounceTime) <= debounceDelay) {
    return false;
  }
  return true;
}

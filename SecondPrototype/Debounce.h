#ifndef DEBOUNCE_H
#define DEBOUNCE_H

class Debounce {
  public:
    Debounce() : _state(false), _debounceTime(0) {};
    bool ok(bool reading);
    
  private:
    bool _state;
    unsigned long _debounceTime;
};

extern unsigned long debounceDelay;
#endif

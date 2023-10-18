#ifndef XBelt_h
#define XBelt_h

#include "Arduino.h"

class XBelt
{
public:
  XBelt(int pin, unsigned long holdTime = 2500);
  void begin();
  void update();
  void onPress(void (*function)());
  void onRelease(void (*function)());

protected:
  int _pin;
  unsigned long _holdTime;
  unsigned long _pressTime;
  unsigned long _replaseTime;
  unsigned long _lastDebounceTime;
  bool _isPress;
  int _lastState;

private:
  void (*_onPressFunction)();
  void (*_onReleaseFunction)();
};

#endif

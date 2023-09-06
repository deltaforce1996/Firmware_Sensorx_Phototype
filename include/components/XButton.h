#ifndef XButton_h
#define XButton_h

#include "Arduino.h"

class XButton
{
public:
  XButton(int pin, unsigned long holdTime = 50);
  void begin();
  void update();
  void onPress(void (*function)());
  void onRelease(void (*function)());

protected:
  int _pin;
  bool _lastState;
  bool _isPress;

  unsigned long _pressTime;
  unsigned long _holdTime;

  void (*_onPressFunction)();
  void (*_onReleaseFunction)();
};
#endif

#ifndef XButton_h
#define XButton_h

#include "Arduino.h"

class XButton
{
public:
  XButton(int pin, unsigned long holdTime = 50);
  void begin();
  virtual void update();
  virtual void onPress(void (*function)());
  virtual void onRelease(void (*function)());

protected:
  int _pin;
  unsigned long _holdTime;
  unsigned long _pressTime;
  unsigned long _lastDebounceTime;
  bool _isPress;
  int _lastState;

private:
  void (*_onPressFunction)();
  void (*_onReleaseFunction)();
};
#endif

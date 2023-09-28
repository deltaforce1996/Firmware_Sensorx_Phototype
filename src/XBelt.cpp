#include "./components/XBelt.h"
#include "./components/XButton.h"

XBelt::XBelt(int pin) : XButton(pin, 2500) {}

void XBelt::update()
{
  bool currentState = !digitalRead(_pin);
  if (currentState != _lastState)
  {
    if (currentState == LOW)
    {
      _pressTime = millis();
    }
    else
    {
      _pressTime = 0;
      if (_onReleaseFunction != NULL && _isPress)
      {
        _onReleaseFunction();
        _isPress = false;
      }
    }
    _lastState = currentState;
  }

  if (currentState == LOW && _pressTime > 0 && millis() - _pressTime >= _holdTime && _onPressFunction != NULL)
  {
    _onPressFunction();
    _pressTime = 0;
    _lastState = currentState;
    _isPress = true;
  }
}

void XBelt::onPress(void (*function)())
{
  _onPressFunction = function;
}

void XBelt::onRelease(void (*function)())
{
  _onReleaseFunction = function;
}
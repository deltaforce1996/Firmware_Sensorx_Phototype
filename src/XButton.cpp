#include "./components/XButton.h"

XButton::XButton(int pin, unsigned long holdTime)
{
  _pin = pin;
  _lastState = HIGH;
  _onPressFunction = NULL;
  _onReleaseFunction = NULL;
  _pressTime = 0;
  _holdTime = holdTime;
  _isPress = false;
}

void XButton::begin()
{
  pinMode(_pin, INPUT_PULLUP);
}

void XButton::update()
{
  bool currentState = digitalRead(_pin);
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
        _isPress = false;
        _onReleaseFunction();
      }
    }
    _lastState = currentState;
  }
  else if (currentState == LOW && _pressTime > 0 && millis() - _pressTime >= _holdTime && _onPressFunction != NULL)
  {
    _isPress = true;
    _onPressFunction();
    _pressTime = 0;
    _lastState = currentState;
  }
}

void XButton::onPress(void (*function)())
{
  _onPressFunction = function;
}

void XButton::onRelease(void (*function)())
{
  _onReleaseFunction = function;
}

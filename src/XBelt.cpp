#include "./components/XBelt.h"

XBelt::XBelt(int pin, unsigned long holdTime)
{
  _pin = pin;
  _lastState = LOW;
  _onPressFunction = NULL;
  _onReleaseFunction = NULL;
  _pressTime = 0;
  _replaseTime = 0;
  _holdTime = holdTime;
  _isPress = true;
}

void XBelt::begin()
{
  pinMode(_pin, INPUT_PULLUP);
}

void XBelt::update()
{
  bool currentState = !digitalRead(_pin);
  if (currentState != _lastState)
  {
    if (currentState == LOW)
    {
      _pressTime = millis();
      // Serial.print("_pressTime : ");
      // Serial.print(_pressTime);
      // Serial.println();
      _replaseTime = 0;
    }
    else
    {
      _pressTime = 0;
      // Serial.print("_replaseTime : ");
      // Serial.print(_replaseTime);
      // Serial.println();
      _replaseTime = millis();
    }
    _lastState = currentState;
  }

  if (currentState == HIGH && _replaseTime > 0 && millis() - _replaseTime > 500 && _onReleaseFunction != NULL && _isPress)
  {
    _onReleaseFunction();
    _replaseTime = 0;
    _isPress = false;
  }

  if (currentState == LOW && _pressTime > 0 && millis() - _pressTime >= _holdTime && _onPressFunction != NULL && !_isPress)
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
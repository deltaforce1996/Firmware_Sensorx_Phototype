#include "./components/XSeat.h"

XSeat::XSeat(int pin, int distanceThreshold)
{
  _pin = pin;
  _startTime = 0;
  _distanceThreshold = distanceThreshold;
  _isSeated = false;
  _onSeatFunction = NULL;
  _onUnSeatFunction = NULL;
}

void XSeat::begin()
{
  pinMode(_pin, INPUT);
}

void XSeat::checkSeat()
{
  long distance = getDistance();
  unsigned long now = millis();
  if (!_isSeated && distance < _distanceThreshold)
  {
    if (_startTime == 0)
    {
      _startTime = now;
    }
    else if (now - _startTime >= HOLD_TIME && _onSeatFunction != NULL)
    {
      _onSeatFunction();
      _isSeated = true;
      _startTime = 0;
    }
  }
  else if (_isSeated && distance >= _distanceThreshold && _onUnSeatFunction != NULL)
  {
    _onUnSeatFunction();
    _isSeated = false;
  }
  else
  {
    _startTime = 0;
  }
}

long XSeat::getDistance()
{
  long duration = pulseIn(_pin, HIGH);
  long distance = (duration / 2) / 29.1;
  return distance;
}

void XSeat::onSeat(void (*function)())
{
  _onSeatFunction = function;
}

void XSeat::onUnSeat(void (*function)())
{
  _onUnSeatFunction = function;
}

void XSeat::reset()
{
  _isSeated = false;
}

#include "./components/XSeat.h"

XSeat::XSeat(int pin, int distanceThreshold)
{
  _pin = pin;
  _startTime = 0;
  _unsetTime = 0;
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
  if (distance == -1)
    return;

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
  else if (_isSeated && distance >= _distanceThreshold)
  {
    if (_unsetTime == 0)
    {
      _unsetTime = now;
    }
    else if (now - _unsetTime >= 2000 && _onUnSeatFunction != NULL)
    {
      _onUnSeatFunction();
      _isSeated = false;
      _unsetTime = 0;
    }
  }
  else
  {
    _startTime = 0;
    _unsetTime = 0; // Reset the unseat timer if the condition is not met
  }
}

long XSeat::getDistance()
{
  // noInterrupts();
  long duration = pulseIn(_pin, HIGH, 100000);
  if (duration != 0)
  {
    long distance = duration / 100;
    // interrupts();
    return distance;
  }
  else
  {
    // interrupts();
    return -1;
  }
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

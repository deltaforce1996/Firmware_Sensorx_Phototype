#ifndef XSeat_h
#define XSeat_h

#include "Arduino.h"

class XSeat
{
public:
  XSeat(int pin, int distanceThreshold);
  void begin();
  void checkSeat();
  long getDistance();
  void onSeat(void (*function)());
  void onUnSeat(void (*function)());
  void reset();

private:
  int _pin;
  unsigned long _startTime;
  int _distanceThreshold;
  bool _isSeated;
  void (*_onSeatFunction)();
  void (*_onUnSeatFunction)();
  const unsigned long HOLD_TIME = 1000;
};

#endif

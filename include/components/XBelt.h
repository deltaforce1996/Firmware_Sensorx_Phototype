#ifndef XBelt_h
#define XBelt_h

#include "Arduino.h"
#include "components/XButton.h"

class XBelt : public XButton
{
public:
  XBelt(int pin);
  void update() override;
  void onPress(void (*function)()) override;
  void onRelease(void (*function)()) override;

private:
  void (*_onPressFunction)();
  void (*_onReleaseFunction)();
};

#endif

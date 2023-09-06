#ifndef XBelt_h
#define XBelt_h

#include "Arduino.h"
#include "components/XButton.h"

class XBelt : public XButton
{
public:
  XBelt(int pin);
};

#endif



#include <Arduino.h>
#include "components/XSeat.h"
#include "components/XBelt.h"
#include "components/XButton.h"

const int PIN_SEAT_LEFT = 2;
const int PIN_SEAT_RIGHT = 3;
const int PIN_BELT_LEFT = 7;
const int PIN_BELT_RIGHT = 5;
const int BUTTON_START = 8;
const int BUTTON_SLOW = 9;

enum Section
{
  DEFAULT_STATE,
  PAYMENT,
  BELT,
  SEAT,
  BUTTON
};

XSeat xSeatLeft(PIN_SEAT_LEFT, 90);
XSeat xSeatRight(PIN_SEAT_RIGHT, 90);
XBelt xBeltLeft(PIN_BELT_LEFT);
XBelt xBeltRight(PIN_BELT_RIGHT);
XButton xButtonStart(BUTTON_START);
XButton xButtonSlow(BUTTON_SLOW);

uint8_t xSeatLeftState = 0;
uint8_t xSeatRightState = 0;
uint8_t xBeltRightState = 0;
uint8_t xBeltLeftState = 0;
// char msg_t[4];

void sendTo(Section section, uint8_t leftData, uint8_t rightData)
{
  // memset(msg_t, 0x00, sizeof msg_t);
  // sprintf(msg_t, "%d%d%d", section, leftData, rightData);
  // Serial.println(msg_t);
  // Serial.flush();
  
  uint8_t dataToSend[3] = {section, leftData, rightData};
  Serial.write(dataToSend, 3);

  // Serial.print("Sent bytes: ");
  // for (int i = 0; i < 3; i++)
  // {
  //   Serial.print(dataToSend[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
}

void setupCallbacks()
{
  xSeatLeft.onSeat([]()
                   { xSeatLeftState = 1; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  xSeatLeft.onUnSeat([]()
                     { xSeatLeftState = 0; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  xSeatRight.onSeat([]()
                    { xSeatRightState = 1; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  xSeatRight.onUnSeat([]()
                      { xSeatRightState = 0; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  xBeltLeft.onPress([]()
                    { xBeltLeftState = 1; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  xBeltLeft.onRelease([]()
                      { xBeltLeftState = 0; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  xBeltRight.onPress([]()
                     { xBeltRightState = 1; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  xBeltRight.onRelease([]()
                       { xBeltRightState = 0; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  xButtonStart.onPress([]()
                       { sendTo(BUTTON, 0, 2); });
  xButtonSlow.onPress([]()
                      { sendTo(BUTTON, 0, 1); });
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Start firmware...........");

  xSeatLeft.begin();
  xSeatRight.begin();
  xBeltLeft.begin();
  xBeltRight.begin();
  xButtonStart.begin();
  xButtonSlow.begin();

  setupCallbacks();
}

void loop()
{
  xBeltLeft.update();
  xBeltRight.update();
  xButtonStart.update();
  xButtonSlow.update();
  xSeatLeft.checkSeat();
}

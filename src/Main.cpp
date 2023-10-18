

#include <Arduino.h>
#include "components/XSeat.h"
#include "components/XBelt.h"
#include "components/XButton.h"

#define PIN_SEAT_LEFT     2
#define PIN_SEAT_RIGHT    3
#define PIN_BELT_LEFT     7
#define PIN_BELT_RIGHT    5
#define BUTTON_START      8
#define BUTTON_SLOW       9
#define BUTTON_PLAYER     10

enum Section
{
  DEFAULT_STATE,
  PAYMENT,
  BELT,
  SEAT,
  BUTTON
};

XSeat xSeatLeft(PIN_SEAT_LEFT, 95);
XSeat xSeatRight(PIN_SEAT_RIGHT, 95);
XBelt xBeltLeft(PIN_BELT_LEFT);
XBelt xBeltRight(PIN_BELT_RIGHT);
XButton xButtonStart(BUTTON_START);
XButton xButtonPlayer(BUTTON_PLAYER);
XButton xButtonSlow(BUTTON_SLOW);

uint8_t xSeatLeftState = 0;
uint8_t xSeatRightState = 0;
uint8_t xBeltRightState = 0;
uint8_t xBeltLeftState = 0;

void sendTo(Section section, uint8_t leftData, uint8_t rightData)
{
  uint8_t dataArray[4];
  dataArray[0] = (uint8_t)section; // ใช้ byte แรกเป็น identifier สำหรับ section
  dataArray[1] = leftData;
  dataArray[2] = rightData;
  dataArray[3] = '#';

  Serial.write(dataArray, sizeof(dataArray));
  // for (int i = 0; i < 4; i++)
  // {
  //   Serial.print(dataArray[i]);
  // }
  // Serial.println();
}

void L_Seat_Set()
{
  xSeatLeftState = 1;
  sendTo(SEAT, xSeatLeftState, xSeatRightState);
}

void L_Seat_Levae()
{
  xSeatLeftState = 0;
  sendTo(SEAT, xSeatLeftState, xSeatRightState);
}

void R_Seat_Set()
{
  xSeatRightState = 1;
  sendTo(SEAT, xSeatLeftState, xSeatRightState);
}

void R_Seat_Levae()
{
  xSeatRightState = 0;
  sendTo(SEAT, xSeatLeftState, xSeatRightState);
}

void L_Fasten()
{
  xBeltLeftState = 1;
  sendTo(BELT, xBeltLeftState, xBeltRightState);
}

void L_Release()
{
  xBeltLeftState = 0;
  sendTo(BELT, xBeltLeftState, xBeltRightState);
}

void R_Fasten()
{
  xBeltRightState = 1;
  sendTo(BELT, xBeltLeftState, xBeltRightState);
}

void R_Release()
{
  xBeltRightState = 0;
  sendTo(BELT, xBeltLeftState, xBeltRightState);
}

void Start_Clicked()
{
  sendTo(BUTTON, 0, 2);
}

void Slow_Clicked()
{
  sendTo(BUTTON, 0, 1);
}

void Player_Clicked()
{
  sendTo(BUTTON, 1, 0);
}
void setupCallbacks()
{
  // xSeatLeft.onSeat([]()
  //                  { xSeatLeftState = 1; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  // xSeatLeft.onUnSeat([]()
  //                    { xSeatLeftState = 0; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  // xSeatRight.onSeat([]()
  //                   { xSeatRightState = 1; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  // xSeatRight.onUnSeat([]()
  //                     { xSeatRightState = 0; sendTo(SEAT, xSeatLeftState, xSeatRightState); });
  // xBeltLeft.onPress([]()
  //                   { xBeltLeftState = 1; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  // xBeltLeft.onRelease([]()
  //                     { xBeltLeftState = 0; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  // xBeltRight.onPress([]()
  //                    { xBeltRightState = 1; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  // xBeltRight.onRelease([]()
  //                      { xBeltRightState = 0; sendTo(BELT, xBeltLeftState, xBeltRightState); });
  // xButtonStart.onPress([]()
  //                      { sendTo(BUTTON, 0, 2); });
  // xButtonSlow.onPress([]()
  //                     { sendTo(BUTTON, 0, 1); });
  // xButtonPlayer.onPress([]()
  //                       { sendTo(BUTTON, 1, 0); });

  xSeatLeft.onSeat(L_Seat_Set);
  xSeatLeft.onUnSeat(L_Seat_Levae);

  xSeatRight.onSeat(R_Seat_Set);
  xSeatRight.onUnSeat(R_Seat_Levae);

  xBeltLeft.onPress(L_Fasten);
  xBeltLeft.onRelease(L_Release);

  xBeltRight.onPress(R_Fasten);
  xBeltRight.onRelease(R_Release);

  xButtonStart.onPress(Start_Clicked);
  xButtonSlow.onPress(Slow_Clicked);
  xButtonPlayer.onPress(Player_Clicked);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Start...");
  xSeatLeft.begin();
  xSeatRight.begin();
  xBeltLeft.begin();
  xBeltRight.begin();
  xButtonStart.begin();
  xButtonSlow.begin();
  xButtonPlayer.begin();

  setupCallbacks();
}

void loop()
{
  xBeltLeft.update();
  xBeltRight.update();
  xButtonStart.update();
  xButtonSlow.update();
  xButtonPlayer.update();
  xSeatLeft.checkSeat();
  xSeatRight.checkSeat();
}

// const int pin1 = 2;  // First sensor pin
// const int pin2 = 3;  // Second sensor pin

// unsigned long duration1;  // Duration for the first sensor
// unsigned long duration2;  // Duration for the second sensor

// void readDistance(int pin, unsigned long& duration, uint16_t& distance) {
//   duration = pulseIn(pin, HIGH);
//   distance = duration / 100;
// }

// void setup() {
//    Serial.begin(115200);
//    pinMode(pin1, INPUT);
//    pinMode(pin2, INPUT);
//    delay(100);
// }

// void loop() {
//    // Distance for the first sensor
//   uint16_t distance1 = 0;
//   uint16_t distance2 = 0;
//   readDistance(pin1, duration1, distance1);  // Read distance for the first sensor

//   readDistance(pin2, duration2, distance2);  // Read distance for the second sensor

// //    // Print the distances in the Serial Monitor
// //  Serial.print("Distance 1: ");
// //  Serial.print(distance1);
// //  Serial.print(" cm\tDistance 2: ");
// //  Serial.print(distance2);
// //  Serial.println(" cm");

//     // Send the distances to the Raspberry Pi via USB serial
//   Serial.print(distance1);
//   Serial.print(",");
//   Serial.println(distance2);

//   delay(50);

// }

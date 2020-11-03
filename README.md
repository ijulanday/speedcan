# speedcan

A library for use with Currawong Velocity ESC and their Velocity SDK to be ran on Teensy 4.x

## example program
```c
#include "speedcan.h"
#include <Metro.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;


Metro statusUpdate = Metro(2000);
Metro blink = Metro(1000);

char led_status = 0;

//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  can1.begin();
  can1.setBaudRate(1000000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}
 
void loop()
{
  if (can1.read(message_speedcan))
    incomingMessageHandler();
  if (blink.check()) {
    led_status ^= 0x1;
    digitalWrite(LED_BUILTIN, led_status);
  }

  if (statusUpdate.check())
    printStatus();
}
```

## dependancies
*   velocity_sdk_v3 (not on GitHub, contact Currawong or regional distributor)
*   [FlexCAN_T4](https://github.com/tonton81/FlexCAN_T4/)
*   Arduino
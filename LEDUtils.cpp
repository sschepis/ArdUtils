#include <Arduino.h>

void led_blink(int LEDpin, int onMS, int offMS, int loops) {
  for (uint8_t i=0; i<loops; i++)  {
    digitalWrite(LEDpin, HIGH);
    delay(onMS);
    digitalWrite(LEDpin, LOW);
    delay(offMS);
  }
}

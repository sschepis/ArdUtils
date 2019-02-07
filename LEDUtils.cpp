void led_blink(byte LEDpin, byte onMS, byte offMS, byte loops) {
  for (byte i=0; i<loops; i++)  {
    digitalWrite(LEDpin, HIGH);
    delay(onMS);
    digitalWrite(LEDpin, LOW);
    delay(offMS);
  }
}


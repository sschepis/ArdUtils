#ifndef ARD__UTILS_H
#define ARD__UTILS_H

#include <Arduino.h>

void initAndWaitForSerial(uint16_t baud = 115200, uint16_t timeout = 1000, uint16_t _delay = 1) {
	Serial.begin(baud);
	uint16_t t = 0;
	while(!Serial) {
		if(t >= timeout) break;
		delay(_delay);
		t += _delay;
	}
}
#endif

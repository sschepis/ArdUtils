#ifndef SERIAL__UTILS_H
#define SERIAL__UTILS_H

#define SP(message) Serial.print(message)
#define SPL(message) Serial.println(message)
#define SPS Serial.print(" ");
#define SPN Serial.println("");

void initAndWaitForSerial(uint16_t baud = 115200, uint16_t timeout = 1000, uint16_t _delay = 1) {
	Serial.begin(baud);
	uint32_t t = 0, nowTime = millis();
	while(!Serial) {
		if(t >= timeout) break;
		delay(_delay);
		t += _delay;
	}
    uint32_t endTime = millis() - nowTime;
    SP("Serial interface started in "); SP(endTime); SPL(" milliseconds");
}
#endif

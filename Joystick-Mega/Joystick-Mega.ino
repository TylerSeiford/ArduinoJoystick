#include <Wire.h>

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Wire.begin();					// join i2c bus (address optional for master)
	Serial.begin(9600);				// start serial for output
}

void loop() {
	Serial.println("Requesting data...");
	print(getData());

	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
	delay(500);
}

uint64_t getData() {
	uint64_t data = 0;
	uint8_t count = 7;
	uint8_t temp = 0;

	Wire.requestFrom(250, 6);		// request 6 bytes from slave device #250

	while (Wire.available()) {
		temp = Wire.read();
		data += uint64_t(temp) << 8 * count;
		count--;
	}

	return data;
}

void print(uint64_t data) {
	for (uint8_t i = 63; i > 0; i--) {
		if (data & uint64_t(1) << i) {
			Serial.print(1);
		}
		else {
			Serial.print(0);
		}
	}

	if (data & 1) {
		Serial.println(1);
	}
	else {
		Serial.println(0);
	}
}
#include <Wire.h>

#include "Button.h"
#include "JoystickWrapper.h"

constexpr uint8_t BUTTON_NUM = 8;
constexpr uint8_t BUTTON_MAP[BUTTON_NUM] = {
	 4,  5,  6,  7,  8,  9,  10,  11
};

Joystick* stick0, * stick1, * stick2, * stick3;
Button* b0, * b1, * b2, * b3, * b4, * b5, * b6, * b7, * b8, * b9, * b10;

void setup() {
	//Initialize pins as inputs with pullups
	for (uint8_t i = 0; i < BUTTON_NUM; i++) {
		pinMode(BUTTON_MAP[i], INPUT_PULLUP);
	}

	pinMode(LED_BUILTIN, OUTPUT);

	stick0 = new Joystick;
	stick1 = new Joystick(0x4);
	stick2 = new Joystick(0x5);
	stick3 = new Joystick(0x6);

	stick0->begin();
	stick1->begin();
	stick2->begin();
	stick3->begin();

	Wire.begin();					// join i2c bus (address optional for master)
	//Serial.begin(9600);				// start serial for output

	stick0->setAxis(0, -32000);
	stick0->setAxis(1, -32000);
	stick1->setAxis(0, -32000);
	stick1->setAxis(1, 32000);
	stick2->setAxis(0, 32000);
	stick2->setAxis(1, 32000);
	stick3->setAxis(0, 32000);
	stick3->setAxis(1, -32000);
}

void loop() {
	Serial.println("Requesting data...");
	updateButtons();
	updateAxis();

	stick0->sendState();
	stick1->sendState();
	stick2->sendState();
	stick3->sendState();

	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

	delay(500);
}

void updateAxis() {
	int16_t temp = (64 * int16_t(analogRead(0))) - 32768;

	for (uint8_t i = 2; i < 7; i++) {
		stick0->setAxis(i, temp);
		stick1->setAxis(i, temp);
		stick2->setAxis(i, temp);
		stick3->setAxis(i, temp);
	}
}

void updateButtons() {
	uint64_t data = getButtons();
	print(data);
	update(data);
}

uint64_t getButtons() {
	uint64_t data = getData();
	data = data >> 16;
	for (uint8_t i = 63; i >= 63 - BUTTON_NUM; i--) {
		data += uint64_t(!digitalRead(BUTTON_MAP[63 - i])) << i;
	}
	return data;
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

void update(uint64_t data) {
	for (uint8_t i = 63; i > 0; i--) {
		if (data & uint64_t(1) << i) {
			setButton(63 - i, 1);
		}
		else {
			setButton(63 - i, 0);
		}
	}
}

void setButton(uint8_t button, uint8_t value) {
	if (button / 16 == 0) {
		stick0->setButton(button % 16, value);
	}
	else if (button / 16 == 1) {
		stick1->setButton(button % 16, value);
	}
	else if (button / 16 == 2) {
		stick2->setButton(button % 16, value);
	}
	else if (button / 16 == 3) {
		stick3->setButton(button % 16, value);
	}
}
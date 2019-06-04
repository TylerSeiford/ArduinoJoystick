#include "Button.h"
#include "JoystickWrapper.h"

constexpr uint16_t DELAY = 250;

Joystick* stick;
Button* button;


void setup() {
	stick = new Joystick;
	button = new Button(12, stick, 0);
	stick->begin();
}

void loop() {
	int16_t temp = (64 * int16_t(analogRead(0))) - 32768;
	stick->setAxis(2, temp);
	stick->setAxis(3, temp);
	stick->setAxis(4, temp);
	stick->setAxis(5, temp);
	stick->setAxis(6, temp);
	stick->sendState();
	button->update();
}

/*void loop() {
	uint16_t state = 0;
	uint8_t i = 0, j = 0;
	if (state == DELAY * 3) {
		stick->setAxis(i, 0.0);
		stick->releaseButton(j);
		stick->sendState();

		state = 0;
		i = (i + 1) % 7;
		j = (j % 15) + 1;
	}
	else if (state == DELAY * 2) {
		stick->setAxis(i, -1.0);
		stick->sendState();

		state++;
	}
	else if (state == DELAY) {
		stick->setAxis(i, 1.0);
		stick->pressButton(j);
		stick->sendState();

		state++;
	}
	else {
		state++;
	}

	button->update();
	delay(1);
}//*/
#include "JoystickWrapper.h"

class Button {
public:
	Button(uint8_t pin, Joystick* stick, uint8_t button) : pin(pin), stick(stick), button(button) {
		pinMode(pin, INPUT_PULLUP);
	}

	void inline update() {
		stick->setButton(button, !digitalRead(pin));
	}
private:
	uint8_t pin, button;
	Joystick* stick;
};
#pragma once
#include "Joystick.h"

class Joystick : public Joystick_ {
public:
	Joystick() : Joystick_(
		0x03,	//HID
		0x05,	//Joystick type (gamepad)
		16,		//Button count
		0,		//POV hat count
		true,	//X axis
		true,	//Y axis
		true,	//Z axis
		true,	//Rx axis
		true,	//Ry axis
		true,	//Rz axis
		false,	//Rudder axis
		true,	//Throttle axis
		false,	//Accelerator axis
		false,	//Brake axis
		false	//Steering axis
	) {
		setXAxisRange(-32768, 32767);
		setYAxisRange(-32768, 32767);
		setZAxisRange(-32768, 32767);
		setRxAxisRange(-32768, 32767);
		setRyAxisRange(-32768, 32767);
		setRzAxisRange(-32768, 32767);
		setThrottleRange(-32768, 32767);
	}

	inline void begin() {
		Joystick_::begin(false);
	}

	inline void setAxis(uint8_t axis, double value) {
		setAxis(axis, int16_t(value * 32767));
	}

	inline void setAxis(uint8_t axis, int16_t value) {
		if (axis == 0) {
			setXAxis(value);
		}
		else if (axis == 1) {
			setYAxis(value);
		}
		else if (axis == 2) {
			setZAxis(value);
		}
		else if (axis == 3) {
			setRxAxis(value);
		}
		else if (axis == 4) {
			setRyAxis(value);
		}
		else if (axis == 5) {
			setRzAxis(value);
		}
		else if (axis == 6) {
			setThrottle(value);
		}
	}
};
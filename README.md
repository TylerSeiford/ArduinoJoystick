# ArduinoJoystick
This project emulates four joysticks using the [ArduinoJoystickLibrary
](https://github.com/MHeironimus/ArduinoJoystickLibrary).  It utilizes two Arduinos to have 64 digital button inputs and currently supports 6 analog axis inputs.

# Hardware
Any 32u4 based arduino should work for the Joystick-Micro project, but I recommend using a pro micro.
The Joystick-Mega project will require an Arduino Mega, and communicates to the Micro using I2C.

# I2C protocol
This project uses the Micro as a master and the Mega as a slave.  The Mega sends 6 bytes for the 43 digital inputs, starting at the lowest numbered input and up to the highest button, with trailing zeros for the rest of the bytes.  The Micro then reads the 6 bytes into a 64 bit unsigned integer, shifts the results down, and then reads 8 inputs into the top of the unsigned integer.  The Micro then transfers the data into the buffer of the joysticks and sends the state of them to the computer.
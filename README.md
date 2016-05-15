# Rudder Pedals
Joystick aviation pedals controller via atmega (Arduino) + magnetometer.
Requires Arduino library 1.6.9 or later - using new HID features.

You will need:
- Arduiuno pro micro (or clone)
- HMC5883L (GY-271)
- Avia simulation pedals

For this sketch to successfully compile, you will need to do the following:
- get HMC5883L.cpp, HMC5883L.h, I2Cdev.cpp, I2Cdev.h files from repository: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/
- Place above files in the same folder as the main sketch (or add as external libraries /untested/)


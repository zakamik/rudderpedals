# Rudder Pedals
Joystick aviation pedals controller via atmega (Arduino) + magnetometer.

You will need:
- Arduiuno pro micro (or clone)
- HMC5883L (GY-271)
- Avia simulation pedals

For this sketch to successfully compile, you will need to do the following:
1. get HMC5883L.cpp, HMC5883L.h, I2Cdev.cpp, I2Cdev.h files from repository: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/
2. Modify HID.cpp & USBAPI.h in Arduino folder according to further instructions

# HUG/AR Goggles

This headset enables the overlay of information on top of its user's field of view. The field of view of the user is captured by a camera and then fed to video goggles, while a MAX7456 OSD chip overlays text on the video feed. The front camera has been chosen to be sensitive to near infrared light, which allows the device to be used as night vision goggles when paired with IR projectors Additionally, the video input source can be changed to any composite signal, which allows for example the user to see from a drone's camera or to use a raspberry pi hands free.

More info on https://cms.maximemoreillon.com/articles/155

## Video:
[![Alt text](https://img.youtube.com/vi/jYXiF9gdmnc/0.jpg)](https://www.youtube.com/watch?v=jYXiF9gdmnc)

## Requirements

* [MPU-6050 Library](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
* HMC5883L library
* [Mirf NRF24L01 library](https://github.com/aaronds/arduino-nrf24l01/tree/master/Mirf)

## Hardware
### Parts list

* Video glasses
* Mini camera with night vision capabilities
* Arduino pro mini 5V
* MPU-6050 Accelerometer and gryo combo
* HMC5883L Magnetometer
* NRF24L01+ wireless transciever
* MAX7456 OSD generator
* 2x DC-DC buck converter
* 2x 14500 Lithium-ion batteries

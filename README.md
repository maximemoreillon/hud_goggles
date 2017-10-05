# HUG Goggles

This headset enables the overlay of information on top of its user's field of view. The field of view of the user is captured by a camera and then fed to video goggles, while a MAX7456 OSD chip overlays text on the video feed. The front camera has been chosen to be sensitive to near infrared light, which allows the device to be used as night vision goggles when paired with IR projectors Additionally, the video input source can be changed to any composite signal, which allows for example the user to see from a drone's camera or to use a raspberry pi hands free.

## Video:
[![Alt text](https://img.youtube.com/vi/jYXiF9gdmnc/0.jpg)](https://www.youtube.com/watch?v=jYXiF9gdmnc)

## Parts list

* Video glasses
* Mini camera with night vision capabilities
* Arduino pro mini 5V (?)
* MPU-6050 Accelerometer and gryo combo
* HMC5883L Magnetometer
* NRF24L01+ wireless transciever
* MAX7456 OSD generator
* 2x DC-DC buck converter
* 2x 14500 Lithium-ion batteries

## Schematic:
![alt text](https://moreillon.duckdns.org/projects/images/arg_schem.png)

Note: Some resistors are missing around the MAX7456
Note 2: Some resistor values are likely to be erroneous


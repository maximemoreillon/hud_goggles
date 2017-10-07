// Libraries
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <HMC5883L.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// Timing
#define dispPeriod 50 // default 50
#define sensorPeriod 50
#define TX_PERIOD 50
#define RX_PERIOD 10
#define messageTime 1000
#define RX_TIMEOUT_TRACKER 20000
#define RX_TIMEOUT_MOTION 30000
#define RX_TIMEOUT_RIFLE 20000
#define MOTION_TIMEOUT 5000
#define DEBOUNCE_DELAY 50

// Pin mapping
#define MAX7456CS 10
#define batPin A0
#define switchPin 3
#define buttonPin 4
#define triggerPin 5


// Modes
#define MAIN_MODES 4
#define AUX_MODES 3

#define MAIN_IN 0
#define AUX_IN 1

#define STANDARD 0
#define TRACKER 1
#define MOTION 2
#define INFO 3

#define OSDOFF 0
#define SENTRY 1
#define RIFLE 2

// Misc
#define HIGHBAT 8000
#define LOWBAT 7300
#define HIGHBAT_3V7 4000
#define LOWBAT_3V7 3650


// MAX7456 Registers
#define VM0 0x00    // Video Mode 0
#define VM1 0x01    // Video Mode 1
#define HOS 0x02    // Horizontal Offset
#define VOS 0x03    // Vertical Offset
#define DMM 0X04    // Display Memory Mode
#define DMAH 0X05   // Display Memory Address High
#define DMAL 0X06   // Display Memory Address Low
#define DMDI 0x07   // Display Memory Data In
#define STATUS 0xA0 // Status register

// VM0
#define PAL (1<<6)
#define NTSC (0<<6)
#define SYNC_AUTO ((0<<5)|(0<<6))
#define SYNC_EXTERNAL ((1<<5)|(0<<6))
#define SYNC_INTERNAL ((1<<5)|(1<<6))
#define ENABLE (1<<3)
#define SYNC_NOW (0<<2)
#define SYNC_VSYNC (1<<2)
#define RESET (1<<1)

// VM1
#define BLINK_DUTY_50 0x00 // 50% ON
#define BLINK_DUTY_33 0x01 // 33% ON
#define BLINK_DUTY_25 0x02 // 25% ON
#define BLINK_DUTY_75 0x03 // 75% ON
#define BLINK_TIME_0 0x00
#define BLINK_TIME_1 0x04
#define BLINK_TIME_2 0x08
#define BLINK_TIME_3 0x0C

// DMM
#define LBC (1<<5)
#define BLINK (1<<4)
#define INVERT (1<<3)
#define CLEAR_MEMORY (1<<2)
#define VSYNC_CLEAR_MEMORY (1<<1)
#define AUTO_INCREMENT (1<<0)

// DMDI
#define ESCAPE_CHAR 0xff


// Variables
HMC5883L compass; // Magnetometer object
MPU6050 accelgyro; // Accelerotmeter / Gyroscope object

int16_t ax, ay, az; // Aceelerations (probably doesn't have to be global
int16_t gx, gy, gz; // Angular velocities global because of crosshair

// General
int input, mainDispMode,auxDispMode;
long messageStartTime;

// sensors
float rollRad, pitchRad;
int bat, headingDegMean, pitchDegMean;

// sentry
int headingZeroTX;
int headingTX, pitchTX; // global because limits display

// motion
long lastMotion1RX, lastMotion2RX, lastMotion1Det, lastMotion2Det;
int motion1Bat,motion2Bat;

// rifle
long lastRifleRX;
int rifleBat, rifleAmmo, riflePitch;

// tracker
long lastTrackerRX;
int targetBearing, targetDistance;
boolean trackerLock, beaconLock, beaconRX, trackerData;
int trackerBat, beaconBat;

void setup()
{
  Serial.begin(9600);
  
  Wire.begin(); // Start I2C
  SPI.begin(); // Start SPI
  SPI.setClockDivider(SPI_CLOCK_DIV2); // SPI clock must be lower than 10MHz
  
  byte error = 0x00;
  if(!osdInit()) error |= (1<<0);
  if(!mpuInit()) error |= (1<<1);
  if(!hmcInit()) error |= (1<<2);
  if(!nrfInit()) error |= (1<<3);
  
  displayIntro(error);
  osdClear();
  
  lastTrackerRX = -RX_TIMEOUT_TRACKER;
  lastMotion1RX = -RX_TIMEOUT_MOTION;
  lastMotion2RX = -RX_TIMEOUT_MOTION;
  lastRifleRX = -RX_TIMEOUT_RIFLE;
}

void loop()
{
  switchRead(); // input selector
  buttonRead(); // dispMode selector
  
  changeManagement(); // what happens when input/mode changes
  sensorManagement();
  displayManagement();
  wirelessManagement();
}

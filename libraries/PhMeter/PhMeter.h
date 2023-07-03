#ifndef PhMeter_h
#define PhMeter_h
#include <Arduino.h>
#include "AD7705_device.h"

class PhMeter {
// protected:
// private:

// members:
  float _val;
  float _intercept;
  float _slope;

  AD7705_device adDev;

public:

  static const byte AIN1 = 0x0;
  static const byte AIN2 = 0x1;
  static const byte AIN1m = 0x2;
  static const byte AIN2m = 0x3;

  static const byte UPDATE_RATE_20 = 0x0; // 20 Hz
  static const byte UPDATE_RATE_25 = 0x1; // 25 Hz
  static const byte UPDATE_RATE_100 = 0x2; // 100 Hz
  static const byte UPDATE_RATE_200 = 0x3; // 200 Hz
  static const byte UPDATE_RATE_50 = 0x4; // 50 Hz
  static const byte UPDATE_RATE_60 = 0x5; // 60 Hz
  static const byte UPDATE_RATE_250 = 0x6; // 250 Hz
  static const byte UPDATE_RATE_500 = 0x7; // 500 Hz

  float avgPoints = 10; // точек усреднения

  // int dr; // DRDY pin

// constructor
  PhMeter (
    float vRef = 5.0,
    int csPin = 10,
    byte channel = AIN1,
    int drPin = 9);

  void drHigh ();
  void setIntercept (float x);
  float intercept ();
  void setSlope (float x);
  float slope ();
  void setValue (float x);
  float value ();
  void incAvgValue (float x);
  float read ();

  // AD7705_device adDev;
  void setCs (int x);
  int cs ();
  void setDr (int x);
  int dr ();
  void setCh (byte x);
  byte ch ();

////////////
// AD7705 //
////////////

  void setNextOperation(byte reg, byte readWrite);
  void writeClockRegister(byte CLKDIS, byte CLKDIV, byte outputUpdateRate);
  void writeSetupRegister(byte operationMode, byte gain, byte unipolar, byte buffered, byte fsync);
  unsigned int readDataRegister();
  void getReady();
  boolean DRDY_REDY();
  void init(byte updRate = UPDATE_RATE_500);
  float readADResult();
  void reset();

};
#endif

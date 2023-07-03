#ifndef AD7705_device_h
#define AD7705_device_h

#include <Arduino.h>
#include "AD7705.h"

class AD7705_device : public AD7705 {

  int _csPin;
  int _drPin;
  int _channel;

public:

  AD7705_device(
    float vref = 5.0,
    int csPin = 53,
    byte channel = CHN_AIN1,
    int drPin = 32);

  void setNextOperation(byte reg, byte readWrite);
  void writeClockRegister(byte CLKDIS, byte CLKDIV, byte outputUpdateRate);
  void writeSetupRegister(byte operationMode, byte gain, byte unipolar, byte buffered, byte fsync);
  unsigned int readDataRegister();
  void getReady();
  boolean DRDY_REDY();
  void init(byte updRate);
  float readADResult();
  void AD770Xreset();

  void setCs (int x);
  int cs ();
  void setDr (int x);
  int dr ();
  void setCh (byte x);
  byte ch ();

  protected:

  // int _csPin;
  // int _drPin;
  // int _channel;
};
#endif

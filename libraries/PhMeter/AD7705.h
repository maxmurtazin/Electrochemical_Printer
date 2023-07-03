#ifndef AD7705_h
#define AD7705_h

#include <Arduino.h>
#include <SPI.h>

class AD7705 {

  float VRef;

public:
  AD7705(float vref = 5.0);
    
  //register selection
  //RS2 RS1 RS0
  static const byte REG_CMM = 0x0; //communication register 8 bit
  static const byte REG_SETUP = 0x1; //setup register 8 bit
  static const byte REG_CLOCK = 0x2; //clock register 8 bit
  static const byte REG_DATA = 0x3; //data register 16 bit, contains conversion result
  static const byte REG_TEST = 0x4; //test register 8 bit, POR 0x0
  static const byte REG_NOP = 0x5; //no operation
  static const byte REG_OFFSET = 0x6; //offset register 24 bit
  static const byte REG_GAIN = 0x7; // gain register 24 bit
  
  //channel selection for AD7706 (for AD7705 use the first two channel definitions)
  //CH1 CH0 CH3 CH2
  static const byte CHN_AIN1 = 0x0; //AIN1; calibration register pair 0
  static const byte CHN_AIN2 = 0x1; //AIN2; calibration register pair 1
  static const byte CHN_AIN1m = 0x2; //common; calibration register pair 0
  static const byte CHN_AIN2m = 0x3; //AIN3; calibration register pair 2
  
  //output update rate
  //CLK FS1 FS0
  static const byte UPDATE_RATE_20 = 0x0; // 20 Hz
  static const byte UPDATE_RATE_25 = 0x1; // 25 Hz
  static const byte UPDATE_RATE_100 = 0x2; // 100 Hz
  static const byte UPDATE_RATE_200 = 0x3; // 200 Hz
  static const byte UPDATE_RATE_50 = 0x4; // 50 Hz
  static const byte UPDATE_RATE_60 = 0x5; // 60 Hz
  static const byte UPDATE_RATE_250 = 0x6; // 250 Hz
  static const byte UPDATE_RATE_500 = 0x7; // 500 Hz
  
  //operating mode options
  //MD1 MD0
  static const byte MODE_NORMAL = 0x0; //normal mode
  static const byte MODE_SELF_CAL = 0x1; //self-calibration
  static const byte MODE_ZERO_SCALE_CAL = 0x2; //zero-scale system calibration, POR 0x1F4000, set FSYNC high before calibration, FSYNC low after calibration
  static const byte MODE_FULL_SCALE_CAL = 0x3; //full-scale system calibration, POR 0x5761AB, set FSYNC high before calibration, FSYNC low after calibration
  
  //gain setting
  static const byte GAIN_1 = 0x0;
  static const byte GAIN_2 = 0x1;
  static const byte GAIN_4 = 0x2;
  static const byte GAIN_8 = 0x3;
  static const byte GAIN_16 = 0x4;
  static const byte GAIN_32 = 0x5;
  static const byte GAIN_64 = 0x6;
  static const byte GAIN_128 = 0x7;
  
  void setNextOperation(int pinCS, byte channel, byte reg, byte readWrite);
  
  void writeClockRegister(int pinCS, byte CLKDIS, byte CLKDIV, byte outputUpdateRate);
  
  void writeSetupRegister(int pinCS, byte operationMode, byte gain, byte unipolar, byte buffered, byte fsync);
  
  unsigned int readDataRegister(int pinCS);
  
  void getReady(int pinDR);
  
  boolean DRDY_REDY(int pinDR);
  
  void init(int pinCS, int pinDR, byte channel, byte gain, byte updRate);
  
  float readADResult(int pinCS, int pinDR, byte channel);
  
  byte spiTransferInit(volatile byte data);
  
  void AD770Xreset(int pinCS);
};
#endif

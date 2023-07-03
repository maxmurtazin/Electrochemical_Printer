#include "AD7705_device.h"

AD7705_device::AD7705_device(float vref, int csPin, byte channel, int drPin) : 
  AD7705(vref),
  _csPin(csPin),
  _drPin(drPin),
  _channel(channel)
{
  pinMode(_csPin, OUTPUT);
  pinMode(_drPin, INPUT);
};

// getters, setters

void AD7705_device::setCs (int x)
{
  _csPin = x;
}
int AD7705_device::cs ()
{
  return _csPin;
}
void AD7705_device::setDr (int x)
{
  _drPin = x;
}
int AD7705_device::dr ()
{
  return _drPin;
}
void AD7705_device::setCh (byte x)
{
  _channel = x;
}
byte AD7705_device::ch ()
{
  return _channel;
}

// AD7705

void AD7705_device::setNextOperation(byte reg, byte readWrite)
{
  AD7705::setNextOperation(_csPin, _channel, reg, readWrite);
}

void AD7705_device::writeClockRegister(byte CLKDIS, byte CLKDIV, byte outputUpdateRate)
{
  AD7705::writeClockRegister(_csPin, CLKDIS, CLKDIV, outputUpdateRate);
}

void AD7705_device::writeSetupRegister(byte operationMode, byte gain, byte unipolar, byte buffered, byte fsync)
{
  AD7705::writeSetupRegister(_csPin, operationMode, gain, unipolar, buffered, fsync);
}

unsigned int AD7705_device::readDataRegister()
{
  AD7705::readDataRegister(_csPin);
}

void AD7705_device::getReady()
{
  AD7705::getReady(_drPin);
}

boolean AD7705_device::DRDY_REDY()
{
  AD7705::DRDY_REDY(_drPin);
}

void AD7705_device::init(byte updRate = UPDATE_RATE_500)
{
  AD7705::init(_csPin, _drPin, _channel, GAIN_1, updRate);
}

float AD7705_device::readADResult()
{
  return AD7705::readADResult(_csPin, _drPin, _channel);
}

void AD7705_device::AD770Xreset()
{
  AD7705::AD770Xreset(_csPin);
}

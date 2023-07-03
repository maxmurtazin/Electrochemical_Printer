#include "PhMeter.h"

PhMeter::PhMeter (float vRef, int csPin, byte channel, int drPin) :
  adDev(vRef, csPin, channel, drPin),
  _val(0),
  _intercept(0),
  _slope(1)
{
}

void PhMeter::drHigh ()
{
  digitalWrite(dr(),HIGH);
}
// void PhMeter::drLow ()
// {
//   digitalWrite(dr(),LOW);
// }

//calibration: getters, setters

void PhMeter::setIntercept (float x)
{
  _intercept = x;
}

float PhMeter::intercept ()
{
  return _intercept;
}

void PhMeter::setSlope (float x)
{
  _slope = x;
}

float PhMeter::slope ()
{
  return _slope;
}

// value: getters, setters

float PhMeter::value ()
{
  return _slope*_val + _intercept;
}

void PhMeter::setValue (float x)
{
  _val = (x - _intercept)/_slope;
}

void PhMeter::setCs (int x)
{
  adDev.setCs(x);
}
int PhMeter::cs ()
{
  return adDev.cs();
}
void PhMeter::setDr (int x)
{
  adDev.setDr(x);
}
int PhMeter::dr ()
{
  return adDev.dr();
}
void PhMeter::setCh (byte x)
{
  adDev.setCh(x);
}
byte PhMeter::ch ()
{
  return adDev.ch();
}

// average value

void PhMeter::incAvgValue (float x)
{
  _val = (_val*(avgPoints-1) + x)/avgPoints;
}

float PhMeter::read ()
{
  incAvgValue(readADResult());
  return value();
}

////////////
// AD7705 //
////////////

void PhMeter::setNextOperation(byte reg, byte readWrite)
{
  adDev.setNextOperation(reg, readWrite);
}

void PhMeter::writeClockRegister(byte CLKDIS, byte CLKDIV, byte outputUpdateRate)
{
  adDev.writeClockRegister(CLKDIS, CLKDIV, outputUpdateRate);
}

void PhMeter::writeSetupRegister(byte operationMode, byte gain, byte unipolar, byte buffered, byte fsync)
{
  adDev.writeSetupRegister(operationMode, gain, unipolar, buffered, fsync);
}

unsigned int PhMeter::readDataRegister()
{
  adDev.readDataRegister();
}

void PhMeter::getReady()
{
  adDev.getReady();
}

boolean PhMeter::DRDY_REDY()
{
  adDev.DRDY_REDY();
}

void PhMeter::init(byte updRate)
{
  adDev.init(updRate);
}

float PhMeter::readADResult()
{
  return adDev.readADResult();
}

void PhMeter::reset()
{
  adDev.AD770Xreset();
}

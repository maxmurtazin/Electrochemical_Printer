#include "AD7705.h"

AD7705::AD7705(float vref) : VRef(vref) {
    // VRef = vref;
//    SPCR = _BV(SPE) | _BV(MSTR) | _BV(CPOL) | _BV(CPHA) | _BV(SPI2X) | _BV(SPR1) | _BV(SPR0);
}

void AD7705::setNextOperation(int pinCS, byte channel, byte reg, byte readWrite)
{
  byte r = 0;
  r = reg << 4 | readWrite << 3 | channel;

  digitalWrite(pinCS, LOW);
  SPI.transfer(r);
  digitalWrite(pinCS, HIGH);
}

//Clock Register
//   7      6       5        4        3        2      1      9
//ZERO(0) ZERO(0) ZERO(0) CLKDIS(0) CLKDIV(0)
void AD7705::writeClockRegister(int pinCS, byte CLKDIS, byte CLKDIV, byte outputUpdateRate)
{
  byte r = CLKDIS << 4 | CLKDIV << 3 | outputUpdateRate;
  // r &= ~(1 << 2);//?
  digitalWrite(pinCS, LOW);
  SPI.transfer(r);
  digitalWrite(pinCS, HIGH);
}

//Setup Register
//  7     6     5     4     3      2      1      0
//MD10) MD0(0) G2(0) G1(0) G0(0) B/U(0) BUF(0) FSYNC(1)

void AD7705::writeSetupRegister(int pinCS, byte operationMode, byte gain, byte unipolar, byte buffered, byte fsync)
{
  byte r = operationMode << 6 | gain << 3 | unipolar << 2 | buffered << 1 | fsync;

  digitalWrite(pinCS, LOW);
  SPI.transfer(r);
  digitalWrite(pinCS, HIGH);
}

unsigned int AD7705::readDataRegister(int pinCS)
{
  digitalWrite(pinCS, LOW);
  byte b1 = SPI.transfer(0xff);
  byte b2 = SPI.transfer(0xff);
  digitalWrite(pinCS, HIGH);

  unsigned int r = b1 << 8 | b2;

  return r;
}

void AD7705::getReady(int pinDR)
{
  while (digitalRead(pinDR)==0);
}

boolean AD7705::DRDY_REDY(int pinDR)
{
  boolean testresult = digitalRead(pinDR);

  while(testresult != 0){
    testresult = digitalRead(pinDR);
  }
//  testresult=digitalRead(pinDR);
}

void AD7705::init(int pinCS, int pinDR, byte channel, byte gain, byte updRate)
{
  setNextOperation(pinCS, channel, REG_CLOCK, 0);
  getReady(pinDR);
  writeClockRegister(pinCS, 0, 1, updRate);
  setNextOperation(pinCS, channel, REG_SETUP, 0);
  getReady(pinDR);
  writeSetupRegister(pinCS, MODE_SELF_CAL, gain, 1, 0, 1);
  setNextOperation(pinCS, channel, REG_SETUP, 0);
  getReady(pinDR);
  writeSetupRegister(pinCS, MODE_SELF_CAL, gain, 1, 0, 0);
}

 float AD7705::readADResult(int pinCS, int pinDR, byte channel) {
  setNextOperation(pinCS, channel, REG_DATA, 1);
  getReady(pinDR);
  // DRDY_REDY(pinDR);
  unsigned int x = readDataRegister(pinCS);
  getReady(pinDR);
  // DRDY_REDY(pinDR);
  Serial.print(" ");
  Serial.print(x, BIN);
  Serial.print(" ");
  return VRef/5.0*x;
}

byte AD7705::spiTransferInit(volatile byte data) {
  SPDR = data;
  while (!(SPSR & _BV(SPIF)));
  return SPDR;
}

void AD7705::AD770Xreset(int pinCS) {
  digitalWrite(pinCS, LOW);
  for (int i = 0; i < 100; i++)//100
    spiTransferInit(0xff);
  digitalWrite(pinCS, HIGH);
}

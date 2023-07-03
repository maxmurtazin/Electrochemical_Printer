#include <Wire.h>
#include <SPI.h>
#include "PhMeter.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

// Пины SPI АЦП pH-метров (AD7705)
const int DRPIN = 9;
const int CSPIN = 10;
int analogPin = 5;  // ШИМ сигнал на АЦП
int PinRelay = 6;  // Пин для подключения реле
bool relay;

// Референсное напряжение
float VRef = 5.0;

// Калибровки  pH-метров
float PH_SLOPE = 0.000986 ; //  0.001012 0.0006, 0.0008   
float PH_INTERCEPT = -19.683 ; // -2.0375 -6.4 -14.185
//float TC_SLOPE = 1;
//float TC_INTERCEPT = 0;

//////////////////////////////
PhMeter pH(VRef, CSPIN, PhMeter::AIN1, DRPIN);
// PhMeter TC(VRef, CSPIN, PhMeter::AIN1, DRPIN);
/////////////////////////////

void setup() {
   pinMode(4,OUTPUT); // Реле
  // calibration
  pH.setSlope(PH_SLOPE);
  pH.setIntercept(PH_INTERCEPT);
  // TC.setSlope(TC_SLOPE);
  // TC.setIntercept(TC_INTERCEPT);

  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(5, 1);
  lcd.print("V");
  lcd.setCursor(7, 1);
  lcd.print("pH=");
  // lcd.setCursor(8, 1);
  // lcd.print("H");
  // lcd.setCursor(9, 1);
  // lcd.print("=");

  // Serial.print("pH.cs ");
  // Serial.print(pH.cs());
  // Serial.print(" pH.dr ");
  // Serial.print(pH.dr());

  // Serial.print("TC.cs ");
  // Serial.print(TC.cs());
  // Serial.print(" TC.dr ");
  // Serial.println(TC.dr());

  SPI.begin();
  SPI.beginTransaction(SPISettings(200000, MSBFIRST, SPI_MODE3));  // 65536 кГц

  pH.reset();
  // TC.reset();

  Serial.begin(9600);
  Serial.println("start");

  // pH-meter

  pH.drHigh();
  Serial.println("pH.init(UPDATE_RATE_500 )");
  pH.init(PhMeter::UPDATE_RATE_500);
  pH.getReady();

  // delay(1000);

  // TC.drHigh();
  // Serial.println("TC.init(UPDATE_RATE_60)");
  // TC.init(PhMeter::UPDATE_RATE_60);
  // TC.getReady();

  Serial.println("Wait 1 sec");
  delay(1000);
}

void loop() {
  // pH-meter
  // Serial.print("pH dr ");
  // Serial.print(digitalRead(pH.dr())); //debug
  Serial.print(" pH ch ");
  Serial.print(pH.ch()); //debug
  Serial.println(" pH ");
  Serial.print(pH.read(), 3);
  // Serial.print(" dr ");
  // Serial.print(digitalRead(pH.dr())); //debug
  int anOut = round(min(max(0, pH.value()*18.2143), 255));  
  Serial.print(" val = ");
  Serial.print(anOut);
  analogWrite(analogPin, anOut);


  // Serial.print("; TC dr ");
  // Serial.print(digitalRead(TC.dr())); //debug
  // Serial.print(" ; TC ch ");
  // // Serial.print(TC.ch()); //debug
  // Serial.print(" TC ");
  // Serial.print(TC.read(), 4);
  // delay(100);
  // // Serial.print(" dr ");
  // // Serial.print(digitalRead(TC.dr())); //debug
  // int tc = round(min(max(0, TC.value()*2.55), 255));
  // Serial.print(" val = ");
  // Serial.println(tc);
  // analogWrite(5, tc);

  lcd.setCursor(0, 0);
  lcd.print("R=");
  lcd.setCursor(1, 0);
  lcd.print("=");
  lcd.print(relay);
  // lcd.print(" Temp=");
  // lcd.print(TC.value());
  lcd.setCursor(0, 1);
  lcd.print((anOut/255.0*5.0), 2);
  lcd.setCursor(11, 4);
  lcd.print(max(pH.value(), 0), 2);

  // Код для реле
   if (pH.value() < 1.9) {
     relay = 1;
     digitalWrite(6, HIGH);
   }    
   if (pH.value() > 2.0) {
     relay = 0;
     digitalWrite(6, LOW);
   }

  delay(200);
}

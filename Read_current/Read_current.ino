#include <Arduino_Helpers.h> // Include the Arduino Helpers library.
#include <AH/Hardware/ExtendedInputOutput/ShiftRegisterOut.hpp>
using namespace ExtIO; // Bring the ExtIO pin functions into your sketch

#include "Wire.h"
#include "DFRobot_MCP4725.h"
#include <Adafruit_INA219.h>
#include <TroykaCurrent.h>
#define  REF_VOLTAGE    4850
DFRobot_MCP4725 DAC;
Adafruit_INA219 ina219;
ACS712 sensorCurrent(A0);


 
const pin_t latchPin = 3; // Pin connected to ST_CP of 74HC595 (violet_T)
const pin_t dataPin = 2;  // Pin connected to DS of 74HC595 (grey_D)
const pin_t clockPin = 4; // Pin connected to SH_CP of 74HC595 (blue_H)
 
// Instantiate a shift register on the correct pins, most significant bit first,
// and a total of 8 outputs.
ShiftRegisterOut<64> sreg {dataPin, clockPin, latchPin, MSBFIRST};//количество пинов сдвигового регистра
//// SH REG
const pin_t ledPin1 = sreg.pin(0); 
const pin_t ledPin2 = sreg.pin(8);// first pin of the shift register
 

// OUTPUT_VOLTAGE_DAC = 30;        // unit : mV 
//int REG_OUTPUT_VOLTAGE_DAC = 0;
 int mV=30;
// библиотека для работы с SPI
#include <SPI.h>
// библиотека для работы с Ethernet Shield
#include <Ethernet2.h>

// MAC-адрес контроллера
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD };
// задаем статический IP-адрес
IPAddress ip(192, 168, 0, 103);
String readString;
// инициализируем библиотеку Ethernet Server
// с необходимыми вам IP-адресом и портом
// порт 80 используется для HTTP по умолчанию
EthernetServer server(80);

void setup()
{
   sreg.begin(); 
//DAC 
  Serial.begin(9600);
  DAC.init(0x62, REF_VOLTAGE);
 ina219.begin();
 // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  //  if (! ina219.begin()) {
  //    Serial.println("Failed to find INA219 chip");
  //    while (1) { delay(10); }
  //  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();


  // открываем последовательный порт
  Serial.begin(9600);
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
 
  Serial.print("Serial init OK\r\n");
  // запускаем Ethernet-соединение:
  if (Ethernet.begin(mac) == 0) {
    // если не удалось сконфигурировать Ethernet при помощи DHCP
    Serial.println("Failed to configure Ethernet using DHCP");
    // продолжать дальше смысла нет, поэтому вместо DHCP
    // попытаемся сделать это при помощи IP-адреса:
    Ethernet.begin(mac, ip);
  }
  // запускаем сервер и выводим локальный IP адрес
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
 
}


int REG_VOLT (int mV){ //
  DAC.outputVoltage(mV);
  
}


void loop()
{
 // Toggle the state of the LED every 1/2 second
 // digitalWrite(ledPin1, HIGH);
  


//DAC///////////////////////////////////
REG_VOLT(mV);
  //Serial.print(OUTPUT_VOLTAGE_DAC); 
  Serial.println(" mV"); 
 // DAC.outputVoltage(150);
  delay(500);

//Current
float busvoltage_OUT = 0;
  float current_mA = 0;
 
 busvoltage_OUT = ina219.getBusVoltage_V();
 // current_mA = ina219.getCurrent_mA();
 current_mA = sensorCurrent.readCurrentDC();
 
 // Serial.print("Bus Voltage:   "); Serial.print(busvoltage_OUT); Serial.println(" V");
 
//  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
 
  delay(500);
///////////////////////////////////////////////////////////////////////

  // слушаем подключающихся клиентов
  EthernetClient client = server.available();
  if (client) {
    // выводим сообщение о новом клиенте
   // Serial.println("new client");
    // HTTP-запрос заканчивается пустой линией
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

                //read char by char HTTP request
                if (readString.length() < 100) {

                    //store characters to string
                    readString += c;
                }

        //if (c == 0x0D)
        Serial.write(c);
        // если добрались до конца строки (т.е. получили символ новой строки),
        // и эта строка – пустая, это значит, что это конец HTTP-запроса.
        // то есть, можно приступать к отправке ответа:
        if (c == '\n' && currentLineIsBlank) {
          // отсылаем стандартный заголовок для HTTP-ответа:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          // после выполнения ответа соединение будет разорвано
          client.println("Connection: close");
          // автоматически обновляем страницу каждые 5 секунд
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
              client.println("<HTML>");
                    client.println("<HEAD>");
                    client.println("<TITLE> ARDUINO ETHERNET SHIELD</TITLE>");
                    client.println("</HEAD>");
                    client.println("<BODY>");
                    client.println("<hr>");
                    client.println("<hr>");
                    client.println("<br>");
                    client.println("<H1 style=\"color:green;\">ARDUINO ETHERNET SHIELD DAC FROM WEBPAGE</H1>");
                    client.println("<hr>");
                    client.println("<br>");

                    client.println("<H2><a href=\"/?UP100\"\"> DAC _OUT 3V</a><br></H2>");
                    client.println("<H2><a href=\"/?UP200\"\"> DAC UP2000mV</a><br></H2>");

                    client.println("<H2><a href=\"/?DAC_OFF\"\">DAC OFF</a><br></H2>");


                    client.println("<H2><a href=\"/?SHREG_ON1\"\"> SHREG_ON1</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF1\"\"> SHREG_OFF1</a><br></H2>");

                    client.println("<H2><a href=\"/?SHREG_ON2\"\"> SHREG_ON2</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF2\"\"> SHREG_OFF2</a><br></H2>");


                    
         

  
            float sensorReading1 = busvoltage_OUT;
            client.print("Voltage_OUT");
            client.print(" V ");
            client.print(sensorReading1);
            client.println("<br />");


             float sensorReading2 = current_mA;
            client.print(" Current_OUT");
            client.print(" A ");
            client.print(sensorReading2);
            client.println("<br />");

       //       float sensorReading3 = OUTPUT_VOLTAGE_DAC ;
            client.print("Voltage_DAC_OUT");
            client.print(" mV ");
      //      client.print(sensorReading3);
            client.println("<br />");



            
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // начинаем новую строку
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // в текущей строке есть символ:
          currentLineIsBlank = false;
        }
      }
    }
    // даем браузеру время, чтобы получить данные
    delay(1);
    // закрываем соединение
    client.stop();


     // control 100
                    if(readString.indexOf("?UP100") > -1) /// 3V
                    {
                      mV =  867 ;
                       digitalWrite(2, HIGH);
                    }
              ////////2
                   if(readString.indexOf("?UP200") > -1) /// "?UP100"
                    {
                      mV =  2000 ;
                    }

                    ////////SH_REG

                    if(readString.indexOf("?SHREG_ON1") > -1) /// 3V
                    {
                      
                        digitalWrite(ledPin1, HIGH);//test
                    }

                    if(readString.indexOf("?SHREG_OFF1") > -1) /// 3V
                    {
                     
                        digitalWrite(ledPin1, LOW);
                    }
                    /////////////

                     if(readString.indexOf("?SHREG_ON2") > -1) /// 3V
                    {
                      
                        digitalWrite(ledPin2, HIGH);//test
                    }

                    if(readString.indexOf("?SHREG_OFF2") > -1) /// 3V
                    {
                     
                        digitalWrite(ledPin2, LOW);
                    }






                    else{
                        if(readString.indexOf("?DAC_OFF") > -1) //checks for LEDOFF
                        {
                           
                        mV = 10;
                       digitalWrite(2, LOW);
                        }
                    }
                    //clearing string for next read
                   // readString="";
                     // control 10
                    
                    
                     readString="";
    // клиент отключился
    Serial.println("Client disconnected");
  }
}
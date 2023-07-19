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
const pin_t ledPin1 = sreg.pin(0); //1 
const pin_t ledPin2 = sreg.pin(1);
const pin_t ledPin3 = sreg.pin(2); 
const pin_t ledPin4 = sreg.pin(3);

const pin_t ledPin5 = sreg.pin(4); //2
const pin_t ledPin6 = sreg.pin(5);
const pin_t ledPin7 = sreg.pin(6);
const pin_t ledPin8 = sreg.pin(7);

const pin_t ledPin9 = sreg.pin(8); //3
const pin_t ledPin10 = sreg.pin(9);
const pin_t ledPin11 = sreg.pin(10);
const pin_t ledPin12 = sreg.pin(11);

const pin_t ledPin13 = sreg.pin(12); //4
const pin_t ledPin14 = sreg.pin(13);
const pin_t ledPin15 = sreg.pin(14);
const pin_t ledPin16 = sreg.pin(15);

const pin_t ledPin17 = sreg.pin(16);//5
const pin_t ledPin18 = sreg.pin(17);
const pin_t ledPin19 = sreg.pin(18);
const pin_t ledPin20 = sreg.pin(19);

const pin_t ledPin21 = sreg.pin(20);//6
const pin_t ledPin22 = sreg.pin(21);
const pin_t ledPin23 = sreg.pin(22);
const pin_t ledPin24 = sreg.pin(23);

const pin_t ledPin25 = sreg.pin(24);//7
const pin_t ledPin26 = sreg.pin(25);
const pin_t ledPin27 = sreg.pin(26);
const pin_t ledPin28 = sreg.pin(27);

const pin_t ledPin29 = sreg.pin(28);//8
const pin_t ledPin30 = sreg.pin(29);
const pin_t ledPin31 = sreg.pin(30);
const pin_t ledPin32 = sreg.pin(31);

const pin_t ledPin33 = sreg.pin(32);//9
const pin_t ledPin34 = sreg.pin(33);
const pin_t ledPin35 = sreg.pin(34);
const pin_t ledPin36 = sreg.pin(35);

const pin_t ledPin37 = sreg.pin(36);//10
const pin_t ledPin38 = sreg.pin(37);
const pin_t ledPin39 = sreg.pin(38);
const pin_t ledPin40 = sreg.pin(39);

const pin_t ledPin41 = sreg.pin(40);//11
const pin_t ledPin42 = sreg.pin(41);
const pin_t ledPin43 = sreg.pin(42);
const pin_t ledPin44 = sreg.pin(43);

const pin_t ledPin45 = sreg.pin(44);//12
const pin_t ledPin46 = sreg.pin(45);
const pin_t ledPin47 = sreg.pin(46);
const pin_t ledPin48 = sreg.pin(47);

const pin_t ledPin49 = sreg.pin(48);//13
const pin_t ledPin50 = sreg.pin(49);
const pin_t ledPin51 = sreg.pin(50);
const pin_t ledPin52 = sreg.pin(51);

const pin_t ledPin53 = sreg.pin(52);//14
const pin_t ledPin54 = sreg.pin(53);
const pin_t ledPin55 = sreg.pin(54);
const pin_t ledPin56 = sreg.pin(55);

const pin_t ledPin57 = sreg.pin(56);//15
const pin_t ledPin58 = sreg.pin(57);
const pin_t ledPin59 = sreg.pin(58);
const pin_t ledPin60 = sreg.pin(59);

const pin_t ledPin61 = sreg.pin(60);//16
const pin_t ledPin62 = sreg.pin(61);
const pin_t ledPin63 = sreg.pin(62);
const pin_t ledPin64 = sreg.pin(63);
////////////////////////////////////////////
 

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
                    //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

                  client.println("<H2><a href=\"/?SHREG_ON1\"\"> SHREG_ON1</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF1\"\"> SHREG_OFF1</a><br></H2>");

                    client.println("<H2><a href=\"/?SHREG_ON2\"\"> SHREG_ON2</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF2\"\"> SHREG_OFF2</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON3\"\"> SHREG_ON3</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF3\"\"> SHREG_OFF3</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON4\"\"> SHREG_ON4</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF4\"\"> SHREG_OFF4</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON5\"\"> SHREG_ON5</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF5\"\"> SHREG_OFF5</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON6\"\"> SHREG_ON6</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF6\"\"> SHREG_OFF6</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON7\"\"> SHREG_ON7</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF7\"\"> SHREG_OFF7</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON8\"\"> SHREG_ON8</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF8\"\"> SHREG_OFF8</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON9\"\"> SHREG_ON9</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF9\"\"> SHREG_OFF9</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON10\"\"> SHREG_ON10</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF10\"\"> SHREG_OFF10</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON11\"\"> SHREG_ON11</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF11\"\"> SHREG_OFF11</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON12\"\"> SHREG_ON12</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF12\"\"> SHREG_OFF12</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON13\"\"> SHREG_ON13</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF13\"\"> SHREG_OFF13</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON14\"\"> SHREG_ON14</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF14\"\"> SHREG_OFF14</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON15\"\"> SHREG_ON15</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF15\"\"> SHREG_OFF15</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON16\"\"> SHREG_ON16</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF16\"\"> SHREG_OFF16</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON17\"\"> SHREG_ON17</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF17\"\"> SHREG_OFF17</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON18\"\"> SHREG_ON18</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF18\"\"> SHREG_OFF18</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON19\"\"> SHREG_ON19</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF19\"\"> SHREG_OFF19</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON20\"\"> SHREG_ON20</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF20\"\"> SHREG_OFF20</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON21\"\"> SHREG_ON21</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF21\"\"> SHREG_OFF21</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON22\"\"> SHREG_ON22</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF22\"\"> SHREG_OFF22</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON23\"\"> SHREG_ON23</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF23\"\"> SHREG_OFF23</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON24\"\"> SHREG_ON24</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF24\"\"> SHREG_OFF24</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON25\"\"> SHREG_ON25</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF25\"\"> SHREG_OFF25</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON26\"\"> SHREG_ON26</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF26\"\"> SHREG_OFF26</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON27\"\"> SHREG_ON27</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF27\"\"> SHREG_OFF27</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON28\"\"> SHREG_ON28</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF28\"\"> SHREG_OFF28</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON29\"\"> SHREG_ON29</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF29\"\"> SHREG_OFF29</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON30\"\"> SHREG_ON30</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF30\"\"> SHREG_OFF30</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON31\"\"> SHREG_ON31</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF31\"\"> SHREG_OFF31</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON32\"\"> SHREG_ON32</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF32\"\"> SHREG_OFF32</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON33\"\"> SHREG_ON33</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF33\"\"> SHREG_OFF33</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON34\"\"> SHREG_ON34</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF34\"\"> SHREG_OFF34</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON35\"\"> SHREG_ON35</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF35\"\"> SHREG_OFF35</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON36\"\"> SHREG_ON36</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF36\"\"> SHREG_OFF36</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON37\"\"> SHREG_ON37</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF37\"\"> SHREG_OFF37</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON38\"\"> SHREG_ON38</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF38\"\"> SHREG_OFF38</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON39\"\"> SHREG_ON39</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF39\"\"> SHREG_OFF39</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON40\"\"> SHREG_ON40</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF40\"\"> SHREG_OFF40</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON41\"\"> SHREG_ON41</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF41\"\"> SHREG_OFF41</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON42\"\"> SHREG_ON42</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF42\"\"> SHREG_OFF42</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON43\"\"> SHREG_ON43</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF43\"\"> SHREG_OFF43</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON44\"\"> SHREG_ON44</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF44\"\"> SHREG_OFF44</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON45\"\"> SHREG_ON45</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF45\"\"> SHREG_OFF45</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON47\"\"> SHREG_ON47</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF47\"\"> SHREG_OFF47</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON48\"\"> SHREG_ON48</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF48\"\"> SHREG_OFF48</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON49\"\"> SHREG_ON49</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF49\"\"> SHREG_OFF49</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON50\"\"> SHREG_ON50</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF50\"\"> SHREG_OFF50</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON51\"\"> SHREG_ON51</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF51\"\"> SHREG_OFF51</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON52\"\"> SHREG_ON52</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF52\"\"> SHREG_OFF52</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON53\"\"> SHREG_ON53</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF53\"\"> SHREG_OFF53</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON54\"\"> SHREG_ON54</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF54\"\"> SHREG_OFF54</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON55\"\"> SHREG_ON55</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF55\"\"> SHREG_OFF55</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON56\"\"> SHREG_ON56</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF56\"\"> SHREG_OFF56</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON57\"\"> SHREG_ON57</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF57\"\"> SHREG_OFF57</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON58\"\"> SHREG_ON58</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF58\"\"> SHREG_OFF58</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON59\"\"> SHREG_ON59</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF59\"\"> SHREG_OFF59</a><br></H2>");
                   
                     client.println("<H2><a href=\"/?SHREG_ON60\"\"> SHREG_ON60</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF60\"\"> SHREG_OFF60</a><br></H2>");

                     client.println("<H2><a href=\"/?SHREG_ON61\"\"> SHREG_ON61</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF61\"\"> SHREG_OFF61</a><br></H2>");

                    client.println("<H2><a href=\"/?SHREG_ON62\"\"> SHREG_ON62</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF62\"\"> SHREG_OFF62</a><br></H2>");

                    client.println("<H2><a href=\"/?SHREG_ON63\"\"> SHREG_ON63</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF63\"\"63 SHREG_OFF63</a><br></H2>");


                    client.println("<H2><a href=\"/?SHREG_ON64\"\"> SHREG_ON64</a><br></H2>");
                    client.println("<H2><a href=\"/?SHREG_OFF64\"\"> SHREG_OFF64</a><br></H2>");



                    
         
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
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
                   //////////////////////////////////////////////////////////////////////// 1
                    ////////SH_REG

                    if(readString.indexOf("?SHREG_ON1") > -1) /// 1
                    {
                        digitalWrite(ledPin1, HIGH);//test
                     // Serial.println("1_ON"); 
                    }

                    if(readString.indexOf("?SHREG_OFF1") > -1) /// 1
                    {
                        digitalWrite(ledPin1, LOW);
                      //  Serial.println("1_LOW");   
                    }
                   /////////////////////////////////////////////////////////////2

                     if(readString.indexOf("?SHREG_ON2") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin2, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF2") > -1) /// 2
                    {
                        digitalWrite(ledPin2, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////3

                     if(readString.indexOf("?SHREG_ON3") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin3, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF3") > -1) /// 2
                    {
                        digitalWrite(ledPin3, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////4

                     if(readString.indexOf("?SHREG_ON4") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin4, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF4") > -1) /// 2
                    {
                        digitalWrite(ledPin4, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////5

                     if(readString.indexOf("?SHREG_ON5") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin5, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF5") > -1) /// 2
                    {
                        digitalWrite(ledPin5, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////6

                     if(readString.indexOf("?SHREG_ON6") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin6, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF6") > -1) /// 2
                    {
                        digitalWrite(ledPin6, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////7

                     if(readString.indexOf("?SHREG_ON7") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin7, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF7") > -1) /// 2
                    {
                        digitalWrite(ledPin7, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////8

                     if(readString.indexOf("?SHREG_ON8") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin8, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF8") > -1) /// 2
                    {
                        digitalWrite(ledPin8, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////9

                     if(readString.indexOf("?SHREG_ON9") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin9, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF9") > -1) /// 2
                    {
                        digitalWrite(ledPin9, LOW);
                       //  Serial.println("2_LOW");
                    }
                      /////////////////////////////////////////////////////////////10

                     if(readString.indexOf("?SHREG_ON10") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin10, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF10") > -1) /// 2
                    {
                        digitalWrite(ledPin10, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////11

                     if(readString.indexOf("?SHREG_ON11") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin11, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF11") > -1) /// 2
                    {
                        digitalWrite(ledPin11, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////12

                     if(readString.indexOf("?SHREG_ON12") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin12, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF12") > -1) /// 2
                    {
                        digitalWrite(ledPin12, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////13

                     if(readString.indexOf("?SHREG_ON13") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin13, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF13") > -1) /// 2
                    {
                        digitalWrite(ledPin13, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////14

                     if(readString.indexOf("?SHREG_ON14") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin14, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF14") > -1) /// 2
                    {
                        digitalWrite(ledPin14, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////15

                     if(readString.indexOf("?SHREG_ON15") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin15, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF15") > -1) /// 2
                    {
                        digitalWrite(ledPin15, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////16

                     if(readString.indexOf("?SHREG_ON16") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin16, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF16") > -1) /// 2
                    {
                        digitalWrite(ledPin16, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////17

                     if(readString.indexOf("?SHREG_ON17") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin17, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF17") > -1) /// 2
                    {
                        digitalWrite(ledPin17, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////18

                     if(readString.indexOf("?SHREG_ON18") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin18, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF18") > -1) /// 2
                    {
                        digitalWrite(ledPin18, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////19

                     if(readString.indexOf("?SHREG_ON19") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin19, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF19") > -1) /// 20
                    {
                        digitalWrite(ledPin19, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////20

                     if(readString.indexOf("?SHREG_ON20") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin20, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF20") > -1) /// 2
                    {
                        digitalWrite(ledPin20, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////21

                     if(readString.indexOf("?SHREG_ON21") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin21, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF21") > -1) /// 2
                    {
                        digitalWrite(ledPin21, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////22

                     if(readString.indexOf("?SHREG_ON22") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin22, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF22") > -1) /// 2
                    {
                        digitalWrite(ledPin22, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////23

                     if(readString.indexOf("?SHREG_ON23") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin23, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF23") > -1) /// 2
                    {
                        digitalWrite(ledPin23, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////24

                     if(readString.indexOf("?SHREG_ON24") > -1) /// 24
                    {
                      
                        digitalWrite(ledPin24, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF24") > -1) /// 2
                    {
                        digitalWrite(ledPin24, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////25

                     if(readString.indexOf("?SHREG_ON25") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin25, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF25") > -1) /// 2
                    {
                        digitalWrite(ledPin25, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////26

                     if(readString.indexOf("?SHREG_ON26") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin26, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF26") > -1) /// 2
                    {
                        digitalWrite(ledPin26, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////27

                     if(readString.indexOf("?SHREG_ON27") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin27, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF27") > -1) /// 2
                    {
                        digitalWrite(ledPin27, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////28

                     if(readString.indexOf("?SHREG_ON28") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin28, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF28") > -1) /// 2
                    {
                        digitalWrite(ledPin28, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////29

                     if(readString.indexOf("?SHREG_ON29") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin29, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF29") > -1) /// 2
                    {
                        digitalWrite(ledPin29, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////30

                     if(readString.indexOf("?SHREG_ON30") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin30, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF30") > -1) /// 2
                    {
                        digitalWrite(ledPin30, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////31

                     if(readString.indexOf("?SHREG_ON31") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin31, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF31") > -1) /// 2
                    {
                        digitalWrite(ledPin31, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////32

                     if(readString.indexOf("?SHREG_ON32") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin32, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF32") > -1) /// 2
                    {
                        digitalWrite(ledPin32, LOW);
                       //  Serial.println("2_LOW");
                    }

                       /////////////////////////////////////////////////////////////32

                     if(readString.indexOf("?SHREG_ON2") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin2, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF2") > -1) /// 2
                    {
                        digitalWrite(ledPin2, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////33

                     if(readString.indexOf("?SHREG_ON33") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin33, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF33") > -1) /// 2
                    {
                        digitalWrite(ledPin33, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////34

                     if(readString.indexOf("?SHREG_ON34") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin34, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF34") > -1) /// 2
                    {
                        digitalWrite(ledPin34, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////35

                     if(readString.indexOf("?SHREG_ON35") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin35, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF35") > -1) /// 2
                    {
                        digitalWrite(ledPin35, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////36

                     if(readString.indexOf("?SHREG_ON36") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin36, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF36") > -1) /// 2
                    {
                        digitalWrite(ledPin36, LOW);
                       //  Serial.println("2_LOW");
                    }

                      /////////////////////////////////////////////////////////////37

                     if(readString.indexOf("?SHREG_ON37") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin37, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF37") > -1) /// 2
                    {
                        digitalWrite(ledPin37, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////38

                     if(readString.indexOf("?SHREG_ON38") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin38, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF38") > -1) /// 2
                    
                        digitalWrite(ledPin38, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////39

                     if(readString.indexOf("?SHREG_ON39") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin39, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF39") > -1) /// 2
                    {
                        digitalWrite(ledPin39, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////40

                     if(readString.indexOf("?SHREG_ON40") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin40, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF40") > -1) /// 2
                    {
                        digitalWrite(ledPin40, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////41

                     if(readString.indexOf("?SHREG_ON41") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin41, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF41") > -1) /// 2
                    {
                        digitalWrite(ledPin41, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////42

                     if(readString.indexOf("?SHREG_ON42") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin42, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF42") > -1) /// 2
                    {
                        digitalWrite(ledPin42, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////43

                     if(readString.indexOf("?SHREG_ON43") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin43, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF43") > -1) /// 2
                    {
                        digitalWrite(ledPin43, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////44

                     if(readString.indexOf("?SHREG_ON44") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin44, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF44") > -1) /// 2
                    {
                        digitalWrite(ledPin44, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////45

                     if(readString.indexOf("?SHREG_ON45") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin45, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF45") > -1) /// 2
                    {
                        digitalWrite(ledPin45, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////46

                     if(readString.indexOf("?SHREG_ON46") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin46, HIGH);//test
                       // Serial.println("2_ON");
                    }
                    if(readString.indexOf("?SHREG_OFF46") > -1) /// 2
                    {
                        digitalWrite(ledPin46, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////47

                     if(readString.indexOf("?SHREG_ON47") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin47, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF47") > -1) /// 2
                    {
                        digitalWrite(ledPin47, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////48

                     if(readString.indexOf("?SHREG_ON48") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin48, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF48") > -1) /// 2
                    {
                        digitalWrite(ledPin48, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////49

                     if(readString.indexOf("?SHREG_ON49") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin49, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF49") > -1) /// 2
                    {
                        digitalWrite(ledPin49, LOW);
                       //  Serial.println("2_LOW");
                    }

                      //////////////////////////////////////////////////////////50

                     if(readString.indexOf("?SHREG_ON50") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin50, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF50") > -1) /// 2
                    {
                        digitalWrite(ledPin50, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////51

                     if(readString.indexOf("?SHREG_ON51") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin51, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF51") > -1) /// 2
                    {
                        digitalWrite(ledPin51, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////52

                     if(readString.indexOf("?SHREG_ON52") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin52, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF52") > -1) /// 2
                    {
                        digitalWrite(ledPin52, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////53

                     if(readString.indexOf("?SHREG_ON53") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin53, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF53") > -1) /// 2
                    {
                        digitalWrite(ledPin53, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////54

                     if(readString.indexOf("?SHREG_ON54") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin54, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF54") > -1) /// 2
                    {
                        digitalWrite(ledPin54, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////55

                     if(readString.indexOf("?SHREG_ON55") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin55, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF55") > -1) /// 2
                    {
                        digitalWrite(ledPin55, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////56

                     if(readString.indexOf("?SHREG_ON56") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin56, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF56") > -1) /// 2
                    {
                        digitalWrite(ledPin56, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////57

                     if(readString.indexOf("?SHREG_ON57") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin57, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF57") > -1) /// 2
                    {
                        digitalWrite(ledPin57, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////58

                     if(readString.indexOf("?SHREG_ON58") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin58, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF58") > -1) /// 2
                    {
                        digitalWrite(ledPin58, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////59

                     if(readString.indexOf("?SHREG_ON59") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin59, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF59") > -1) /// 2
                    {
                        digitalWrite(ledPin59, LOW);
                       //  Serial.println("2_LOW");
                    }

                       ////////////////////////////////////////////////////////////60

                     if(readString.indexOf("?SHREG_ON60") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin60, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF60") > -1) /// 2
                    {
                        digitalWrite(ledPin60, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////61

                     if(readString.indexOf("?SHREG_ON61") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin61, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF61") > -1) /// 2
                    {
                        digitalWrite(ledPin61, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////62

                     if(readString.indexOf("?SHREG_ON62") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin62, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF62") > -1) /// 2
                    {
                        digitalWrite(ledPin62, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////63

                     if(readString.indexOf("?SHREG_ON63") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin63, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF63") > -1) /// 2
                    {
                        digitalWrite(ledPin63, LOW);
                       //  Serial.println("2_LOW");
                    }

                       /////////////////////////////////////////////////////////////64

                     if(readString.indexOf("?SHREG_ON64") > -1) /// 2
                    {
                      
                        digitalWrite(ledPin64, HIGH);//test
                       // Serial.println("2_ON");
                    }

                    if(readString.indexOf("?SHREG_OFF64") > -1) /// 2
                    {
                        digitalWrite(ledPin64, LOW);
                       //  Serial.println("2_LOW");
                    }

                      ////////////////////////////////////////////////////////////



                    else{{
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
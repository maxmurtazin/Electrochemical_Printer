#include "Wire.h"
#include "DFRobot_MCP4725.h"
#include <Adafruit_INA219.h>
#define  REF_VOLTAGE    4850
DFRobot_MCP4725 DAC;
Adafruit_INA219 ina219;
// OUTPUT_VOLTAGE_DAC = 30;        // unit : mV 
//int REG_OUTPUT_VOLTAGE_DAC = 0;
 int mV=30;
// библиотека для работы с SPI
#include <SPI.h>
// библиотека для работы с Ethernet Shield
#include <Ethernet2.h>

// MAC-адрес контроллера
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// задаем статический IP-адрес
IPAddress ip(192, 168, 88, 177);
String readString;
// инициализируем библиотеку Ethernet Server
// с необходимыми вам IP-адресом и портом
// порт 80 используется для HTTP по умолчанию
EthernetServer server(80);

void setup()
{
//DAC 
  Serial.begin(9600);
  DAC.init(0x62, REF_VOLTAGE);

 // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();


  // открываем последовательный порт
  Serial.begin(9600);
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  while (!Serial) {
  }
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
  current_mA = ina219.getCurrent_mA();
 
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


                    
         

  
            float sensorReading1 = busvoltage_OUT;
            client.print("Voltage_OUT");
            client.print(" V ");
            client.print(sensorReading1);
            client.println("<br />");


             float sensorReading2 = current_mA;
            client.print(" Current_OUT");
            client.print(" mA ");
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
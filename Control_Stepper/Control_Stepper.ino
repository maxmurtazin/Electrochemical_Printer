#include <SPI.h>
#include <Ethernet2.h>

const int dirPin = 7;
const int stepPin = 6;

//MOVE
// ST 1/8
const int MV50 = 10000 ; 
const int MV10 = 2000 ; 
const int MV1 = 200 ; 
const int MV01 = 20 ;  
const int MV005 = 10  ;
const int MV001 = 2 ;


// ST 1/16
// const int MV50 = 20000 ; 
// const int MV10 = 4000 ; 
// const int MV1 =  400; 
// const int MV01 = 40 ;  
// const int MV005 = 20 ;
// const int MV001 = 4 ;


String readString;
int ledPin = 5;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 167);

EthernetServer server(80);
void setup(){

  // Объявить контакты как выходы
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT); 
  

    pinMode(ledPin, OUTPUT); //pin selected to control
    // Test LED
    digitalWrite(ledPin, HIGH); // set pin high
    delay(500);
    digitalWrite(ledPin, LOW); // set pin low
   
   


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

int MOVE (int heihgt, bool UPP){ //
   // Установка направления вращения двигателя по часовой стрелке.
 
  digitalWrite(dirPin, UPP); // по часовой 
  // Медленное вращение двигателя
  for(int x = 0; x < heihgt; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
 // delay(5000); // Ждем 
}

void loop(){
 // MOVE(50, HIGH);
 // delay(5000);
    // Create a client connection
    EthernetClient client = server.available();
    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                //read char by char HTTP request
                if (readString.length() < 100) {

                    //store characters to string
                    readString += c;
                }

                //if HTTP request has ended– 0x0D is Carriage Return \n ASCII
                if (c == 0x0D) {
                    client.println("HTTP/1.1 200 OK"); //send new page
                    client.println("Content-Type: text/html");
                    client.println();

                    client.println("<HTML>");
                    client.println("<HEAD>");
                    client.println("<TITLE> ARDUINO ETHERNET SHIELD</TITLE>");
                    client.println("</HEAD>");
                    client.println("<BODY>");
                    client.println("<hr>");
                    client.println("<hr>");
                    client.println("<br>");
                    client.println("<H1 style=\"color:green;\">ARDUINO ETHERNET SHIELD STEPPER RULE FROM WEBPAGE</H1>");
                    client.println("<hr>");
                    client.println("<br>");

                    client.println("<H2><a href=\"/?UP50\"\"> STEPPER UP50</a><br></H2>");
                    client.println("<H2><a href=\"/?DOWN50\"\">STEPPER DOWN50</a><br></H2>");

                    client.println("<H2><a href=\"/?UP10\"\"> STEPPER UP10</a><br></H2>");
                    client.println("<H2><a href=\"/?DOWN10\"\">STEPPER DOWN10</a><br></H2>");

                    client.println("<H2><a href=\"/?UP1\"\"> STEPPER UP1</a><br></H2>");
                    client.println("<H2><a href=\"/?DOWN1\"\">STEPPER DOWN1</a><br></H2>");

                    client.println("<H2><a href=\"/?UP01\"\"> STEPPER UP01</a><br></H2>");
                    client.println("<H2><a href=\"/?DOWN01\"\">STEPPER DOWN01</a><br></H2>");


                    client.println("<H2><a href=\"/?UP005\"\"> STEPPER UP005</a><br></H2>");
                    client.println("<H2><a href=\"/?DOWN005\"\">STEPPER DOWN005</a><br></H2>");

                      client.println("<H2><a href=\"/?UP001\"\"> STEPPER UP001</a><br></H2>");
                    client.println("<H2><a href=\"/?DOWN001\"\">STEPPER DOWN001</a><br></H2>");

                    

                    client.println("</BODY>");
                    client.println("</HTML>");

                    delay(10);
                    //stopping client
                    client.stop();

                    // control 50
                    if(readString.indexOf("?UP50") > -1) //checks for LEDON
                    {
                        MOVE(MV50, HIGH);
                        digitalWrite(ledPin, HIGH); // set pin high
                        //delay(7200);
                    }
                    else{
                        if(readString.indexOf("?DOWN50") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPin, LOW); // set pin low
                             MOVE(MV50, LOW);//
                        }
                    }
                    //clearing string for next read
                   // readString="";
                     // control 10
                    if(readString.indexOf("?UP10") > -1) //checks for LEDON
                    {
                        MOVE(MV10, HIGH);
                        digitalWrite(ledPin, HIGH); // set pin high
                        //delay(7200);
                    }
                    else{
                        if(readString.indexOf("?DOWN10") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPin, LOW); // set pin low
                             MOVE(MV10, LOW);//
                        }
                    }
                    //clearing string for next read
                    //readString="";

                      // control 1
                    if(readString.indexOf("?UP1") > -1) //checks for LEDON
                    {
                        MOVE(MV1, HIGH);
                        digitalWrite(ledPin, HIGH); // set pin high
                        //delay(7200);
                    }
                    else{
                        if(readString.indexOf("?DOWN1") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPin, LOW); // set pin low
                             MOVE(MV1, LOW);//
                        }
                    }
                    //clearing string for next read
                   // readString="";

                        // control 01
                    if(readString.indexOf("?UP01") > -1) //checks for LEDON
                    {
                        MOVE(MV01, HIGH);
                        digitalWrite(ledPin, HIGH); // set pin high
                        //delay(7200);
                    }
                    else{
                        if(readString.indexOf("?DOWN01") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPin, LOW); // set pin low
                             MOVE(MV01, LOW);//
                        }
                    }
                    //clearing string for next read
                   // readString="";

                          // control 005
                    if(readString.indexOf("?UP005") > -1) //checks for LEDON
                    {
                        MOVE(MV005, HIGH);
                        digitalWrite(ledPin, HIGH); // set pin high
                        //delay(7200);
                    }
                    else{
                        if(readString.indexOf("?DOWN005") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPin, LOW); // set pin low
                             MOVE(MV005, LOW);//
                        }
                    }
                    //clearing string for next read
                   // readString="";


                           // control 001
                    if(readString.indexOf("?UP001") > -1) //checks for LEDON
                    {
                        MOVE(MV001, HIGH);
                        digitalWrite(ledPin, HIGH); // set pin high
                        //delay(7200);
                    }
                    else{
                        if(readString.indexOf("?DOWN001") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPin, LOW); // set pin low
                             MOVE(MV001, LOW);//
                        }
                    }
                    //clearing string for next read
                    readString="";

                }
            }
        }
    }
}
#include <Arduino_Helpers.h> // Include the Arduino Helpers library.
#include <AH/Hardware/ExtendedInputOutput/ShiftRegisterOut.hpp>
using namespace ExtIO; // Bring the ExtIO pin functions into your sketch

#include "Wire.h"

#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>

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
/************************* Ethernet Client Setup *****************************/
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

//Uncomment the following, and set to a valid ip if you don't have dhcp available.
//IPAddress iotIP (192, 168, 0, 42);
//Uncomment the following, and set to your preference if you don't have automatic dns.
//IPAddress dnsIP (8, 8, 8, 8);
//If you uncommented either of the above lines, make sure to change "Ethernet.begin(mac)" to "Ethernet.begin(mac, iotIP)" or "Ethernet.begin(mac, iotIP, dnsIP)"


/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "192.168.50.133"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "mosquitto"
#define AIO_KEY         "1234"


/************ Global State (you don't need to change this!) ******************/

//Set up the ethernet client
EthernetClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }


/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/Habr/Temp");//mosquitto/Habr/Temp

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/sw/");

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);

  Serial.println(F("Adafruit MQTT demo"));

  // Initialise the Client
  Serial.print(F("\nInit the Client..."));
  Ethernet.begin(mac);
  delay(1000); //give the ethernet a second to initialize
  

  mqtt.subscribe(&onoffbutton);
}

float x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
 
  // this is our 'wait for incoming subscription packets' busy subloop
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
   
    if (subscription == &onoffbutton) {
    
      String status = (char *)onoffbutton.lastread;
      Serial.println(status);
      if(status.equals("on1")){
        digitalWrite(ledPin1,HIGH);
        }
      
     if(status.equals("of1")){digitalWrite(ledPin1,LOW);
     }
    }

    
  }

  // Now we can publish stuff!
  // Serial.print(F("\nSending photocell val "));
  // Serial.print(x);
  // Serial.print("...");
  // if (! photocell.publish(x++)) {
  //   Serial.println(F("Failed"));
  // } else {
  //   Serial.println(F("OK!"));
  // }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

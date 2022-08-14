/* 
* For two 4051 multiplexers parallel wiring
*/

// Define constants
const int s0Pin = 2;  // multiplexer select pins
const int s1Pin = 3;
const int s2Pin = 4;
const int mux1 = 0;   // analogue port multiplexer 1 is read on
const int mux2 = 1;   // analogue port multiplexer 2 is read on
const byte channel = 0; // 

// Variable definitions
int currentState[16]; // current state of sensors
int lastState[16];    // the last state of the sensors

// Start of code
void setup() {
  //  set the states of the I/O pins to drive the sensor multiplexer:
   pinMode(s0Pin, OUTPUT);
   pinMode(s1Pin, OUTPUT);
   pinMode(s2Pin, OUTPUT);
   Serial.begin(9600); 
}

//********************* MAIN LOOP ***********************************

void loop() {
    doSensorScan();
    Serial.print("Ch0=");
    Serial.println(currentState[0]);
    Serial.print("Ch1=");
    Serial.println(currentState[1]);
    Serial.print("Ch8=");
    Serial.println(currentState[8]);
    delay(1000);
    } // end loop function
    
//********************* Functions *********************************** 

void doSensorScan() {
 for(int i=0; i<8; i++){
   // select multiplexer channel
   digitalWrite(s0Pin, i & 0x1);
   digitalWrite(s1Pin, (i>>1) & 0x1);
   digitalWrite(s2Pin, (i>>2) & 0x1);
   currentState[i] = analogRead(mux1); // dummy read to allow sample & hold capacitor to charge
   currentState[i] = analogRead(mux1); // read mux1 in first 8 array locations
   currentState[i+8] = analogRead(mux2); // dummy read to allow sample & hold capacitor to charge
   currentState[i+8] = analogRead(mux2); // read mux2 in last 8 array locations
 }  
}

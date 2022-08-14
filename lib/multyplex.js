var mux1 = A0;// analog pin cinnected to mux1
var mux2 = A1; //analog pin connected to mux 2
var S0_PIN = P13;// multyplex select digital pins
var S1_PIN = P7;// multyplex select digital pins
var S2_PIN = P9;// multyplex select digital pins
var dataArray = new Array (16);
  for (var i=0; i<8; i++) { 
    digitalWrite ( S0_PIN, i & 0x01);
    digitalWrite ( S1_PIN, i>>1 & 0x01);
    digitalWrite ( S2_PIN, i>>2 & 0x01);
    dataArray[i]=analogRead(mux1);
    dataArray[i+8]=analogRead(mux2);
  } 
console.log (dataArray[0]);//read analog pins mux1
console.log (dataArray[1]);
console.log (dataArray[2]);//3.3 v- 1.00
console.log (dataArray[3]);
console.log (dataArray[4]);
console.log (dataArray[5]);
console.log (dataArray[6]);
console.log (dataArray[7]);

console.log (dataArray[8]); // mux2 -0
console.log (dataArray[9]);// mux2 -1
console.log (dataArray[10]);// read analog pins mux2
console.log (dataArray[11]);
console.log (dataArray[12]);
console.log (dataArray[13]);
console.log (dataArray[14]);
console.log (dataArray[15]);//











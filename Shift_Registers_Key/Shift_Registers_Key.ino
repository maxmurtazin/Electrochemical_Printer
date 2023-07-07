
//Контакт SH_CP
int SH_CP = 2;
//Контакт ST_CP
int ST_CP = 3;
//Контакт DS
int DS = 4;
 
void setup() {
   // Настроим выходы SH_CP, ST_CP, DS
   pinMode(SH_CP, OUTPUT);
   pinMode(ST_CP, OUTPUT);
   pinMode(DS, OUTPUT);
}
 
void loop() {
   for (int i = 0; i < 256; i++) {
      // Вызовем начало приема данных
      digitalWrite(ST_CP, LOW);
      // Последовательная передача данных на Контакт DS
      shiftOut(DS, SH_CP, MSBFIRST, i);
      // Вызовем окончание передачи данных.
      // Теперь сдвиговый регистр подаст напряжение на указанные выходы
      digitalWrite(ST_CP, HIGH);
      // Задержка в 1 секунду
      delay(1000);
   }
}
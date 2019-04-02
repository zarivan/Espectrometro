/*
MODE0 	MODE1 	MODE2 	Microstep Resolution
0  Low 	Low 	Low 	Full step
1  High 	Low 	Low 	Half step
2  Low 	High 	Low 	1/4 step
3  High 	High 	Low 	1/8 step
4  Low 	Low 	High 	1/16 step
5  High 	Low 	High 	1/32 step
6  Low 	High 	High 	1/32 step
7  High 	High 	High 	1/32 step
*/
void tipoPaso(int inc_muestras){

switch(inc_muestras){
  case 0:
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  delay(500);
  break;

  case 1:
  digitalWrite(M0,HIGH);
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  delay(500);
  break;

  case 2:
  digitalWrite(M0,LOW);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,LOW);
  delay(500);
  break;

  case 3:
  digitalWrite(M0,HIGH);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,LOW);
  delay(500);
  break;

  case 4:
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);
  digitalWrite(M2,HIGH);
  delay(500);
  break;

  case 5:
  digitalWrite(M0,HIGH);
  digitalWrite(M1,LOW);
  digitalWrite(M2,HIGH);
  delay(500);
  break;

  case 6:
  digitalWrite(M0,LOW);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  delay(500);
  break;

  case 7:
  digitalWrite(M0,HIGH);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  delay(500);
  break;

  default:
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  delay(500);
  break;

}
}

int k = 1;
int tPaso = 10;
void potUP(int valor){

  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(UD, HIGH);
  delay(10);
  digitalWrite(CSEL,LOW);
  for(k=0;k<valor;k++){
    digitalWrite(INC, HIGH);
    delay(tPaso);
    digitalWrite(INC, LOW);
    delay(10);
  }
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
}
void potDOWN(int valor){
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(UD, LOW);
  delay(10);
  digitalWrite(CSEL,LOW);
  for(k=0;k<valor;k++){
    digitalWrite(INC, HIGH);
    delay(tPaso);
    digitalWrite(INC, LOW);
    delay(10);
  }
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
}

void potCero(){
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(UD, LOW);
  delay(10);
  digitalWrite(CSEL,LOW);
  for(k=0;k<100;k++){
    digitalWrite(INC, HIGH);
    delay(tPaso);
    digitalWrite(INC, LOW);
    delay(10);
  }
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
}
void potInicio(int valor){
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(UD, HIGH);
  delay(10);
  digitalWrite(CSEL,LOW);
  for(k=0;k<valor;k++){
    digitalWrite(INC, HIGH);
    delay(tPaso);
    digitalWrite(INC, LOW);
    delay(10);
  }
  digitalWrite(CSEL, HIGH);
  digitalWrite(INC, HIGH);
}

void potReset(){

    digitalWrite(INC, HIGH);
    delay(5);
    digitalWrite(CSEL, LOW);
    delay(5);
    digitalWrite(CSEL, HIGH);
    delay(50);

}

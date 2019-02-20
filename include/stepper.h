void encender(){
    digitalWrite(act1, HIGH);

    digitalWrite(sleep, LOW); //habilita el motor.
    digitalWrite(dire, LOW); //dirección del motor.
    digitalWrite(paso, HIGH); //velocidad constante del giro.
    delayMicroseconds(velH);
    digitalWrite(paso, LOW);
    delayMicroseconds(velL);
}


void apagar(){
  digitalWrite(sleep, HIGH);
  digitalWrite(paso, LOW);
  digitalWrite(act1, LOW);
}

void pasoMotor() {
  digitalWrite(sleep, LOW);
  digitalWrite(dire, HIGH);
  digitalWrite(paso, HIGH);
  delayMicroseconds(velH);
  digitalWrite(paso, LOW);
  delayMicroseconds(velL);
}

void retorno() {
  digitalWrite(sleep, LOW);
  digitalWrite(dire, LOW);
  digitalWrite(paso, HIGH);
  delayMicroseconds(velH);
  digitalWrite(paso, LOW);
  delayMicroseconds(velL);
}

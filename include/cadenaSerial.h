long int cadenaS(){
  if(Serial.available() == 9){
  //accion
    A = Serial.read();
  //pasos
    long pasoE = Serial.read()-48;
    pasoE *= 10000;
    int pasoD = Serial.read()-48;
    pasoD *= 1000;
    int pasoC = Serial.read()-48;
    pasoC *=100;
    int pasoB = Serial.read()-48;
    pasoB *=10;
    int pasoA = Serial.read()-48;
    pasosM =pasoE + pasoD + pasoC + pasoB + pasoA;
    return pasosM;
    //muestras.
    int error = Serial.read();
    error = error * 0;
    int muestra1 = Serial.read()-48;
    muestra1 *= 10;
    int muestra2 = Serial.read()-48;
    inc_muestras = muestra1+muestra2;
  }
  return inc_muestras;
}

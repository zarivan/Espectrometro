void rellenar(){
  if(posicion >= 0){
    Serial.print('+');
    if(posicion < 10000)
    {
      Serial.print(0);

      if(posicion<1000){

        Serial.print(0);

        if(posicion<100){

        Serial.print(0);

        if(posicion<10 ){

           Serial.print(0);
          }
        }
      }
    }
  }else{

    if(posicion > -10000)
    {
      Serial.print(0);

      if(posicion > -1000){

        Serial.print(0);

        if(posicion > -100){

        Serial.print(0);

        if(posicion > -10 ){

           Serial.print(0);


        }
        }
      }
    }
  }

}
void Srellenar(){
  if(promedio<10000)
  {
    Serial.print(0);
    if(promedio<1000){

      Serial.print(0);
      if(promedio<100){

        Serial.print(0);
        if(promedio<10){
           Serial.print(0);
        }
      }
    }
  }
}
void imprimir(){
   Serial.print("p");
   rellenar();
   Serial.print(posicion);
   Serial.print(",");
   Serial.print(S);
   Srellenar();
   Serial.println(promedio);
   S = 'V';
    }
void borrar(){
    A = 'Z';
    S = 'V';
    pasosM = 0;
}

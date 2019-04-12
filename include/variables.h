void rellenar2(int valorR){
  if(valorR >= 0){
    Serial.print('+');
    if(valorR < 10000)
    {
      Serial.print(0);

      if(valorR<1000){

        Serial.print(0);

        if(valorR<100){

        Serial.print(0);

        if(valorR<10 ){

           Serial.print(0);
          }
        }
      }
    }
  }else{

    if(valorR > -10000)
    {
      Serial.print(0);

      if(valorR > -1000){

        Serial.print(0);

        if(valorR > -100){

        Serial.print(0);

        if(valorR > -10 ){

        Serial.print(0);
          }
        }
      }
    }
  }

}

//imprimir velocidad al inicio del programa y apartir de ahí solo cuando la velocidad sea
//necesaria enviarse de nuevo.
//solición temporal.
void imprimir(int valor){
   Serial.print("p");
   rellenar2(posicion);
   Serial.print(posicion);
   Serial.print(",");
   Serial.print(S);
   rellenar2(valor);
   Serial.println(valor);
   S = 'V';
    }
void borrar(){
    A = 'Z';
    S = 'V';
    pasosM = 0;
}

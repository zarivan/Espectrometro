//velocidad del ADC
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

// variables de entrada y salida para activar el encoder 1 y 2.

#define PMT A0
#define act1 13
#define enc1 12
// cambiar las salidas, por el POTdigital.
#define INC 23
#define UD 25
#define CS 27
// se pueden desconectar estos encoders y el EN y utilizar el pot digital.
#define act2 11
#define enc2 10
//definen salidas de motor y tipo de pasao.
#define EN 9

#define M0 8
#define M1 7
#define M2 6
//tabla de tipo de paso.
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

//*********************** Se modifican mientras no se usen, para probarse con arduino uno
//se definen las entradas y salidas del motor.
#define reset 5
#define sleep 4
#define paso 3
#define dire 2

int velH = 100;
long velL = 900;
long velT = 0;
char S = 'V';
char A = 'Z';
int inc_muestras = 1;
long pasosM = 0;
long i = 1; long j = 1;
long posicion = 0;
long promedio = velL;
long contarPaso = 0;

#include <Arduino.h>
#include "stepper.h"
//#include "cadenaSerial.h"
#include "variables.h"
#include "ADCprom.h"

void setup() {
  Serial.begin(115200);

  cbi(ADCSRA, ADPS2); // 1 0 0
  sbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);

  /*
  Prescale 	ADPS2 ADPS1 ADPS0 	Clock freq (MHz) 	Sampling rate (KHz)
        2 	0     0     1 	    8 	              615
        4 	0     1     0 	    4 	              307
        8 	0     1     1 	    2 	              153
        16 	1     0     0 	    1 	              76.8
        32 	1     0     1 	    0.5 	            38.4
        64 	1     1     0 	    0.25             	19.2
      128 	1     1     1 	    0.125 	          9.6
  */

  pinMode(PMT, INPUT);

  pinMode(CS, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(INC, OUTPUT);


  pinMode(act1, OUTPUT);
  pinMode(enc1, INPUT);
  pinMode(act2, OUTPUT);
  pinMode(enc2, INPUT);

  pinMode(EN, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(reset, OUTPUT);
  pinMode(sleep, OUTPUT);
  pinMode(paso, OUTPUT);
  pinMode(dire, OUTPUT);


  digitalWrite(act1, LOW);
  digitalWrite(act2, LOW);


  //************************************
  digitalWrite(EN, LOW);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);

  digitalWrite(reset, LOW);
  digitalWrite(sleep, HIGH);
  digitalWrite(paso, LOW);
  digitalWrite(dire, LOW);

  //potCero();

}

void loop() {
  // put your main code here, to run repeatedly:
  imprimir();
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
  //muestras.
  int error = Serial.read();
  error = error * 0;
  int muestra1 = Serial.read()-48;
  muestra1 *= 10;
  int muestra2 = Serial.read()-48;
  inc_muestras = muestra1+muestra2;
}
  switch(A){
   case 'a':
   //Serial.println("a");
   for(int v=0; v<2; v++){
     while(digitalRead(enc1) == true){
        encender();
      }
    delay(1000);
    velT = velL;
    if(digitalRead(enc1) == false){
      borrar();
      posicion = 0;
      velL = 1000;
      digitalWrite(act1, HIGH);
    }
    for(int k = 0; k<400; k++){
      pasoMotor();
    }
      velL = velT;

  }
   break;


   case 'b':
   for (j = 1; j <= pasosM; j++){
   retorno();
   posicion--;
   imprimir();
   }

   borrar();

   break;


   //*****************contar ceros*************************************
   case 'c': // contador de puntos en alto, puede servir para el control.
   //    contador();

   while(digitalRead(enc1) == true){
     contarPaso = 0;
     //Serial.println("avanzando");
     encender();
   }
   delay(1000);
   while(digitalRead(enc1) == false){
     //Serial.print("contando: ");
     contarPaso = contarPaso+1;
     retorno();
     //Serial.println(contarPaso);
   }
   delay(1000);
   if(digitalRead(enc1) == true && contarPaso != 0){

     apagar();
     borrar();
   }
   break;
   //********************************************************************
   case 'm':

   for (j = 1; j <= pasosM; j++){
     pasoMotor();
     //promedio = analogRead(PMT);
     posicion++;
     S = 's';
     promedio = lecturaADCn(inc_muestras);
     imprimir();

   }
   borrar();
   break;



   case 'p':
   j = 1;

   digitalWrite(act1, HIGH);


   for (j = 1;j <= pasosM; j++){
     pasoMotor();
     posicion++;
     imprimir();
   }
   j = 1;
   borrar();

   digitalWrite(act1, LOW);
   break;

   case 't':
   tipoPaso();
   default;

   case 'V':
    delay(500);
    velL = pasosM;
    delay(1000);
    promedio = velL;
    borrar();
    break;
//******************************************************************

default:
    apagar();
    borrar();
break;
 }
}

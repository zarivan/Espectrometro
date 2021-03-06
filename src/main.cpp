//Esta línea solo se agrego para ver si funciona el git-merge
// variables de entrada y salida para activar el encoder 1 y 2.
#define PMT A0
#define conPMT A1

#define act1 13 //salidad
#define enc1 12 //entrada, regreso del encoder.

// se pueden desconectar estos encoders y el EN y utilizar el pot digital.
#define act2 11
#define enc2 10


#define UD 7
#define INC 6
#define CSEL 5

//definen salidas de motor y tipo de paso. Cuack

#define EN 9
#define M0 22
#define M1 24
#define M2 26

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
#define reset 28
#define sleep 4
#define paso 3
#define dire 2

int ganPMT = 0, velH = 100, inc_muestras = 1, potDig = 30, PMT_contador = 0, promPMT = 0, Stop = 1, promGan = 0, pGan = 10;
char S = 'V', A = 'Z', P = 'p';
long velL = 29900, pasosM = 15099, i = 1, j = 1, posicion = 0, promedio = velL, contarPaso = 0, velT = 0, sumaGan = 0;

#include <Arduino.h>
#include "stepper.h"
#include "microStep.h"
#include "variables.h"
#include "MCP3202.h"
MCP3202 adc = MCP3202(53);
#include "digPot.h"
#include "ADCprom.h"

void setup() {
  Serial.begin(115200);
  adc.begin();
  /* al utilizar un ADC-Externo esto ya no es necesario.
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

  pinMode(CSEL, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(INC, OUTPUT);

  pinMode(act1, OUTPUT); //pin 13
  pinMode(enc1, INPUT); //pin12
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
  digitalWrite(dire, HIGH);

  potCero();
  potInicio(potDig);
  //potInicio(45);
  S = 'v';
  imprimir(velL);
  //delay(100);
  S = 'D';
  imprimir(potDig);
  //delay(2000);
}

void loop() {
  // ganPMT = adc.readChannel(1);
      pGan=100;
      sumaGan=0;
      for(i=1; i<=pGan;i++){
      sumaGan=sumaGan+adc.readChannel(1);
      delayMicroseconds(10);
      }
      promGan = sumaGan/pGan;
    //  imprimir(ganPMT);
      imprimir(promGan);
  //}



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
      S = 's';
      promedio = 0;
      imprimir(promedio);
    
    for(int v=0; v<2; v++){
      while(digitalRead(enc1) == true){
        posicion = 18000;
        imprimir(0);
        encender();

        posicion = 0;
        imprimir(0);


        }

      delay(1000);
      velT = velL;
      if(digitalRead(enc1) == false){
        borrar();
        posicion = 0;
        velL = 4000;
        digitalWrite(act1, HIGH);
      }

      for(int k = 0; k<308; k++){
        pasoMotor();
      }
      velL = velT;
    }
    break;

    case 'b':
    for (j = 1; j <= pasosM; j++){
      retorno();
      posicion--;
      imprimir(ganPMT);
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

    case 'd':
    potDOWN(pasosM);
    S='D';
    imprimir(potDig);
    delay(500);
    borrar();
    break;

    case 'e':
    borrar();
    posicion=0;
    break;

    case 'm':
    for (j = 1; j <= pasosM; j++){
      pasoMotor();
      //promedio = analogRead(PMT);
      posicion++;
      S = 's';
      promedio = lecturaADCn(inc_muestras);
      imprimir(promedio);
    }
    borrar();
    break;

    case 'p':
    j = 1;
    digitalWrite(act1, HIGH);
    for (j = 1;j <= pasosM; j++){
      pasoMotor();
      posicion++;
      imprimir(ganPMT);
    }
    j = 1;
    borrar();
    digitalWrite(act1, LOW);
    break;
    
    case 's':
    potCero();
    potDig = 0;
    sumaGan = 0;
    promGan = 0;
    pGan=10;

    for(int c=1;c<=100;c++)
    {  
      sumaGan = 0;
      for(i=1; i<=pGan;i++){
        sumaGan=sumaGan+adc.readChannel(1);
        delayMicroseconds(10);
      }
      promGan = sumaGan/pGan;

      
      S = 'f';
      P = 'd';
      posicion=potDig;
      imprimir(promGan);
      delay(20);
      potUP(1);

    }
    potCero();
    delay(50);
    borrar();
    posicion = 0;
    potDig =25;
    potInicio(potDig);
    S='D';
    imprimir(potDig);
    
    
    
    break;

    case 't':
    tipoPaso(inc_muestras);
    borrar();
    break;

    case 'u':
    potUP(pasosM);
    S='D';
    imprimir(potDig);
    delay(500);
    borrar();
    break;

    case 'v':
    delay(500);
    velL = pasosM;
    S = 'v';
    imprimir(velL);
    delay(1000);
    borrar();
    break;

    //******************************************************************
    default:
    apagar();
    borrar();
    break;
  }
}

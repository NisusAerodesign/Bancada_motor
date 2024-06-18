#define VIN 35 // define the Arduino pin A0 as voltage input (V in)
#define TIN 15 //input pin to read batery tension
//#define EMG 22 //Pino botao emergencia (ligado no 3.3V e nesse pino) e resistencia de 1k entre ele e o terra
#define Lim 300 //potencia maxima definida
#define rpmin 4
#include <ESP32Servo.h> 
#include "HX711.h"
#define T1In 12, 13 //torq cell 1 input (data, clock)
#define T2In 27, 14 //torq cell 2 input (data, clock)
#define T3In 25, 26 //thrust cell input (data, clock)
HX711 escala1;
HX711 escala2;
HX711 escala3;
Servo servo1;
//int Lim = 300; //potencia maxima
//float volt, corrente, torque, empuxo, command = 0;
int servoPin = 4, strt = 0; 
float c1, c2, c3, c4; 
float tempo = 0;
float delta = 0;
void setup_data() {
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  servo1.setPeriodHertz(50); 
  servo1.attach(servoPin, 1000, 2000);
  pinMode(22, INPUT);
  pinMode(TIN, INPUT);
  pinMode(VIN, INPUT);
  escala1.begin(T1In);
  escala2.begin(T2In);
  escala3.begin(T3In);
  pinMode(rpmin, INPUT);
  attachInterrupt(digitalPinToInterrupt(rpmin), dt, RISING);


}

void dt(){
  delta = millis() - tempo;
  tempo = millis();
}

void loop_data() {
  torque = ((escala1.get_units()+521470.00) + ((escala2.get_units()*1.1564)-674676.00))/2590070.50;
  empuxo = (escala3.get_units()-260407.00)/-44350.00;
  volt = analogRead(TIN)/105.3; //read battery voltage
  if(delta < 100){
  rpm = (15000.0/delta);
  }
  else{
    rpm = 0;
  }
  c4 = c3;
  c3 = c2;
  c2 = c1;
  c1 = abs((analogRead(VIN)/20.4)-146.8);
  corrente = (c1+c2+c3+c4)/4.0;
  //corrente = analogRead(2);
  if(digitalRead(22)==1){
    if((corrente * volt) < 680){
      if((corrente * volt) < 450){
        command = command + 0.4;
      }
      else{
    command = command + 0.1;
      }
    } 
    else{
    command = command - 0.2;
    }
  } 
  else{
    if(command > 2){
      command = command -1.5;
    }
    else{
      command =0;
    }
  }
  servo1.write(command); 
  Serial.print(digitalRead(22));
  Serial.print("\t");
  Serial.print(volt);
  Serial.print(" V\t");
  Serial.print(corrente);
  Serial.print(" A\t");
  Serial.print(volt*corrente);
  Serial.print(" W\t");
  Serial.print(command/1.8);
  Serial.print(" %\t");
  Serial.print(torque);
  Serial.print(" Nm\t");
  Serial.print(empuxo);
  Serial.print(" N\t");
  Serial.print(rpm);
  Serial.println(" rpm");
}

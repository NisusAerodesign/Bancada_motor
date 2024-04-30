#define VIN 2 // define the Arduino pin A0 as voltage input (V in)
#define TIN 15 //input pin to read batery tension

float c1 = 0;
float c2 = 0;
float c3 = 0;
float c4 = 0;
float c5 = 0;
float c6 = 0;
float c7 = 0;
float c8 = 0;
float c9 = 0;
float c10 = 0;
float c11 = 0;
float c12 = 0;
float c13 = 0;
float c14 = 0;
float c15 = 0;
void loop_Power() {
  volt = analogRead(TIN)/105.0; //read battery voltage
  c15 = c14;
  c14 = c13;
  c13 = c12;
  c12 = c11;
  c11 = c10;
  c10 = c9;
  c9 = c8;
  c8 = c7;
  c7 = c6;
  c6 = c5;
  c5 = c4;
  c4 = c3;
  c3 = c2;
  c2 = c1;
  //c1 = ((0.0806521713731583 * analogRead(VIN)) - 150.8092600507063);//this equations was set to 3.3v and 50B sensor
  c1 = ((0.4453612903225806 * analogRead(VIN)) - 228.768734); //this equation was set to 3.3v and 100B sensor
  corrente = abs((c1 +  c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10 + c11 + c12 + c13 + c14 + c15)/15); //mesuremants linearization 
  power = volt * corrente;

} 

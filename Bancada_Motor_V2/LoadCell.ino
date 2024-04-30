#include "HX711.h"
#define T1In 12, 13 //torq cell 1 input (data, clock)
#define T2In 27, 14 //torq cell 2 input (data, clock)
#define T3In 25, 26 //thrust cell input (data, clock)
HX711 escala1;
HX711 escala2;
HX711 escala3;
void setup_LoadCell() {
  
  Serial.begin(115200);
  Serial.println("Rotina de medida com a célula de carga.");
  //escala1 and escala2 are for torq calculation
  escala1.begin(T1In);
  escala2.begin(T2In);
  //escala3 is for thrust
  escala3.begin(T3In);
}
void loop_LoadCell() {
  torq = ((escala1.get_units() + (escala2.get_units()-37000.0))/2390.0);
  //need to check, perhaps calibrate the thrust one
  empuxo = ((escala3.get_units()/(-37191.1))+230.22);
  
}
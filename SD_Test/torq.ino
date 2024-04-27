#include "HX711.h"
HX711 escala1;
HX711 escala2;

void setup_torq() {
  
  Serial.begin(115200);
  Serial.println("Rotina de medida com a célula de carga.");
  escala1.begin(12, 13);
  escala2.begin(27, 14);
}
void loop_torq() {
  torq = ((escala1.get_units() + (escala2.get_units()-37000.0))/2390);

  
}
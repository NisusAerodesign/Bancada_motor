#include <DFRobot_HX711.h>

DFRobot_HX711 MyScale(25,26);
void setup_empuxo() {
  Serial.begin(115200);
  //276864;
  //-369.91;
}

void loop_empuxo() {
  // Get the weight of the object
  empuxo = (((MyScale.getValue()/(-371.91))+23022.0)/100);
}
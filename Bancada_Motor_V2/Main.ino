#define Periodo 16000             // define o periodo em 16 mili segundos para ler o pwm

void setup(){
  Serial.begin(115200);
  setup_sd();
  pinMode(4, INPUT);
  setup_LoadCell();
  setup_rpm();
  Serial.println("torque   empuxo   comando  RPM  tensao    corrente   potencia");
  Serial.println("Did you checked the load cells calibration??");
}

void loop(){
  ttl = (pulseIn(4, HIGH)/10.0)-100.0;  //leitura do duty cycle do pwm, onde 1 milisegundo = 0% e 2milisegundos = 100%
  loop_Power();
  loop_rpm();
  loop_LoadCell();
  loop_sd();
  Serial.print(torq);
  Serial.print("\t");
  Serial.print(empuxo);
  Serial.print("\t");
  Serial.print(ttl);
  Serial.print("\t");
  Serial.print(rpm);
  Serial.print("\t");
  Serial.print(volt);
  Serial.print("\t");
  Serial.print(corrente);
  Serial.print("\t");
  Serial.println(power);

}
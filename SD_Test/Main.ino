float voltage;
float corrente;
float torq;
float volt;
float empuxo;
float ttl;
void setup(){
  Serial.begin(115200);
  setup_empuxo();
  setup_torq();
  setup_pwm();
  setup_sd();
  Serial.println("torque   empuxo   comando  tensao    corrente   potencia");
  Serial.println("N/mm   N   %  V   A   W");
}

void loop(){
  loop_volt();
  loop_corrente();
  loop_empuxo();
  loop_pwm();
  loop_torq();
  loop_sd();
  a1 = torq;
  a2 = empuxo;
  a3 = volt;
  a4 = corrente;
  a5 = ttl;

  Serial.print(torq);
  Serial.print("\t");
  Serial.print(empuxo);
  Serial.print("\t");
  Serial.print(ttl);
  Serial.print("\t");
  Serial.print(volt);
  Serial.print("\t");
  Serial.print(corrente);
  Serial.print("\t");
  Serial.println(volt * corrente);

}
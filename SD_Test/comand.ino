#define Periodo 16000             // define o periodo em 16 mili segundos


void setup_pwm() {
  pinMode(4, INPUT);               // Configura pino 9 como entrada

  Serial.begin(115200);
  delay(100);
}

void loop_pwm() {
  ttl = (pulseIn(4, HIGH)/10.0)-100.0;


}
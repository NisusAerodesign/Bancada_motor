#define pino 33
uint32_t tempo = 0;
uint32_t delta = 0;
hw_timer_t *timer = NULL;

void setup_rpm() {
  attachInterrupt(digitalPinToInterrupt(pino), dt, RISING);
  timerAttachInterrupt(timer, timeout, true);
  timerAlarmWrite(timer, 250000, true);
  timerAlarmEnable(timer);
  

}
void dt(){
  delta = micros() - tempo;
  tempo = micros();
  rpm = (8571428.57/delta);
  timer = timerBegin(0, 80, true);
}
void timeout(){
  rpm = 0;
  timer = timerBegin(0, 80, true);
}
void loop_rpm() {
}

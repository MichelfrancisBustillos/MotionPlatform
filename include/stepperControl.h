extern Adafruit_StepperMotor *motor1;
extern Adafruit_StepperMotor *motor2;

void forwardstep1() {
  motor1->onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  motor1->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {
  motor2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  motor2->onestep(BACKWARD, DOUBLE);
}
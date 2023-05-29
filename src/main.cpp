#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include "stepperControl.h"

//Function Definitions
int SerialIO();
int getDistance();

//Pin Definitions
#define trigPin 13 //Ultrasonic trigger pin
#define echoPin 12 //Ultrasonic echo pin

//Global Variable and Object Definitions
int motorRPM = 1000; //Motor standard RPM, also used for acceleration
int motorMaxRPM = 1000; //Motor max RPM
int stepsPerRotation = 200; //Steps per 1 rotation of stepper motor
Adafruit_MotorShield motorshield = Adafruit_MotorShield(); //Adafruit MotorShield Object
Adafruit_StepperMotor *motor1 = motorshield.getStepper(stepsPerRotation, 2); //Stepper motor object pointer
Adafruit_StepperMotor *motor2 = motorshield.getStepper(stepsPerRotation, 1); //Stepper motor object pointer
AccelStepper stepper1(forwardstep1,backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

void setup() {
  //Initialize Serial Coms
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial Initialized!");

  //Initialize Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Initialize Motorshield
  if(!motorshield.begin()){
    Serial.println("Could not find Motor Shield!");
    while(1);
  }
  Serial.println("Motorshield Initialized!");

  //Initialize Stepper Settings
  stepper1.setMaxSpeed(motorMaxRPM); 
  stepper1.setSpeed(motorRPM);
  stepper1.setAcceleration(motorRPM);
  stepper2.setMaxSpeed(motorMaxRPM);
  stepper2.setSpeed(motorRPM); 
  stepper2.setAcceleration(motorRPM);

  TWBR = ((F_CPU /400000l) - 16) / 2; // Change the i2c clock to 400KHz
}

void loop() {
  int steps = SerialIO();
  int distance = getDistance();

  if ((distance < 10) && (distance > 0)){
    Serial.print("Obstacle detected! Distance: ");
    Serial.println(distance);
    steps = 1;
  }

  if(stepper1.distanceToGo() == 0){
    stepper1.move(steps);
  }
  if(stepper2.distanceToGo() == 0){
    stepper2.move(steps);
  }

  stepper1.run();
  stepper2.run();
}

int SerialIO(){
  String userInput = "";
  int steps = 0;
  if(Serial.available()){
    userInput = Serial.readStringUntil('\n');
    steps = (userInput.toDouble() * stepsPerRotation);
    Serial.print("Moving... ");
    Serial.print(userInput.toDouble());
    Serial.print(" rotations (");
    Serial.print(steps);
    Serial.println(" steps).");
  }
  return steps;
}

int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
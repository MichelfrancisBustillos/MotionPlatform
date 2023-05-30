#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <NewPing.h>
#include "stepperControl.h"

//Function Definitions
int SerialIO();
void getDistance();

//Pin Definitions
#define trigPin 13 //Ultrasonic trigger pin
#define echoPin 12 //Ultrasonic echo pin

//Global Variable and Object Definitions
int motorMaxSPS = 520; //Motor max steps per second
int stepsPerRotation = 200; //Steps per 1 rotation of stepper motor
unsigned int pingSpeed = 50; //Ping frequency in MS
unsigned long pingTimer; //Place holder for next ping time
int distance; //Distance from obstacle
Adafruit_MotorShield motorshield = Adafruit_MotorShield(); //Adafruit MotorShield Object
Adafruit_StepperMotor *motor1 = motorshield.getStepper(stepsPerRotation, 2); //Stepper motor object pointer
Adafruit_StepperMotor *motor2 = motorshield.getStepper(stepsPerRotation, 1); //Stepper motor object pointer
AccelStepper stepper1(forwardstep1,backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
NewPing sonar(trigPin, echoPin); //Ultrasonic sensor object

void setup() {
  //Initialize Serial Coms
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial Initialized!");

  //Initialize Pins
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);

  //Initialize Motorshield
  if(!motorshield.begin()){
    Serial.println("Could not find Motor Shield!");
    while(1);
  }
  Serial.println("Motorshield Initialized!");

  //Initialize Stepper Settings
  stepper1.setMaxSpeed(motorMaxSPS); 
  stepper1.setAcceleration(motorMaxSPS);
  stepper2.setMaxSpeed(motorMaxSPS);
  stepper2.setAcceleration(motorMaxSPS);

  pingTimer = millis(); //Start ping timer

  TWBR = ((F_CPU /400000l) - 16) / 2; // Change the i2c clock to 400KHz
}

void loop() {
  //Set motor speed to 50% of max
  stepper1.setSpeed((motorMaxSPS/2));
  stepper2.setSpeed((motorMaxSPS/2));
  
  //Get Input (Serial & Ultrasonic)
  int steps = SerialIO();

  if (millis() >= pingTimer){
    pingTimer += pingSpeed;
    sonar.ping_timer(getDistance);
  }

  if (distance < 10){
    Serial.print("Obstacle detected! Distance: ");
    Serial.println(distance);
    stepper1.stop();
    stepper2.stop();
  }

  if(stepper1.distanceToGo() == 0){
    stepper1.move(steps);
  }
  if(stepper2.distanceToGo() == 0){
    stepper2.move(steps);
  }

  stepper1.runSpeedToPosition();
  stepper2.runSpeedToPosition();
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

void getDistance(){
  if (sonar.check_timer()){
    distance = (sonar.ping_result / US_ROUNDTRIP_CM);
  }
} 
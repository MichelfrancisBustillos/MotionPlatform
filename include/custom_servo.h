#ifndef custom_servo_h
#define custom_servo_h
#include <ESP32Servo.h>

class custom_servo {
  public:
    Servo servo;
    int max;
    int min;
    int pin;
    int wait;
    int current_position;
    int center = ((max+min)/2);
    int home_position;
    void move(int);
    void home();
};

void custom_servo::move(int movement){
        Serial.print("Received: ");
        Serial.println(movement);
        if (movement >= min && movement <= max){
            servo.attach(pin);
            servo.write(movement);
            delay(wait);
            servo.detach();
        } else {
            Serial.println("Invalid movement!");
        }
    }

void custom_servo::home(){
    Serial.print("Homing servo...");
    servo.write(home_position);
}

#endif
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
    void move(int);
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

#endif
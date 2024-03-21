#include <Arduino.h>

struct Motor {
    int pin;
    int pwm;
};

// Pin 3 and 5 are PWM capable
const Motor right = {2, 3};
const Motor left = {4, 5};
int speed = 0;

void motorControl(Motor motor, int speed);
void straight(int speed);
void rotate(int speed);

//---------------------------------------------------------------------------------

void setup() {
    pinMode(right.pin, OUTPUT);
    pinMode(right.pwm, OUTPUT);
    pinMode(left.pin, OUTPUT);
    pinMode(left.pwm, OUTPUT);

    speed = 255;

    Serial.begin(9600);
    Serial.println("ON");
}

void loop() {
    straight(speed);
    delay(5000);
    straight(-speed);
    delay(5000);
}

//---------------------------------------------------------------------------------

void motorControl(Motor motor, int speed) {
    if (speed > 0) {
        digitalWrite(motor.pin, 0);
        analogWrite(motor.pwm, speed);
    } else {
        digitalWrite(motor.pin, 1);
        analogWrite(motor.pwm, (255 + speed));
    }
}

void straight(int speed) {
    motorControl(right, speed);
    motorControl(left, speed);
    Serial.print("Forward: ");
    Serial.println(speed);
}

void rotate(int speed) {
    Serial.print("Rotate: ");
    motorControl(right, speed);
    motorControl(left, -speed);
    Serial.println(speed);
}

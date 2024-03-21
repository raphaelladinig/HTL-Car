#include <Arduino.h>

struct Motor {
    int pin1;
    int pin2;
};

const Motor right = {2, 3};
const Motor left = {4, 5};
int speed = 0;

void motorControl(Motor motor, int speed);
void straight(int speed);
void rotate(int speed);

//---------------------------------------------------------------------------------

void setup() {
    pinMode(right.pin1, OUTPUT);
    pinMode(right.pin2, OUTPUT);
    pinMode(left.pin1, OUTPUT);
    pinMode(left.pin2, OUTPUT);

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
        analogWrite(motor.pin1, speed);
        analogWrite(motor.pin2, 0);
    } else {
        analogWrite(motor.pin1, 0);
        analogWrite(motor.pin2, abs(speed));
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

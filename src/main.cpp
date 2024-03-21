#include <Arduino.h>

struct Motor {
    int in;
    int out;
};

const Motor right = {2, 3};
const Motor left = {4, 5};
int speed = 0;

void motorControl(Motor motor, int speed);
void forward(int speed);
void backward(int speed);

//---------------------------------------------------------------------------------

void setup() {
    pinMode(right.in, OUTPUT);
    pinMode(right.out, OUTPUT);
    pinMode(left.in, OUTPUT);
    pinMode(left.out, OUTPUT);

    speed = 255;

    Serial.begin(9600);
    Serial.println("ON");
}

void loop() {
    forward(speed);
    delay(5000);
    backward(speed);
    delay(5000);
}

//---------------------------------------------------------------------------------

void motorControl(Motor motor, int speed) {
    if (speed > 0) {
        analogWrite(motor.in, speed);
        analogWrite(motor.out, 0);
    } else {
        analogWrite(motor.in, 0);
        analogWrite(motor.out, abs(speed));
    }
}

void forward(int speed) {
    motorControl(right, speed);
    motorControl(left, speed);
    Serial.print("Forward: ");
    Serial.println(speed);
}

void backward(int speed) {
    motorControl(right, -speed);
    motorControl(left, -speed);
    Serial.print("Backward: ");
    Serial.println(speed);
}

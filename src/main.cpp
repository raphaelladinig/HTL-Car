#include <Arduino.h>

struct Motor {
    int in;
    int out;
};

const Motor right = {2, 3};
const Motor left = {4, 5};

void forward(Motor motor);
void backward(Motor motor);

//---------------------------------------------------------------------------------

void setup() {
    pinMode(right.in, OUTPUT);
    pinMode(right.out, OUTPUT);
    pinMode(left.in, OUTPUT);
    pinMode(left.out, OUTPUT);

    Serial.begin(9600);
    Serial.println("ON");
}

void loop() {
    forward(right);
    forward(left);
    delay(5000);
    backward(right);
    backward(left);
}

//---------------------------------------------------------------------------------

void forward(Motor motor) {
    analogWrite(motor.in, 255);
    analogWrite(motor.out, 0);
}

void backward(Motor motor) {
    analogWrite(motor.in, 0);
    analogWrite(motor.out, 255);
}

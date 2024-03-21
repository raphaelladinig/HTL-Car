#include <Arduino.h>

struct Motor {
    int in;
    int out;
};

const Motor right = {2, 3};
const Motor left = {4, 5};

void setup() {
    pinMode(right.in, OUTPUT);
    pinMode(right.out, OUTPUT);
    pinMode(left.in, OUTPUT);
    pinMode(left.out, OUTPUT);
    
    Serial.begin(9600);
    Serial.println("ON");
}

void loop() {
    analogWrite(right.in, 255);
    analogWrite(right.out, 0);
}

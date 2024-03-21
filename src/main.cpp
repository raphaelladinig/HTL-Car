#include <Arduino.h>

struct Motor {
    int noPWM;
    int PWM;
};

const Motor right = {2, 3}; // Pin 3 and 5 are PWM capable
const Motor left = {4, 5};
int speed = 0;

void motorControl(Motor motor, int speed);
void straight(int speed);
void rotate(int speed);

//---------------------------------------------------------------------------------

void setup() {
    pinMode(right.noPWM, OUTPUT);
    pinMode(right.PWM, OUTPUT);
    pinMode(left.noPWM, OUTPUT);
    pinMode(left.PWM, OUTPUT);

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
        digitalWrite(motor.noPWM, 0);
        analogWrite(motor.PWM, speed);
    } else {
        digitalWrite(motor.noPWM, 1);
        analogWrite(motor.PWM, (255+speed));
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

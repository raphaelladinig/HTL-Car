#include "SoftwareSerial.h"
#include "bluetooth.h"
#include "car.h"
#include "motor.h"
#include <Arduino.h>

// Pin 3 and 5 are PWM capable
Car car = {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {11, 12}, 0};
SoftwareSerial bt(10, 0);

void setup() {
    pinMode(car.right.noPwm, OUTPUT);
    pinMode(car.right.pwm, OUTPUT);
    pinMode(car.left.noPwm, OUTPUT);
    pinMode(car.left.pwm, OUTPUT);
    pinMode(car.ultrasonicLeft.echo, OUTPUT);
    pinMode(car.ultrasonicLeft.trig, INPUT);
    pinMode(car.ultrasonicRight.echo, OUTPUT);
    pinMode(car.ultrasonicRight.trig, INPUT);
    pinMode(car.ultrasonicMiddle.echo, OUTPUT);
    pinMode(car.ultrasonicMiddle.trig, INPUT);

    Serial.begin(9600);
    Serial.println("Car started");
}

void loop() {
    Value value = btQuery(bt);
    if (value.id != 0) {
        switch (value.id) {
        case 'G': // Go
            car.speed = abs(car.speed);
            car.move();
            break;
        case 'S': // Stop
            car.stop();
            break;
        case 'R': // Reverse
            car.speed = -abs(car.speed);
            car.move();
            break;
        case 'V': // Velocity
            car.speed = value.value;
            break;
        case 'Y': // Curve
            car.curve(value.value);
            break;
        }
    }
}

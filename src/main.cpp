#include "HardwareSerial.h"
#include "car.h"
#include <Arduino.h>

// Pin 3 and 5 are PWM capable
Car car = {{2, 3, false}, {4, 5, false}, {6, 7}, {8, 9}, {11, 12}, 255};
int curveDistance = 75;

void setup() {
    // setup car
    pinMode(car.right.noPwm, OUTPUT);
    pinMode(car.right.pwm, OUTPUT);
    pinMode(car.left.noPwm, OUTPUT);
    pinMode(car.left.pwm, OUTPUT);
    pinMode(car.ultrasonicLeft.trig, OUTPUT);
    pinMode(car.ultrasonicLeft.echo, INPUT);
    pinMode(car.ultrasonicRight.trig, OUTPUT);
    pinMode(car.ultrasonicRight.echo, INPUT);
    pinMode(car.ultrasonicMiddle.trig, OUTPUT);
    pinMode(car.ultrasonicMiddle.echo, INPUT);

    Serial.begin(9600);

    Serial.println("Car started");
}

void loop() {
    double form = 0.0;

    if (car.ultrasonicLeft.distance() < curveDistance * 0.5 ||
        car.ultrasonicMiddle.distance() < curveDistance ||
        car.ultrasonicLeft.distance() < curveDistance * 0.5) {
        if (car.ultrasonicLeft.distance() < car.ultrasonicRight.distance()) {
            form = map(car.ultrasonicLeft.distance(), 0, curveDistance * 0.5, 0,
                       curveDistance * 2) /
                   10.0;
        } else {
            form = -map(car.ultrasonicRight.distance(), 0, curveDistance * 0.5,
                        0, curveDistance * 2) /
                   10.0;
        }
    }

    car.move(form);
}

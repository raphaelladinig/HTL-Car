#include "car.h"
#include <Arduino.h>

// Pin 3 and 5 are PWM capable
Car car = {{2, 3, false}, {4, 5, false}, {6, 7}, {8, 9}, {11, 12}, 255};

int turnDistance = 25;
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
    int form = 0;

    if (car.ultrasonicMiddle.distance() < curveDistance) {
        form = map(car.ultrasonicLeft.distance(), 0, car.speed, 0, 10);
        if (car.ultrasonicLeft.distance() > car.ultrasonicRight.distance()) {
            form = -form;
        }
    }

    if (car.ultrasonicLeft.distance() > turnDistance &&
        car.ultrasonicMiddle.distance() > turnDistance &&
        car.ultrasonicRight.distance() > turnDistance) {
        car.move(form);
    } else {
        while (car.ultrasonicMiddle.distance() < turnDistance) {
            if (car.ultrasonicLeft.distance() <
                car.ultrasonicRight.distance()) {
                car.rotate(car.speed);
            } else {
                car.rotate(-car.speed);
            }
        }
    }
}

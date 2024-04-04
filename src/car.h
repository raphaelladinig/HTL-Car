#ifndef CAR_H
#define CAR_H

#include "motor.h"
#include "ultrasonic.h"
#include <Arduino.h>

struct Car {
    Motor right;
    Motor left;
    Ultrasonic ultrasonicRight;
    Ultrasonic ultrasonicMiddle;
    Ultrasonic ultrasonicLeft;
    int speed;

    void stop();
    void go();
    void move(double form);
    bool safe();
};

#endif

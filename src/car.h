#ifndef CAR_H
#define CAR_H

#include <Arduino.h>
#include "motor.h"

struct Car {
    Motor right;
    Motor left;
    int speed;
    
    void move();
    void rotate();
    void stop();
    void curve(double form);
};

#endif

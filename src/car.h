#ifndef CAR_H
#define CAR_H

#include <Arduino.h>
#include "motor.h"

struct Car {
    Motor right;
    Motor left;
    
    void move(int speed);
    void rotate(int speed);
    void stop();
    void curve(int speed, double form);
};

#endif

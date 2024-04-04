#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

struct Motor {
    int noPwm;
    int pwm;
    bool stopped;
    
    void move(int speed);
};

#endif

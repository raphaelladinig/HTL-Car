#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

struct Motor {
    int noPwm;
    int pwm;
    
    void move(int speed);
    void stop();
};

#endif

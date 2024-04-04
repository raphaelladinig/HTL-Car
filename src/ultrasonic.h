#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

struct Ultrasonic {
    int trig;
    int echo;
    
    double distance();
};

#endif

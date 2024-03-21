#ifndef CAR_H
#define CAR_H

#include "motor.h"

struct Car {
    Motor right;
    Motor left;

    void move(int speed) {
        right.move(speed);
        left.move(speed);
        Serial.println(speed);
    }

    void rotate(int speed) {
        right.move(speed);
        left.move(-speed);
    }

    void stop() {
        right.stop();
        left.stop();
    }

    void curve(int speed, double form) {
        if (form >= 0) {
            right.move(speed);
            left.move(speed / pow(2, form));
        } else {
            form = abs(form);
            right.move(speed / pow(2, form));
            left.move(speed);
        }
    } 
};

#endif

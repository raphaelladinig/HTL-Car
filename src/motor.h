#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

struct Motor {
    int noPwm;
    int pwm;

    void move(int speed) {
        if (speed > 0) {
            digitalWrite(noPwm, LOW);
            analogWrite(pwm, speed);
        } else {
            digitalWrite(noPwm, HIGH);
            analogWrite(pwm, (255 + speed));
        }
    }

    void stop() {
        digitalWrite(noPwm, LOW);
        digitalWrite(pwm, LOW);
    }
};

#endif

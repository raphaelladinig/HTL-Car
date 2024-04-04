#include "motor.h"

void Motor::move(int speed) {
    if (!stopped) {
        if (speed > 0) {
            digitalWrite(noPwm, LOW);
            analogWrite(pwm, speed);
        } else {
            digitalWrite(noPwm, HIGH);
            analogWrite(pwm, (255 + speed));
        }

    } else {
        digitalWrite(noPwm, LOW);
        analogWrite(pwm, 0);
    }
}

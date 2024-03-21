#include "motor.h"

void Motor::move(int speed) {
    if (speed > 0) {
        digitalWrite(noPwm, LOW);
        analogWrite(pwm, speed);
    } else {
        digitalWrite(noPwm, HIGH);
        analogWrite(pwm, (255 + speed));
    }
}

void Motor::stop() {
    digitalWrite(noPwm, LOW);
    digitalWrite(pwm, LOW);
}

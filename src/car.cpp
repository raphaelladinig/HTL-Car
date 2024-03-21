#include "car.h"

void Car::move(int speed) {
    right.move(speed);
    left.move(speed);
    Serial.println(speed);
}

void Car::rotate(int speed) {
    right.move(speed);
    left.move(-speed);
}

void Car::stop() {
    right.stop();
    left.stop();
}

void Car::curve(int speed, double form) {
    if (form >= 0) {
        right.move(speed);
        left.move(speed / pow(2, form));
    } else {
        form = abs(form);
        right.move(speed / pow(2, form));
        left.move(speed);
    }
}

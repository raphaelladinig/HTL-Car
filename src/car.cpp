#include "car.h"

void Car::move(double form) {
    if (safe()) {
        if (form >= 0) {
            right.move(speed);
            left.move(speed / pow(2, form));
        } else {
            form = abs(form);
            right.move(speed / pow(2, form));
            left.move(speed);
        }
    } else {
        stop();
    }
}

void Car::stop() {
    right.stopped = true;
    left.stopped = true;
}

void Car::go() {
    right.stopped = false;
    left.stopped = false;
}

bool Car::safe() {
    return ultrasonicLeft.distance() > 5  && ultrasonicMiddle.distance() > 10 && ultrasonicRight.distance() > 5;
}

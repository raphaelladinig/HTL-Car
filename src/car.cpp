#include "car.h"

void Car::move(double form) {
    if (form >= 0) {
        right.move(speed);
        left.move(speed / pow(2, form));
    } else {
        form = abs(form);
        right.move(speed / pow(2, form));
        left.move(speed);
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

void Car::rotate(int direction) {
    if (direction > 0) {
        right.move(direction);
        left.move(-direction);
    } else {
        right.move(-direction);
        left.move(direction);
    }
}

#include "car.h"

void Car::move() {
    right.move(speed);
    left.move(speed);
    Serial.println(speed);
    // if (safe()) {
    //     right.move(speed);
    //     left.move(speed);
    //     Serial.println(speed);
    // }
}

void Car::rotate() {
    right.move(speed);
    left.move(-speed);
}

void Car::stop() {
    right.stop();
    left.stop();
}

void Car::curve(double form) {
    if (form >= 0) {
        right.move(speed);
        left.move(speed / pow(2, form));
    } else {
        form = abs(form);
        right.move(speed / pow(2, form));
        left.move(speed);
    }
}

bool Car::safe() {
    if (ultrasonicLeft.safe() && ultrasonicMiddle.safe() &&
        ultrasonicRight.safe()) {
        return true;
    } else {
        return false;
    }
}

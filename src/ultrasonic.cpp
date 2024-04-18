#include "ultrasonic.h"

double Ultrasonic::distance() {
    delay(30);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    return pulseIn(echo, HIGH) / 58.0;
}

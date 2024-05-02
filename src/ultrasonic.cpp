#include "ultrasonic.h"

double Ultrasonic::distance() {
    delay(2);
    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);

    return pulseIn(echo, HIGH) / 58.0;
}

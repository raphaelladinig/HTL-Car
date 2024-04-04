#include "ultrasonic.h"

double Ultrasonic::distance() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    return pulseIn(echo, HIGH) / 58.0;
}

bool Ultrasonic::safe() {
    return distance() > 5;
}

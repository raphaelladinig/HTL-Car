#include <Arduino.h>
#include <car.h>

// Pin 3 and 5 are PWM capable
Car car = {{2, 3}, {4, 5}};
int speed = 0;

//---------------------------------------------------------------------------------

void setup() {
    pinMode(car.right.noPwm, OUTPUT);
    pinMode(car.right.pwm, OUTPUT);
    pinMode(car.left.noPwm, OUTPUT);
    pinMode(car.left.pwm, OUTPUT);
    
    speed = 255;

    Serial.begin(9600);
    Serial.println("ON");
}

void loop() {
}

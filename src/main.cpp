#include <Arduino.h>

struct Motor {
    int noPwm;
    int pwm;

    void motorControl(int speed) {
        if (speed > 0) {
            digitalWrite(noPwm, 0);
            analogWrite(pwm, speed);
        } else {
            digitalWrite(noPwm, 1);
            analogWrite(pwm, (255 + speed));
        }
    }

    void stop() {
        digitalWrite(noPwm, 0);
        digitalWrite(pwm, 0);
    }
};

struct Car {
    Motor right;
    Motor left;

    void move(int speed) {
        right.motorControl(speed);
        left.motorControl(speed);
        Serial.print("Forward: ");
        Serial.println(speed);
    }

    void rotate(int speed) {
        Serial.print("Rotate: ");
        right.motorControl(speed);
        left.motorControl(-speed);
        Serial.println(speed);
    }

    void stop() {
        right.stop();
        left.stop();
        Serial.println("Stop");
    }

    void curve(int speed, double form) {
        if (form > 0) {
            right.motorControl(speed);
            left.motorControl(speed / pow(2, form));
        } else {
            right.motorControl(speed / pow(2, form));
            left.motorControl(speed);
        }
    } 
};

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
    speed = 100;
    car.move(speed);
    delay(2000);
    car.curve(speed, -1);
    delay(2000);
    car.curve(speed, 1);
    delay(2000);
}

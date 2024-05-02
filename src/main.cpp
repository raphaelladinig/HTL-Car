#include "HardwareSerial.h"
#include "SoftwareSerial.h"
#include "car.h"
#include <Arduino.h>

const String mode = "auto"; // bt or auto

// Pin 3 and 5 are PWM capable
Car car = {{2, 3, false}, {4, 5, false}, {6, 7}, {8, 9}, {11, 12}, 255};

SoftwareSerial bt(10, 0);
struct Value {
    char id;
    int value;
};
char btChar = ' ';
char btId = ' ';
char btIdTemp = ' ';
bool btIdExpected = true;
bool btNewReading = false;
String btValueString = "";
float btValue;
Value btQuery();

int curveDistance = 75;
int turnDistance = 25;

void setup() {
    // setup car
    pinMode(car.right.noPwm, OUTPUT);
    pinMode(car.right.pwm, OUTPUT);
    pinMode(car.left.noPwm, OUTPUT);
    pinMode(car.left.pwm, OUTPUT);
    pinMode(car.ultrasonicLeft.trig, OUTPUT);
    pinMode(car.ultrasonicLeft.echo, INPUT);
    pinMode(car.ultrasonicRight.trig, OUTPUT);
    pinMode(car.ultrasonicRight.echo, INPUT);
    pinMode(car.ultrasonicMiddle.trig, OUTPUT);
    pinMode(car.ultrasonicMiddle.echo, INPUT);

    bt.begin(9600);
    Serial.begin(9600);

    Serial.println("Car started");
}

void loop() {
    if (mode == "bt") {
        Value value = btQuery();
        if (value.id != 0) {
            switch (value.id) {
            case 'G': // Go
                car.speed = abs(car.speed);
                car.go();
                break;
            case 'S': // Stop
                car.stop();
                break;
            case 'R': // Reverse
                car.speed = -abs(car.speed);
                car.go();
                break;
            case 'V': // Velocity
                car.speed = value.value;
                break;
            case 'Y': // Curve
                car.move(value.value);
                break;
            }
        }
    } else if (mode == "auto") {
        double form = 0.0;

        if (car.ultrasonicLeft.distance() < curveDistance * 0.5 ||
            car.ultrasonicMiddle.distance() < curveDistance ||
            car.ultrasonicLeft.distance() < curveDistance * 0.5) {
            if (car.ultrasonicLeft.distance() <
                car.ultrasonicRight.distance()) {
                form = map(car.ultrasonicLeft.distance(), 0,
                           curveDistance * 0.5, 0, curveDistance * 2) /
                       10.0;
            } else {
                form = -map(car.ultrasonicRight.distance(), 0,
                            curveDistance * 0.5, 0, curveDistance * 2) /
                       10.0;
            }
        }
        if (car.ultrasonicMiddle.distance() < turnDistance) {
            car.speed = -abs(car.speed);
        } else if (car.ultrasonicMiddle.distance() > turnDistance + 10) {
            car.speed = abs(car.speed);
        }

        car.move(form);
    }
}

Value btQuery() {
    Value result = {0, 0};

    btNewReading = false;
    if (bt.available()) {
        btChar = bt.read();
        if (btIdExpected) {
            btIdTemp = btChar;
            btIdExpected = false;
            btValueString = "";
        } else {
            if ((btChar != ' ') && (btChar != '\n')) {
                btValueString += btChar;
            }
            if (btChar == '\n') {
                result.id = btIdTemp;
                result.value = btValueString.toFloat();
                Serial.print(result.id);
                Serial.print(" ");
                Serial.println(result.value);
                btValueString = "";
                btIdExpected = true;
                btNewReading = true;
            }
        }
    }

    return result;
}

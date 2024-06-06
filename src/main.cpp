#include "Adafruit_NeoPixel.h"
#include "HardwareSerial.h"
#include "SoftwareSerial.h"
#include "car.h"
#include <Arduino.h>

const String mode = "bt"; // NOTE: bt or auto

// NOTE: Pin 3 and 5 are PWM capable
Car car = {
    {2, 3, false}, {4, 5, false}, {6, 7}, {8, 9}, {11, 12}, 255,
};

unsigned long timeout = millis();
// HACK: Libaries stop working outside of main.cpp
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 13, NEO_GRB + NEO_KHZ800);
SoftwareSerial bt(10, 0);
struct Signal {
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
Signal btQuery();

int curveDistance = 75;
int turnDistance = 15;
void blink(int speed, int form);

void setup() {
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
    strip.begin();
    Serial.println("Car started");
}

void loop() {
    if (mode == "bt") {
        Signal s = btQuery();
        if (s.id != 0) {
            switch (s.id) {
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
                car.speed = s.value;
                break;
            case 'Y': // Curve
                car.move(s.value);
                blink(car.speed, s.value);
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
                           curveDistance * 0.5, 0, curveDistance * 1.5) /
                       10.0;
            } else {
                form = -map(car.ultrasonicRight.distance(), 0,
                            curveDistance * 0.5, 0, curveDistance * 1.5) /
                       10.0;
            }
        }

        if (car.ultrasonicLeft.distance() < turnDistance ||
            car.ultrasonicMiddle.distance() < turnDistance ||
            car.ultrasonicMiddle.distance() < turnDistance) {
            car.speed = -abs(car.speed);
        } else if (car.ultrasonicMiddle.distance() > turnDistance + 10) {
            car.speed = abs(car.speed);
        }
        
        blink(car.speed, form);
        car.move(form);
    }
    if ((timeout + 50) < millis()) {
        strip.show();
        timeout = millis();
    }
}

Signal btQuery() {
    Signal result = {0, 0};

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

void blink(int speed, int form) {
    strip.clear();
    if (car.speed < 0) {
        strip.setPixelColor(5, strip.Color(255, 0, 0));
        strip.setPixelColor(6, strip.Color(255, 0, 0));
        strip.setPixelColor(7, strip.Color(255, 0, 0));
        strip.setPixelColor(8, strip.Color(255, 0, 0));
        strip.setPixelColor(9, strip.Color(255, 0, 0));
    } else if (form < 0) {
        strip.setPixelColor(3, strip.Color(0, 255, 0));
        strip.setPixelColor(4, strip.Color(0, 255, 0));
    } else if (form > 0) {
        strip.setPixelColor(0, strip.Color(0, 255, 0));
        strip.setPixelColor(1, strip.Color(0, 255, 0));
    }
}

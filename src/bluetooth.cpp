#include <bluetooth.h>

char btChar = ' ';
char btId = ' ';
char btIdTemp = ' ';
bool btIdExpected = true;
bool btNewReading = false;
String btValueString = "";
float btValue;

Value btQuery(SoftwareSerial bt) {
   Value result;

    btNewReading = false;
    if (bt.available()) {
        btChar = bt.read();
        Serial.write(btChar);
        if (btIdExpected) {
            btIdTemp = btChar;
            btIdExpected = false;
            btValueString = "";
        } else {
            if ((btChar != ' ') && (btChar != '\n'))
                btValueString += btChar;
            if (btChar == '\n') {
                btId = btIdTemp;
                btValue = btValueString.toFloat();
                btValueString = "";
                btIdExpected = true;
                btNewReading = true;
            }
        }
    }
 
   return result;
}
#include <bluetooth.h>

String btQuery(SoftwareSerial bt) {

}

// SoftwareSerial bt(10, 11);
// char btChar = ' ';
// char btId = ' ';
// char btIdTemp = ' ';
// bool btIdExpected = true;
// bool btNewReading = false;
// String btValueString = "";
// float btValue;
//
// void btQuery() {
//     btNewReading = false;
//     if (bt.available()) {
//         btChar = bt.read();
//         Serial.write(btChar);
//         if (btIdExpected) {
//             btIdTemp = btChar;
//             btIdExpected = false;
//             btValueString = "";
//         } else {
//             if ((btChar != ' ') && (btChar != '\n'))
//                 btValueString += btChar;
//             if (btChar == '\n') {
//                 btId = btIdTemp;
//                 btValue = btValueString.toFloat();
//                 btValueString = "";
//                 btIdExpected = true;
//                 btNewReading = true;
//             }
//         }
//     }
// }

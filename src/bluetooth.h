#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>

struct Value {
  char id;
  int value;
};

Value btQuery(SoftwareSerial bt);

#endif

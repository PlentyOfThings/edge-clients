#include "mec/mec.h"
#include <Arduino.h>
#include <stdlib.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Serial.println("Hello World!");

  mec::ipso::BaseObject obj;
  uint8_t buf[256];

  obj.buildUpData(buf, sizeof(buf));
}

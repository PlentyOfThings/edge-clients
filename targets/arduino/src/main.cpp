/*
    The Arduino Micro Edge Client.

    Currently supports:
    - ESP32
    - ESP8266
*/

#include "mec/mec.hpp"

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Platform not supported
#endif

#include <Arduino.h>
#include <MQTT.h>
#include <WiFiClientSecure.h>
#include <cstdlib>

// Arduino objects.
static WiFiClientSecure net;

// IPSO objects
static mec::ipso::objects::custom::Ping object_ping(0, 10);

// MEC Client
static mec::ipso::objects::Base *objects[] = { &object_ping };
static mec::Client client(objects, sizeof(objects) / sizeof(objects[0]));

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Serial.println(F("Hello World!"));

  uint8_t buf[256];

  mec::ipso::BuildResult res;
  if (client.handle(buf, sizeof(buf), res)) {
    Serial.println(F("Got result"));
    if (res.has_data) {
      Serial.println(F("Got data"));
    } else {
      Serial.println(F("No data"));
    }
  } else {
    Serial.println(F("No result"));
  }
}

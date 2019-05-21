/*
    The Arduino Micro Edge Client.

    Currently supports:
    - ESP32
    - ESP8266
*/

#include "mec/mec.hpp"

/*
  This file provides the following definitions:

static const char ssid[] = "";
static const char pass[] = "";
*/
#include "./secrets/config.hpp"

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
// static WiFiClientSecure net_client;
static WiFiClient net_client;
static MQTTClient mqtt_client;

// Config
static const char topic_down[] = "device/test/d/ipso/bson";
static const char topic_get[] = "device/test/g/ipso/bson";
static const char topic_up[] = "device/test/u/ipso/bson";

// IPSO objects
static mec::ipso::objects::custom::Ping object_ping(0, 10);

// MEC Client
static mec::ipso::objects::Base *objects[] = { &object_ping };
static mec::Client mec_client(objects, sizeof(objects) / sizeof(objects[0]));

void connect() {
  Serial.print("Checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nConnecting...");
  while (!mqtt_client.connect("test")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected!");

  mqtt_client.subscribe(topic_down);
  mqtt_client.subscribe(topic_get);
  // client.unsubscribe("/hello");
}

void mec_loop(uint8_t payload[], size_t len) {
  uint8_t buf[256];
  mec::ipso::BuildResult build_res;
  bool succ;

  if (payload) {
    succ = mec_client.handle(payload, len, buf, sizeof(buf), build_res);
  } else {
    succ = mec_client.handle(buf, sizeof(buf), build_res);
  }

  if (succ && build_res.has_data && build_res.res.status == bsons::Status::Ok) {
    mqtt_client.publish(topic_up, reinterpret_cast<char *>(buf),
                        build_res.res.len);
  }
}

void mec_loop() {
  mec_loop(nullptr, 0);
}

void on_msg(MQTTClient *client, char topic[], char bytes[], int len) {
  Serial.println("Got message from " + String(topic));
  mec_loop(reinterpret_cast<uint8_t *>(bytes), len);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  mqtt_client.begin("192.168.0.13", net_client);
  mqtt_client.onMessageAdvanced(on_msg);

  connect();
}

void loop() {
  mqtt_client.loop();
  delay(10);

  if (!mqtt_client.connected()) {
    connect();
  }

  mec_loop();
}

/*
    The Arduino Micro Edge Client.

    Currently supports:
    - ESP32 (untested)
    - ESP8266
*/

#include "./api.hpp"
#include "./controller.hpp"
#include "./debug.hpp"

#include "mec/mec.hpp"

#include <Arduino.h>
#include <MQTT.h>
#include <WiFiClientSecure.h>
#include <cstdlib>

// Arduino objects.
// static WiFiClientSecure net_client;
// static WiFiClient net_client;
static MQTTClient mqtt_client;

// Config
static MecController controller;

// IPSO objects
static mec::ipso::objects::custom::Ping object_ping(0, 10);

// MEC Client
static mec::ipso::objects::Base *objects[] = { &object_ping };
static mec::Client mec_client(objects, SIZE_OF(objects));

void connect() {
  MEC_DEBUG_PRINT("Checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    MEC_DEBUG_PRINT(".");
    delay(1000);
  }

  // Serial.print("\nConnecting...");
  // while (!mqtt_client.connect("test")) {
  //   Serial.print(".");
  //   delay(1000);
  // }

  MEC_DEBUG_PRINTLN("\nConnected!");

  // mqtt_client.subscribe(topic_down);
  // mqtt_client.subscribe(topic_get);
  // client.unsubscribe("/hello");
}

// void mec_loop(uint8_t payload[], size_t len) {
//   uint8_t buf[256];
//   mec::ipso::BuildResult build_res;
//   bool succ;

//   if (payload) {
//     succ = mec_client.handle(payload, len, buf, sizeof(buf), build_res);
//   } else {
//     succ = mec_client.handle(buf, sizeof(buf), build_res);
//   }

//   if (succ && build_res.has_data && build_res.res.status ==
//   bsons::Status::Ok) {
//     mqtt_client.publish(topic_up, reinterpret_cast<char *>(buf),
//                         build_res.res.len);
//   }
// }

// void mec_loop() {
//   mec_loop(nullptr, 0);
// }

// void on_msg(MQTTClient *client, char topic[], char bytes[], int len) {
//   MEC_DEBUG_PRINTLN_DYN("Got message from " + String(topic));
//   mec_loop(reinterpret_cast<uint8_t *>(bytes), len);
// }

void setup() {
  Serial.begin(9600);
  SPIFFS.begin();

#if MEC_DEBUG_MODE
  delay(5000);
#endif
  MEC_DEBUG_PRINTLN("[SETUP] Beginning init");

  if (!controller.init()) {
    MEC_DEBUG_PRINTLN("[SETUP] Failed to init");
    while (true) {
      delay(1000000);
    }
  } else {
    MEC_DEBUG_PRINTLN("[SETUP] Init successful");
  }

  // mqtt_client.begin("192.168.0.13", net_client);
  // mqtt_client.onMessageAdvanced(on_msg);

  connect();

  // net_client.setFingerprint(kFingerprintDSTRoot);
}

void loop() {
  MEC_DEBUG_PRINTLN("[MAIN] stub");
  // mqtt_client.loop();
  // delay(10);

  // if (!mqtt_client.connected()) {
  //   connect();
  // }

  // mec_loop();

  if (!WiFi.status() != WL_CONNECTED) {
    connect();
  }

  // if (test_https(net_client)) {
  //   Serial.println("Connection successful");
  // } else {
  //   Serial.println("Connection failed");
  // }
  delay(10000);
}

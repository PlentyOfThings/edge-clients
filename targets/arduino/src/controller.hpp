#ifndef MEC_TARGET_ARDUINO_DATA_H_
#define MEC_TARGET_ARDUINO_DATA_H_

#include "./api.hpp"
#include "./debug.hpp"
#include "mec/mec.hpp"
#include <FS.h>
#include <WiFiClientSecure.h>
#include <cstring>

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Platform not supported
#endif

static constexpr char kFileConfig[] = "/config.bson";
static constexpr char kFileReg[] = "/reg_data.bson";
static constexpr char kFileSign[] = "/sign_data.bson";

static constexpr char kFieldSsid[] = "ssid";
static constexpr char kFieldPass[] = "pass";

bool read_all_bytes_from(const char *path, uint8_t buf[], size_t len) {
  bool succ = false;
  File fp = SPIFFS.open(path, "r");

  if (fp) {
    size_t current = 0;
    int avl = 0;
    bool under = true;

    while ((avl = fp.available()) > 0) {
      if (current + avl > len) {
        MEC_DEBUG_PRINTLN("[FILE] File read went over buffer");
        under = false;
        break;
      }

      int read = fp.read(&buf[current], len - current);

      MEC_DEBUG_PRINTF("[FILE] Read %d bytes from file\n", read);
      current += read;
    }

    succ = under;
    fp.close();
  } else {
    MEC_DEBUG_PRINTF("[FILE] Failed to open file %s\n", path);
  }

  return succ;
}

bool write_all_bytes_to(const char *path, uint8_t buf[], size_t len) {
  bool succ = false;
  File fp = SPIFFS.open(path, "w");

  if (fp) {
    size_t written = fp.write(buf, len);
    MEC_DEBUG_PRINTF("[FILE] Wrote %zu bytes to file %s", written, path);
    succ = true;

    fp.close();
  } else {
    MEC_DEBUG_PRINTF("[FILE] Failed to open file %s\n", path);
  }

  return succ;
}

class MecController {
public:
  /** The SSID of the wifi point to connect to. */
  char ssid[32];

  /** The password of the wifi point to connect to. */
  char pass[32];

  /** The ID of the device according to PoT. */
  char id[64];

  /** The MQTT endpoint. */
  char endpoint[64];

  /** The MQTT port. */
  int64_t port;

  /** The received cert authority. */
  X509List ca;

  /** The received signed cert. */
  X509List crt;

  /** The received private key. */
  PrivateKey key;

  bool init() {
    if (!SPIFFS.exists(kFileConfig)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to find config file");
      return false;
    }

    if (!this->readConfig()) {
      return false;
    }

    WiFi.begin(this->ssid, this->pass);
    this->connect();

    if (SPIFFS.exists(kFileReg) && SPIFFS.exists(kFileSign)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Found device files, reading...");
      return this->loadDataFromFiles();
    } else {
      return this->performRegistration();
    }
  }

  void connect() {
    MEC_DEBUG_PRINTLN("[CONTROL] Waiting for wifi to connect");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    }

    // Serial.print("\nConnecting...");
    // while (!mqtt_client.connect("test")) {
    //   Serial.print(".");
    //   delay(1000);
    // }

    MEC_DEBUG_PRINTLN("[CONTROL] Wifi connected");

    // mqtt_client.subscribe(topic_down);
    // mqtt_client.subscribe(topic_get);
    // client.unsubscribe("/hello");
  }

private:
  bool readConfig() {
    bool succ = false;

    uint8_t buf[512];
    if (read_all_bytes_from(kFileConfig, buf, SIZE_OF(buf))) {
      bsond::Document doc(buf, SIZE_OF(buf));

      if (doc.valid()) {
        bool found_ssid = false;
        bool found_pass = false;

        for (auto const el : doc) {
          if (el.nameEquals(kFieldSsid)) {
            if (el.type() == bson::Element::String) {
              el.getStr(this->ssid, SIZE_OF(this->ssid));
              found_ssid = true;
            } else {
              MEC_DEBUG_PRINTLN("[CONTROL] SSID field invalid type");
              break;
            }
          } else if (el.nameEquals(kFieldPass)) {
            if (el.type() == bson::Element::String) {
              el.getStr(this->pass, SIZE_OF(this->pass));
              found_pass = true;
            } else {
              MEC_DEBUG_PRINTLN("[CONTROL] Password field invalid type");
              break;
            }
          }
        }

        succ = found_ssid && found_pass;

        if (succ) {
          MEC_DEBUG_PRINTF("[CONTROL] Found SSID of %s and password\n",
                           this->ssid);
        }
      } else {
        MEC_DEBUG_PRINTLN("[CONTROL] Config file invalid BSON");
      }
    } else {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to read config from file");
    }

    return succ;
  }

  bool loadDataFromFiles() {
    uint8_t reg_buf[512];
    uint8_t sign_buf[3072];

    if (!read_all_bytes_from(kFileReg, reg_buf, SIZE_OF(reg_buf))) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to read device file");
      return false;
    }

    if (!read_all_bytes_from(kFileSign, sign_buf, SIZE_OF(sign_buf))) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to read certs file");
      return false;
    }

    mec::http::RegRes reg_res;
    mec::http::SignRes sign_res;

    if (!mec::http::get_reg_res(reg_buf, SIZE_OF(reg_buf), reg_res)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to load reg res");
      return false;
    }

    if (!mec::http::get_sign_res(sign_buf, SIZE_OF(sign_buf), sign_res)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to load reg res");
      return false;
    }

    return this->readResults(reg_res, sign_res);
  }

  bool performRegistration() {
    uint8_t reg_buf[512];
    uint8_t sign_buf[3072];

    PotApi api;
    mec::http::RegRes reg_res;
    mec::http::SignRes sign_res;

    if (!api.performRegistration(reg_buf, SIZE_OF(reg_buf), reg_res, sign_buf,
                                 SIZE_OF(sign_buf), sign_res)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to register");
      return false;
    }

    return this->readResults(reg_res, sign_res);
  }

  bool readResults(mec::http::RegRes reg_res, mec::http::SignRes sign_res) {
    strncpy(this->id, reg_res.id, SIZE_OF(this->id));
    strncpy(this->endpoint, sign_res.endpoint, SIZE_OF(this->endpoint));
    this->port = sign_res.port;

    if (!this->ca.append(sign_res.ca, sign_res.ca_len)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to append CA");
      return false;
    }

    if (!this->crt.append(sign_res.crt, sign_res.crt_len)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to append CRT");
      return false;
    }

    if (!this->key.parse(sign_res.key, sign_res.key_len)) {
      MEC_DEBUG_PRINTLN("[CONTROL] Failed to append key");
      return false;
    }

    return true;
  }
};

#endif

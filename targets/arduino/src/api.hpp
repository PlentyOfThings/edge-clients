#ifndef MEC_TARGET_ARDUINO_API_H_
#define MEC_TARGET_ARDUINO_API_H_

#include "./debug.hpp"
#include "./verify.hpp"
#include "mec/mec.hpp"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

class PotApi {
public:
  PotApi() {
    this->net_client_.setFingerprint(kFingerprintDSTRoot);
  }

  bool performRegistration(uint8_t reg_buf[], size_t reg_buf_len,
                           mec::http::RegRes &reg_res, uint8_t sign_buf[],
                           size_t sign_buf_len, mec::http::SignRes &sign_res) {
    if (!this->apiRegister(reg_buf, reg_buf_len, reg_res)) {
      MEC_DEBUG_PRINTLN("[API] Failed to register");
      return false;
    }

    if (!this->apiSign(sign_buf, sign_buf_len, reg_res, sign_res)) {
      MEC_DEBUG_PRINTLN("[API] Failed to sign");
      return false;
    }

    return true;
  }

private:
  WiFiClientSecure net_client_;

  bool apiRegister(uint8_t buf[], size_t len, mec::http::RegRes &reg_res) {
    uint8_t payload[512];
    bool succ = false;

    auto build_res = mec::http::create_reg_req(payload, SIZE_OF(payload),
                                               [](bsons::Document &doc) {});
    if (build_res.status == bsons::Status::Ok) {
      MEC_DEBUG_PRINTLN("[API] Successfully built register payload");
      size_t payload_len = build_res.len;

      // This endpoint should return a 201 on success.
      size_t recv_len;
      if (this->httpPost(mec::http::kHost, mec::http::kPathRegister, payload,
                         payload_len, buf, len, recv_len)) {
        MEC_DEBUG_PRINTF("[API] Got response of %zu bytes from reg endpoint\n",
                         recv_len);
        succ = mec::http::get_reg_res(buf, len, reg_res);
      } else {
        MEC_DEBUG_PRINTLN("[API] Failed to POST");
      }
    } else {
      MEC_DEBUG_PRINTLN(
          "[API] Failed to build register payload (buffer overflow)");
    }

    return succ;
  }

  bool apiSign(uint8_t buf[], size_t len, mec::http::RegRes reg_res,
               mec::http::SignRes &sign_res) {
    uint8_t payload[512];
    bool succ = false;

    auto build_res =
        mec::http::create_sign_req(payload, SIZE_OF(payload), reg_res);
    if (build_res.status == bsons::Status::Ok) {
      MEC_DEBUG_PRINTLN("[API] Successfully built sign payload");
      size_t payload_len = build_res.len;

      char sign_path[128];
      snprintf(sign_path, SIZE_OF(sign_path), mec::http::kPathSign, reg_res.id);

      // This endpoint should return a 200 on success.
      size_t recv_len;
      if (this->httpPost(mec::http::kHost, sign_path, payload, payload_len, buf,
                         len, recv_len)) {
        MEC_DEBUG_PRINTF("[API] Got response of %zu bytes from sign endpoint\n",
                         recv_len);
        succ = mec::http::get_sign_res(buf, len, sign_res);
      } else {
        MEC_DEBUG_PRINTLN("[API] Failed to POST");
      }
    } else {
      MEC_DEBUG_PRINTLN("[API] Failed to build sign payload (buffer overflow)");
    }

    return succ;
  }

  bool httpPost(const char host[], const char uri[], uint8_t payload[],
                size_t payload_len, uint8_t resp[], size_t resp_len,
                size_t &resp_recv_len) {
    bool succ = false;
    HTTPClient http_client;

    MEC_DEBUG_PRINTF("[HTTP] Making request to %s%s\n", host, uri);

    if (http_client.begin(this->net_client_, host, 443, uri, true)) {
      MEC_DEBUG_PRINTLN("[HTTP] client begin");

      http_client.addHeader("Content-Type", mec::http::kBsonMimeType);
      http_client.addHeader("Accept", mec::http::kBsonMimeType);

      int code = http_client.POST(payload, payload_len);
      MEC_DEBUG_PRINTF("[HTTP] code: %d\n", code);
      if (code >= 200 && code < 300) {
        size_t current = 0;
        int avl;

        while ((avl = this->net_client_.available()) > 0) {
          MEC_DEBUG_PRINTF("[HTTP] available: %d\n", avl);

          int read = this->net_client_.read(&resp[current], resp_len - current);
          MEC_DEBUG_PRINTF("[HTTP] read: %d\n", read);

          current += read;
        }

        succ = true;
        resp_recv_len = current;
      } else {
        MEC_DEBUG_PRINTF("[HTTP] failed conn: %s\n",
                         HTTPClient::errorToString(code).c_str());
      }
    } else {
      MEC_DEBUG_PRINTLN("[HTTP] Failed to begin client");
    }

    return succ;
  }
};

#endif

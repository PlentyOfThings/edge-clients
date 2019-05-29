#ifndef MEC_HTTP_API_H_
#define MEC_HTTP_API_H_

#include "./bson_utils.hpp"
#include "./consts.hpp"
#include <cstdio>
#include <functional>

namespace mec {
namespace http {

struct RegRes {
  const char *id;
  const char *token;
};

struct SignRes {
  const uint8_t *crt;
  size_t crt_len;
  const uint8_t *ca;
  size_t ca_len;
  const uint8_t *key;
  size_t key_len;
  const char *endpoint;
  int64_t port;
};

bsons::Result
create_reg_req(uint8_t buf[], size_t len,
               std::function<void(bsons::Document &)> props_builder) {
  return bsons::Document::build(
      buf, len, [&props_builder](bsons::Document &doc) {
        doc.appendStr(fields::kFormat, kBsonFormat)
            .appendDoc(fields::kProperties,
                       [&props_builder](bsons::Document &props) {
                         props_builder(props);
                       });
      });
}

bool get_reg_res(const uint8_t buf[], size_t len, RegRes &reg_res) {
  bsond::Document res(buf, len);

  if (!res.valid()) {
    return false;
  }

  bool found_id = false;
  bool found_token = false;

  for (auto const el : res) {
    if (el.nameEquals(fields::kId)) {
      bsond::data_type::Str out;
      if (el.tryGetStr(out)) {
        reg_res.id = out.str;
        found_id = true;
      } else {
        return false;
      }
    } else if (el.nameEquals(fields::kToken)) {
      bsond::data_type::Str out;
      if (el.tryGetStr(out)) {
        reg_res.token = out.str;
        found_token = true;
      } else {
        return false;
      }
    }
  }

  return found_id && found_token;
}

bsons::Result create_sign_req(uint8_t buf[], size_t len, RegRes reg_res) {
  return bsons::Document::build(buf, len, [&reg_res](bsons::Document &doc) {
    doc.appendStr(fields::kToken, reg_res.token)
        .appendStr(fields::kFormat, kKeyFormat);
  });
}

bool get_sign_res(const uint8_t buf[], size_t len, SignRes &sign_res) {
  bsond::Document res(buf, len);

  if (!res.valid()) {
    return false;
  }

  bool success = false;
  bool found_crt = false;
  bool found_ca = false;
  bool found_key = false;
  bool found_endpoint = false;
  bool found_port = false;

  for (auto const el : res) {
    if (el.nameEquals(fields::kStatus)) {
      bsond::data_type::Str out;
      if (el.tryGetStr(out)) {
        success = out.str;
      } else {
        return false;
      }
    } else if (el.nameEquals(fields::kCrt)) {
      bsond::data_type::Bin out;
      if (el.tryGetBin(out)) {
        sign_res.crt = out.bin;
        sign_res.crt_len = out.len;
        found_crt = true;
      } else {
        return false;
      }
    } else if (el.nameEquals(fields::kCa)) {
      bsond::data_type::Bin out;
      if (el.tryGetBin(out)) {
        sign_res.ca = out.bin;
        sign_res.ca_len = out.len;
        found_ca = true;
      } else {
        return false;
      }
    } else if (el.nameEquals(fields::kKey)) {
      bsond::data_type::Bin out;
      if (el.tryGetBin(out)) {
        sign_res.key = out.bin;
        sign_res.key_len = out.len;
        found_key = true;
      } else {
        return false;
      }
    } else if (el.nameEquals(fields::kEndpoint)) {
      bsond::data_type::Str out;
      if (el.tryGetStr(out)) {
        sign_res.endpoint = out.str;
        found_endpoint = true;
      } else {
        return false;
      }
    } else if (el.nameEquals(fields::kPort)) {
      int64_t out;
      if (el.tryGetInt(out)) {
        sign_res.port = out;
        found_port = true;
      } else {
        return false;
      }
    }
  }

  return success && found_crt && found_ca && found_key && found_endpoint &&
         found_port;
}

} // namespace http
} // namespace mec

#endif

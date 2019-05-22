#ifndef MEC_HTTP_API_H_
#define MEC_HTTP_API_H_

#include "./bson_utils.hpp"
#include "./fields.hpp"
#include <functional>

namespace mec {

struct RegistrationResult {
  const char *id;
  const char *token;
};

class HttpApi {
public:
  bsons::Result createRegistrationRequest(
      uint8_t buf[], size_t len,
      std::function<void(bsons::Document &)> props_builder) {
    return bsons::Document::build(
        buf, len, [&props_builder](bsons::Document &doc) {
          doc.appendDoc(fields::kProperties,
                        [&props_builder](bsons::Document &props) {
                          props_builder(props);
                        });
        });
  }

  bool getRegistrationResult(uint8_t buf[], size_t len,
                             RegistrationResult &reg_res) {
    bsond::Document res(buf, len);

    if (!res.valid()) {
      return false;
    }

    bool found_id = false;
    bool found_token = false;

    for (auto const el : res) {
      if (el.nameEquals(fields::kId)) {
        reg_res.id = el.getStrRef();
      } else if (el.nameEquals(fields::kToken)) {
        reg_res.token = el.getStrRef();
      }
    }

    return found_id && found_token;
  }

  // bsons::Result createSigningRequest(uint8_t buf[], size_t len,
  //                                    RegistrationResult reg_res);
};

} // namespace mec

#endif

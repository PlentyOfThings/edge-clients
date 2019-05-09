#ifndef MEC_IPSO_OBJECTS_BASE_HPP_
#define MEC_IPSO_OBJECTS_BASE_HPP_

#include "../../utils.hpp"
#include "../build_result.hpp"
#include "../consts.hpp"
#include "../definitions.hpp"
#include "bson/bson.hpp"
#include <ctime>
#include <stdlib.h>

namespace bsons = pot::bson::serializer;

namespace mec {
namespace ipso {
namespace objects {

/**
 * The base class all IPSO objects derive from.
 */
class Base {
public:
  uint16_t getObjectId() {
    return object_id_;
  }

  uint32_t getObjectInstance() {
    return object_instance_;
  }

  char *getAppType() {
    return app_type_;
  }

  int getAppType(char *app_type, size_t len) {
    return copy_str_to(app_type_, app_type, len);
  }

  BuildResult buildUpData(uint8_t buf[], size_t len) {
    bool has_data = false;
    auto res = bsons::Document::build(
        buf, len, [this, &has_data](bsons::Document &doc) {
          doc.appendInt32(kPayloadId, object_id_)
              .appendInt32(kPayloadInstance, object_instance_)
              .appendInt32(kPayloadTimestamp, std::time(nullptr))
              .appendDoc(kPayloadResources,
                         [this, &has_data](bsons::Document &doc) {
                           has_data = buildResources(doc);
                         });
        });

    return { .res = res, .has_data = has_data };
  }

protected:
  Base(uint16_t object_id, uint32_t object_instance) :
      object_id_(object_id), object_instance_(object_instance) {}

  virtual bool buildResources(bsons::Document &doc) {
    doc.appendStr(Resource::sApplicationType, app_type_);

    // For now, we always return all data.
    // Once deserialization is implemented, we will use it
    // to decide what values to include.
    return true;
  }

protected:
  uint16_t object_id_;
  uint32_t object_instance_;

  char app_type_[kLenAppType];
};

} // namespace objects
} // namespace ipso
} // namespace mec

#endif

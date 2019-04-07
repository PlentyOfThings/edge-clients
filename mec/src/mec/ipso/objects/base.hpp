#ifndef MEC_IPSO_OBJECTS_BASE_HPP_
#define MEC_IPSO_OBJECTS_BASE_HPP_

#include "../../utils.hpp"
#include "../consts.hpp"
#include "../definitions.hpp"
#include "bson/bson.h"
#include <ctime>
#include <stdlib.h>

namespace bsons = pot::bson::serializer;

namespace mec {
namespace ipso {

/**
 * The base class all IPSO objects derive from.
 */
class BaseObject {
public:
  int getApplicationType(char *appType, size_t len) {
    return copy_str_to(appType_, appType, len);
  }

  bsons::Result buildUpData(uint8_t buf[], size_t len) {
    return bsons::Document::build(buf, len, [this](bsons::Document &doc) {
      doc.appendInt32(kPayloadId, object_)
          .appendInt32(kPayloadInstance, objectInstance_)
          .appendInt32(kPayloadTimestamp, std::time(nullptr))
          .appendDoc(kPayloadResources,
                     [this](bsons::Document &doc) { buildResources(doc); });
    });
  }

protected:
  virtual void buildResources(bsons::Document &doc) {
    doc.appendStr(Resource::sApplicationType, appType_);
  }

private:
  uint16_t object_;
  uint16_t objectInstance_;

  char appType_[kLenAppType];
};

} // namespace ipso
} // namespace mec

#endif

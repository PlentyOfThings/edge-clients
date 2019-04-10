#ifndef MEC_IPSO_BUILD_RESULT_H_
#define MEC_IPSO_BUILD_RESULT_H_

#include "bson/bson.h"

namespace mec {
namespace ipso {

struct BuildResult {
  pot::bson::serializer::Result res;
  bool has_data;
};

} // namespace ipso
} // namespace mec

#endif

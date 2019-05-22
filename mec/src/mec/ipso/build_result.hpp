#ifndef MEC_IPSO_BUILD_RESULT_H_
#define MEC_IPSO_BUILD_RESULT_H_

#include "../bson_utils.hpp"

namespace mec {
namespace ipso {

struct BuildResult {
  bsons::Result res;
  bool has_data;
};

} // namespace ipso
} // namespace mec

#endif

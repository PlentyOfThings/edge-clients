#ifndef MEC_IPSO_CONSTS_H_
#define MEC_IPSO_CONSTS_H_

#include "cstdlib"

namespace mec {
namespace ipso {

static constexpr size_t kLenAppType = 50;
static constexpr char kPayloadId[] = "id";
static constexpr char kPayloadInstance[] = "instance";
static constexpr char kPayloadTimestamp[] = "timestamp";
static constexpr char kPayloadResources[] = "resources";
static constexpr int64_t kDefaultReportInterval = 30; // In seconds.

} // namespace ipso
} // namespace mec

#endif

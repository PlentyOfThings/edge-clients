#ifndef MEC_CONSTS_H_
#define MEC_CONSTS_H_

#include <cstdint>
#include <cstdlib>

namespace mec {

namespace fields {

static constexpr char kId[] = "id";
static constexpr char kToken[] = "token";
static constexpr char kFormat[] = "format";
static constexpr char kStatus[] = "status";
static constexpr char kCrt[] = "crt";
static constexpr char kCa[] = "ca";
static constexpr char kKey[] = "key";
static constexpr char kEndpoint[] = "endpoint";
static constexpr char kPort[] = "port";
static constexpr char kProperties[] = "properties";
static constexpr char kInstance[] = "instance";
static constexpr char kTimestamp[] = "timestamp";
static constexpr char kResources[] = "resources";

} // namespace fields

namespace ipso {

static constexpr size_t kLenAppType = 50;
static constexpr int64_t kDefaultReportInterval = 30; // In seconds.

} // namespace ipso

namespace http {

static constexpr char kHost[] = "plenty.home.t3s.uk";
static constexpr char kPathRegister[] = "/api/v1/registration/register";
static constexpr char kPathSign[] = "/api/v1/registration/%s/sign";
static constexpr char kBsonMimeType[] = "application/bson";

static constexpr char kBsonFormat[] = "BSON";
static constexpr char kKeyFormat[] = "DER";
static constexpr char kSuccess[] = "SUCCESS";

static constexpr char kStatusOk[] = "200";
static constexpr char kStatusCreated[] = "201";

} // namespace http

namespace topics {

static constexpr char kUp[] = "device/%s/u/ipso";
static constexpr char kDown[] = "device/%s/d/ipso";
static constexpr char kGet[] = "device/%s/g/ipso";
static constexpr char kEvent[] = "device/%s/e/ipso";

} // namespace topics

} // namespace mec

#endif

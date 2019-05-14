#ifndef MEC_IPSO_OBJECTS_CUSTOM_PING_H_
#define MEC_IPSO_OBJECTS_CUSTOM_PING_H_

#include "../../definitions.hpp"
#include "../report_interval.hpp"
#include <cstdlib>
#include <ctime>

namespace mec {
namespace ipso {
namespace objects {
namespace custom {

class Ping : public ReportInterval {
public:
  Ping(const uint32_t object_instance, const int64_t report_interval) :
      ReportInterval(Object::iPing, object_instance, report_interval) {}

  Ping(const uint32_t object_instance) :
      ReportInterval(Object::iPing, object_instance) {}

  int32_t getCounter() {
    return this->counter_;
  }

protected:
  bool buildResources(bsons::Document &resources,
                      const bsond::Array *get_ids) override {
    bool has_data = false;

    if (this->ReportInterval::shouldReport() ||
        Base::hasResourceId(get_ids, Resource::iCounter)) {
      resources.appendInt32(Resource::sCounter, this->counter_++);
      has_data = true;
    }

    return this->ReportInterval::buildResources(resources, get_ids) || has_data;
  }

private:
  int32_t counter_ = 0;
};

} // namespace custom
} // namespace objects
} // namespace ipso
} // namespace mec

#endif

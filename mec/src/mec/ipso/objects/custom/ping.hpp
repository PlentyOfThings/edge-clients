#ifndef MEC_IPSO_OBJECTS_CUSTOM_PING_H_
#define MEC_IPSO_OBJECTS_CUSTOM_PING_H_

#include "../../definitions.hpp"
#include "../base.hpp"
#include <ctime>
#include <stdlib.h>

namespace mec {
namespace ipso {
namespace objects {
namespace custom {

class Ping : public Base {
public:
  Ping(uint32_t object_instance, time_t delay_time) :
      Base(Object::iPing, object_instance), delay_time_(delay_time) {}

  int32_t getCounter() {
    return counter_;
  }

protected:
  bool buildResources(bsons::Document &doc) override {
    bool has_data = false;
    time_t ctime = std::time(nullptr);

    if (ctime - last_count_time_ >= delay_time_) {
      last_count_time_ = ctime;
      doc.appendInt32(Resource::sCounter, counter_++);
      has_data = true;
    }

    return Base::buildResources(doc) || has_data;
  }

private:
  int32_t counter_ = 0;
  time_t delay_time_;
  time_t last_count_time_ = 0;
};

} // namespace custom
} // namespace objects
} // namespace ipso
} // namespace mec

#endif

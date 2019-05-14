#ifndef MEC_IPSO_OBJECTS_REPORT_INTERVAL_H_
#define MEC_IPSO_OBJECTS_REPORT_INTERVAL_H_

#include "../definitions.hpp"
#include "./base.hpp"
#include <cstdlib>
#include <ctime>

namespace mec {
namespace ipso {
namespace objects {

class ReportInterval : public Base {
public:
  int64_t getReportIterval() const {
    return this->report_interval_;
  }

protected:
  ReportInterval(const uint16_t object_id, const uint32_t object_instance,
                 const int64_t report_interval) :
      Base(object_id, object_instance),
      report_interval_(report_interval) {}

  ReportInterval(const uint16_t object_id, const uint32_t object_instance) :
      Base(object_id, object_instance),
      report_interval_(kDefaultReportInterval) {}

  bool shouldReport() {
    bool should_report = false;
    time_t ctime = std::time(nullptr);

    if (ctime - this->last_report_time_ >= this->report_interval_) {
      this->last_report_time_ = ctime;
      should_report = true;
    }

    return should_report;
  }

  bool appendGetOnlyResource(bsons::Document &doc, const int64_t resource_id) {
    switch (resource_id) {
      case Resource::iReportInterval:
        doc.appendInt64(Resource::sReportInterval, this->report_interval_);
        return true;
      default:
        return Base::appendGetOnlyResource(doc, resource_id);
    }
  }

private:
  int64_t report_interval_;
  time_t last_report_time_ = 0;
};

} // namespace objects
} // namespace ipso
} // namespace mec

#endif

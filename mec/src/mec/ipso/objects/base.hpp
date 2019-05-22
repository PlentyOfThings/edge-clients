#ifndef MEC_IPSO_OBJECTS_BASE_HPP_
#define MEC_IPSO_OBJECTS_BASE_HPP_

#include "../../bson_utils.hpp"
#include "../../fields.hpp"
#include "../../utils.hpp"
#include "../build_result.hpp"
#include "../consts.hpp"
#include "../definitions.hpp"
#include <cstdlib>
#include <ctime>

namespace mec {
namespace ipso {
namespace objects {

/**
 * The base class all IPSO objects derive from.
 */
class Base {
public:
  static inline bool hasResourceId(const bsond::Array *get_ids,
                                   const uint16_t resource_id) {
    return get_ids && get_ids->containsInt(resource_id);
  }

  uint16_t getObjectId() {
    return this->object_id_;
  }

  uint32_t getObjectInstance() {
    return this->object_instance_;
  }

  char *getAppType() {
    return this->app_type_;
  }

  int getAppType(char *app_type, const size_t len) {
    return copy_str_to(this->app_type_, app_type, len);
  }

  BuildResult buildUpData(uint8_t buf[], const size_t len) {
    return this->buildUpData(buf, len, nullptr);
  }

  BuildResult buildUpData(uint8_t buf[], const size_t len,
                          const bsond::Array *get_ids) {
    bool has_data = false;
    auto res = bsons::Document::build(
        buf, len, [this, &has_data, get_ids](bsons::Document &up) {
          up.appendInt32(fields::kId, object_id_)
              .appendInt32(fields::kInstance, object_instance_)
              .appendInt32(fields::kTimestamp, std::time(nullptr))
              .appendDoc(fields::kResources, [this, &has_data, get_ids](
                                                 bsons::Document &resources) {
                has_data = this->buildResources(resources, get_ids);
              });
        });

    return { .res = res, .has_data = has_data };
  }

protected:
  Base(const uint16_t object_id, const uint32_t object_instance) :
      object_id_(object_id), object_instance_(object_instance) {}

  /**
   * Builds the resources document that will be sent to the MQTT topic.
   * If it returns false, then it means that no resources needed
   * to send up data, and so the entire document will be discarded.
   *
   * This function will be called on a regular interval, but of
   * an undefined time, meaning overriding implementations should
   * not rely on it, and keep track of timing themselves.
   *
   * All overriding implementations should ALWAYS call the super
   * method, otherwise it will not function correctly.
   */
  virtual bool buildResources(bsons::Document &resources,
                              const bsond::Array *get_ids) {
    if (get_ids) {
      bool appended_resources = false;

      for (auto const &el : *get_ids) {
        auto type = el.type();

        // IDs can only be integers, anything else is ignored.
        if (type == pot::bson::Element::Int32 ||
            type == pot::bson::Element::Int64) {
          appended_resources |=
              this->appendGetOnlyResource(resources, el.getInt());
        }
      }

      return appended_resources;
    } else {
      // We have no resources to get, by default we send nothing up.
      return false;
    }
  }

  /**
   * Appends the resource of the given ID to the up document.
   * Returns whether the resource by that ID was found and appended.
   *
   * Overriding implementations only need to call the super method
   * if none of their own resources match, otherwise they can return
   * directly.
   */
  virtual bool appendGetOnlyResource(bsons::Document &resources,
                                     const int64_t resource_id) {
    switch (resource_id) {
      case Resource::iApplicationType:
        resources.appendStr(Resource::sApplicationType, this->app_type_);
        return true;
      default:
        return false;
    }
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

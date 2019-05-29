#ifndef MEC_CLIENT_H_
#define MEC_CLIENT_H_

#include "./consts.hpp"
#include "./ipso/objects/base.hpp"
#include <cstdlib>

namespace mec {

class Client {
public:
  Client(ipso::objects::Base *objs[], size_t objs_len) :
      objects_(objs), objects_length_(objs_len) {}

  bool handle(uint8_t up_buf[], size_t up_len, ipso::BuildResult &result) {
    return this->handle(nullptr, 0, up_buf, up_len, result);
  }

  bool handle(uint8_t down_buf[], size_t down_len, uint8_t up_buf[],
              size_t up_len, ipso::BuildResult &result) {
    size_t current_object;
    bsond::Array resources;
    bool got_resources = false;

    if (down_buf) {
      if (!this->findObject(down_buf, down_len, current_object, resources)) {
        return false;
      }
      got_resources = true;
    } else {
      current_object = this->next_object_++;
      this->next_object_ %= this->objects_length_;
    }

    if (got_resources) {
      result = this->objects_[current_object]->buildUpData(up_buf, up_len,
                                                           &resources);
    } else {
      result = this->objects_[current_object]->buildUpData(up_buf, up_len);
    }
    return true;
  }

private:
  ipso::objects::Base **objects_;
  const size_t objects_length_;
  size_t next_object_ = 0;

  bool findObject(uint8_t down_buf[], size_t down_len, size_t &index,
                  bsond::Array &resources) {
    bsond::Document down(down_buf, down_len);

    if (!down.valid()) {
      return false;
    }

    int64_t objectId = -1;
    int64_t objectInstance = -1;
    bool found_resources = false;
    for (auto const el : down) {
      if (el.nameEquals(fields::kId)) {
        if (!el.tryGetInt(objectId)) {
          return false;
        }
      } else if (el.nameEquals(fields::kInstance)) {
        if (!el.tryGetInt(objectInstance)) {
          return false;
        }
      } else if (el.nameEquals(fields::kResources)) {
        bsond::data_type::Arr out;
        if (el.tryGetArr(out)) {
          resources = out.arr;
          found_resources = true;
        } else {
          return false;
        }
      }
    }

    // If none of the fields were set correctly, bail out here.
    if (objectId < 0 || objectInstance < 0 || !found_resources) {
      return false;
    }

    for (size_t i = 0; i < this->objects_length_; i++) {
      if (this->objects_[i]->getObjectId() == objectId &&
          this->objects_[i]->getObjectInstance() == objectInstance) {
        index = i;
        return true;
      }
    }

    return false;
  }
};

} // namespace mec

#endif

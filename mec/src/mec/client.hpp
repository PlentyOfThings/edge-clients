#ifndef MEC_CLIENT_H_
#define MEC_CLIENT_H_

#include "./ipso/consts.hpp"
#include "./ipso/objects/base.hpp"
#include <cstdlib>
#include <memory>

namespace mec {

class Client {
public:
  Client(std::shared_ptr<mec::ipso::objects::Base> objs[], size_t objs_len) :
      objects_(objs), objects_length_(objs_len) {}

  std::shared_ptr<ipso::BuildResult> handle(uint8_t up_buf[], size_t up_len) {
    return this->handle(nullptr, 0, up_buf, up_len);
  }

  std::shared_ptr<ipso::BuildResult> handle(uint8_t down_buf[], size_t down_len,
                                            uint8_t up_buf[], size_t up_len) {
    size_t current_object;
    std::shared_ptr<bsond::Array> resources;

    if (down_buf) {
      if (!this->findObject(down_buf, down_len, current_object, resources)) {
        return nullptr;
      }
    } else {
      current_object = this->next_object_++;
      this->next_object_ %= this->objects_length_;
    }

    return std::make_shared<ipso::BuildResult>(
        this->objects_[current_object]->buildUpData(up_buf, up_len, resources));
  }

private:
  std::shared_ptr<mec::ipso::objects::Base> *objects_;
  const size_t objects_length_;
  size_t next_object_ = 0;

  bool findObject(uint8_t down_buf[], size_t down_len, size_t &index,
                  std::shared_ptr<bsond::Array> &resources) {
    bsond::Document down(down_buf, down_len);

    int64_t objectId = -1;
    int64_t objectInstance = -1;
    for (auto const el : down) {
      if (el.nameEquals(ipso::kPayloadId)) {
        if (el.isInt()) {
          objectId = el.getInt();
        }
      } else if (el.nameEquals(ipso::kPayloadInstance)) {
        if (el.isInt()) {
          objectInstance = el.getInt();
        }
      } else if (el.nameEquals(ipso::kPayloadResources)) {
        if (el.type() == pot::bson::Element::Array) {
          resources = std::make_shared<bsond::Array>(el.getArr());
        }
      }
    }

    // If none of the fields were set correctly, bail out here.
    if (objectId < 0 || objectInstance < 0 || !resources) {
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

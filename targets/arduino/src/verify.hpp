#ifndef MEC_TARGET_ARDUINO_VERIFY_H_
#define MEC_TARGET_ARDUINO_VERIFY_H_

#include <cstdint>

/**
 * This is the fingerprint of the DST Root CA X3
 * root cert. It expires Thursday, 30 September 2021 at 14:01:15 UTC,
 * so we should probably update it before then...
 */
static constexpr uint8_t kFingerprintDSTRoot[20] = {
  0xDA, 0xC9, 0x02, 0x4F, 0x54, 0xD8, 0xF6, 0xDF, 0x94, 0x93,
  0x5F, 0xB1, 0x73, 0x26, 0x38, 0xCA, 0x6A, 0xD7, 0x7C, 0x13
};

#endif

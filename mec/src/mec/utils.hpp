#ifndef MEC_UTILS_H_
#define MEC_UTILS_H_

#include "stdlib.h"

inline size_t copy_str_to(const char src[], char dest[], size_t len) {
  if (len < 1) {
    return 0;
  }

  size_t i = 0;

  // Copy string until buffer length - 1, so we always
  // have room for the null terminator.
  for (; i < len - 1; i++) {
    if (src[i] == '\0') {
      break;
    }

    dest[i] = src[i];
  }

  // Store the length we actually copied (excluding null terminator).
  size_t copied = i;

  // Fill the remaining destination buffer with null bytes.
  for (; i < len; i++) {
    dest[i] = '\0';
  }

  // Return the length that was copied including null terminator.
  return copied + 1;
}

#endif

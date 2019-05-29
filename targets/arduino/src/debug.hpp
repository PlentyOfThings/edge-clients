#ifndef MEC_TARGET_ARDUINO_DEBUG_H_
#define MEC_TARGET_ARDUINO_DEBUG_H_

#ifdef MEC_DEBUG_MODE

#define MEC_DEBUG_PRINT(str, ...) Serial.print(F(str))
#define MEC_DEBUG_PRINT_DYN(str, ...) Serial.print(str)
#define MEC_DEBUG_PRINTLN(str, ...) Serial.println(F(str))
#define MEC_DEBUG_PRINTLN_DYN(str, ...) Serial.println(str)
#define MEC_DEBUG_PRINTF(fmt, ...) Serial.printf(fmt, __VA_ARGS__)

#else

#define MEC_DEBUG_PRINT(...)
#define MEC_DEBUG_PRINT_DYN(...)
#define MEC_DEBUG_PRINTLN(...)
#define MEC_DEBUG_PRINTLN_DYN(...)
#define MEC_DEBUG_PRINTF(...)

#endif

#endif

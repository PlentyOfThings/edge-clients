#ifndef MEC_IPSO_OBJECTS_H
#define MEC_IPSO_OBJECTS_H

/*
  Common resources.

  Only single instances of each of these are allowed.
  These all apply to each of the common objects.
*/

#define IPSO_RESOURCE_SENSOR_VALUE 5700                  // R, Mandatory, Float
#define IPSO_RESOURCE_UNITS 5701                         // R, String
#define IPSO_RESOURCE_MIN_MEASURED_VALUE 5601            // R, Float
#define IPSO_RESOURCE_MAX_MEASURED_VALUE 5602            // R, Float
#define IPSO_RESOURCE_MIN_RANGE_VALUE 5603               // R, Float
#define IPSO_RESOURCE_MAX_RANGE_VALUE 5604               // R, Float
#define IPSO_RESOURCE_RESET_MIN_MAX_MEASURED_VALUES 5605 // E
#define IPSO_RESOURCE_CALIBRATION_OFFSET 5535            // R, W, Float
#define IPSO_RESOURCE_APPLICATION_TYPE 5750              // R, W, String

/*
  Common objects

  Multiple instances of each of these are allowed.
  Each one has all of the common resources attached.
*/

#define IPSO_OBJECT_VOLTAGE 3316
#define IPSO_OBJECT_CURRENT 3317
#define IPSO_OBJECT_FREQUENCY 3318
#define IPSO_OBJECT_DEPTH 3319
#define IPSO_OBJECT_PERCENTAGE 3320
#define IPSO_OBJECT_ALTITUDE 3321
#define IPSO_OBJECT_LOAD 3322
#define IPSO_OBJECT_PRESSURE 3323
#define IPSO_OBJECT_LOUDNESS 3324
#define IPSO_OBJECT_CONCENTRATION 3325
#define IPSO_OBJECT_ACIDITY 3326
#define IPSO_OBJECT_CONDUCTIVITY 3327
#define IPSO_OBJECT_POWER 3328
#define IPSO_OBJECT_POWER_FACTOR 3329
#define IPSO_OBJECT_RATE 3346
#define IPSO_OBJECT_DISTANCE 3330

/*
  Special resources.

  Same restriction as common resources.
  These apply to some of the special objects.
*/

#define IPSO_RESOURCE_RESET_CUMULATIVE_ENERGY 5822 // E
#define IPSO_RESOURCE_COMPASS_DIRECTION 5705       // R, Mandatory, Float (units: deg, range: 0-360 incl)
#define IPSO_RESOURCE_CURRENT_TIME 5506            // R, W, Mandatory, Time (unix)
#define IPSO_RESOURCE_FRACTIONAL_TIME 5507         // R, W, Float (range: 0-1 incl)
#define IPSO_RESOURCE_X_VALUE 5702                 // R, Mandatory, Float
#define IPSO_RESOURCE_Y_VALUE 5703                 // R, Float
#define IPSO_RESOURCE_Z_VALUE 5704                 // R, Float
#define IPSO_RESOURCE_SENSOR_UNITS 5701            // R, String
#define IPSO_RESOURCE_MIN_X_VALUE 5508             // R, Float
#define IPSO_RESOURCE_MAX_X_VALUE 5509             // R, Float
#define IPSO_RESOURCE_MIN_Y_VALUE 5510             // R, Float
#define IPSO_RESOURCE_MAX_Y_VALUE 5511             // R, Float
#define IPSO_RESOURCE_MIN_Z_VALUE 5512             // R, Float
#define IPSO_RESOURCE_MAX_Z_VALUE 5513             // R, Float
#define IPSO_RESOURCE_COLOR 5706                   // R, W, Mandatory, String
#define IPSO_RESOURCE_LATITUDE 5513                // R, Mandatory, String
#define IPSO_RESOURCE_LONGITUDE 5514               // R, Mandatory, String
#define IPSO_RESOURCE_ALTITUDE 5515                // R, String
#define IPSO_RESOURCE_UNCERTAINTY 5516             // R, String
#define IPSO_RESOURCE_COMPASS_DIRECTION 5705       // R, Float
#define IPSO_RESOURCE_VELOCITY 5517                // R, Opaque
#define IPSO_RESOURCE_TIMESTAMP 5518               // R, Time (unix)

/*
  Special objects.

  Same freedom as the common objects.
  Resources for each are specified in comments.
*/

/**
 * Resources:
 * - IPSO_RESOURCE_SENSOR_VALUE (unit: Wh)
 * - IPSO_RESOURCE_UNITS
 * - IPSO_RESOURCE_RESET_CUMULATIVE_ENERGY
 * - IPSO_RESOURCE_APPLICATION_TYPE
 */
#define IPSO_OBJECT_ENERGY 3331

/**
 * Resources:
 * - IPSO_RESOURCE_COMPASS_DIRECTION
 * - IPSO_RESOURCE_MIN_MEASURED_VALUE
 * - IPSO_RESOURCE_MAX_MEASURED_VALUE
 * - IPSO_RESOURCE_RESET_MIN_MAX_MEASURED_VALUES
 * - IPSO_RESOURCE_APPLICATION_TYPE
 */
#define IPSO_OBJECT_DIRECTION 3332

/**
 * Resources:
 * - IPSO_RESOURCE_CURRENT_TIME (unit: s, unix time (seconds since epoc))
 * - IPSO_RESOURCE_FRACTIONAL_TIME
 * - IPSO_RESOURCE_APPLICATION_TYPE
 */
#define IPSO_OBJECT_TIME 3333

/**
 * Resources:
 * - IPSO_RESOURCE_X_VALUE
 * - IPSO_RESOURCE_Y_VALUE
 * - IPSO_RESOURCE_Z_VALUE
 * - IPSO_RESOURCE_SENSOR_UNITS
 * - IPSO_RESOURCE_MIN_X_VALUE
 * - IPSO_RESOURCE_MAX_X_VALUE
 * - IPSO_RESOURCE_MIN_Y_VALUE
 * - IPSO_RESOURCE_MAX_Y_VALUE
 * - IPSO_RESOURCE_MIN_Z_VALUE
 * - IPSO_RESOURCE_MAX_Z_VALUE
 * - IPSO_RESOURCE_RESET_MIN_MAX_MEASURED_VALUES
 * - IPSO_RESOURCE_MIN_RANGE_VALUE
 * - IPSO_RESOURCE_MAX_RANGE_VALUE
 * - IPSO_RESOURCE_APPLICATION_TYPE
 */
#define IPSO_OBJECT_GYROMETER 3334

/**
 * Resources:
 * - IPSO_RESOURCE_COLOR
 * - IPSO_RESOURCE_UNITS
 * - IPSO_RESOURCE_APPLICATION_TYPE
 */
#define IPSO_OBJECT_COLOR 3335

/**
 * Resources:
 * - IPSO_RESOURCE_LATITUDE
 * - IPSO_RESOURCE_LONGITUDE
 * - IPSO_RESOURCE_ALTITUDE
 * - IPSO_RESOURCE_UNCERTAINTY
 * - IPSO_RESOURCE_COMPASS_DIRECTION
 * - IPSO_RESOURCE_VELOCITY
 * - IPSO_RESOURCE_TIMESTAMP
 * - IPSO_RESOURCE_APPLICATION_TYPE
 */
#define IPSO_OBJECT_GPS_LOCATION 3336

#endif

#ifndef MEC_IPSO_H_
#define MEC_IPSO_H_

#include <stdint.h>

namespace ipso
{
enum struct kResource : uint16_t
{
  /*
    Common resources.

    Only single instances of each of these are allowed.
    These all apply to each of the common objects.
  */

  SensorValue = 5700,               // R, Mandatory, Float
  Units = 5701,                     // R, String
  MinMeasuredValue = 5601,          // R, Float
  MaxMeasuredValue = 5602,          // R, Float
  MinRangeValue = 5603,             // R, Float
  MaxRangeValue = 5604,             // R, Float
  ResetMinMaxMeasuredValues = 5605, // E
  CalibrationOffset = 5535,         // R, W, Float
  ApplicationType = 5750,           // R, W, String

  /*
    Special resources.

    Same restriction as common resources.
    These apply to some of the special objects.
  */

  ResetCumulativeEnergy = 5822, // E
  CompassDirection = 5705,      // R, Mandatory, Float (units: deg, range: 0-360 incl)
  CurrentTime = 5506,           // R, W, Mandatory, Time (unix)
  FractionalTime = 5507,        // R, W, Float (range: 0-1 incl)
  XValue = 5702,                // R, Mandatory, Float
  YValue = 5703,                // R, Float
  ZValue = 5704,                // R, Float
  SensorUnits = 5701,           // R, String
  MinXValue = 5508,             // R, Float
  MaxXValue = 5509,             // R, Float
  MinYValue = 5510,             // R, Float
  MaxYValue = 5511,             // R, Float
  MinZValue = 5512,             // R, Float
  MaxZValue = 5513,             // R, Float
  Color = 5706,                 // R, W, Mandatory, String
  Latitude = 5513,              // R, Mandatory, String
  Longitude = 5514,             // R, Mandatory, String
  Altitude = 5515,              // R, String
  Uncertainty = 5516,           // R, String
  Velocity = 5517,              // R, Opaque
  Timestamp = 5518,             // R, Time (unix)
};

enum struct kObject : uint16_t
{
  /*
    Common objects

    Multiple instances of each of these are allowed.
    Each one has all of the common resources attached.
  */

  Voltage = 3316,
  Current = 3317,
  Frequency = 3318,
  Depth = 3319,
  Percentage = 3320,
  Altitude = 3321,
  Load = 3322,
  Pressure = 3323,
  Loudness = 3324,
  Concentration = 3325,
  Acidity = 3326,
  Conductivity = 3327,
  Power = 3328,
  PowerFactor = 3329,
  Rate = 3346,
  Distance = 3330,

  /*
    Special objects.

    Same freedom as the common objects.
    Resources for each are specified in comments.
  */

  /**
   * Resources:
   * - SensorValue (unit: Wh)
   * - Units
   * - ResetCumulativeEnergy
   * - ApplicationType
   */
  Energy = 3331,

  /**
   * Resources:
   * - CompassDirection
   * - MinMeasuredValue
   * - MaxMeasuredValue
   * - ResetMinMaxMeasuredValues
   * - ApplicationType
   */
  Direction = 3332,

  /**
   * Resources:
   * - CurrentTime (unit: s, unix time (seconds since epoc))
   * - FractionalTime
   * - ApplicationType
   */
  Time = 3333,

  /**
   * Resources:
   * - XValue
   * - YValue
   * - ZValue
   * - SensorUnits
   * - MinXValue
   * - MaxXValue
   * - MinYValue
   * - MaxYValue
   * - MinZValue
   * - MaxZValue
   * - ResetMinMaxMeasuredValues
   * - MinRangeValue
   * - MaxRangeValue
   * - ApplicationType
   */
  Gyrometer = 3334,

  /**
   * Resources:
   * - Color
   * - Units
   * - ApplicationType
   */
  Color = 3335,

  /**
   * Resources:
   * - Latitude
   * - Longitude
   * - Altitude
   * - Uncertainty
   * - CompassDirection
   * - Velocity
   * - Timestamp
   * - ApplicationType
   */
  GpsLocation = 3336,
};
} // namespace ipso

#endif

#ifndef MEC_IPSO_DEFINITIONS_HPP_
#define MEC_IPSO_DEFINITIONS_HPP_

/*
  Derived from
  http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html

  Shared resources listing can be found here:
  http://upfiles.heclouds.com/forum-app/2018/07/15/673e6333f545809ddfae2f98ee4a4a73.pdf
*/

#include <stdint.h>

namespace mec {
namespace ipso {

#define MEC_IPSO_CONST(name, id)          \
  static constexpr uint16_t i##name = id; \
  static constexpr char s##name[] = #id;

namespace Resource {

MEC_IPSO_CONST(DigitalInputState, 5500);
MEC_IPSO_CONST(DigitalInputCounter, 5501);
MEC_IPSO_CONST(DigitalInputPolarity, 5502);
MEC_IPSO_CONST(DigitalInputDebounce, 5503);
MEC_IPSO_CONST(DigitalInputEdgeSelection, 5504);
MEC_IPSO_CONST(DigitalInputCounterReset, 5505);
MEC_IPSO_CONST(CurrentTime, 5506);
MEC_IPSO_CONST(FractionalTime, 5507);
MEC_IPSO_CONST(MinXValue, 5508);
MEC_IPSO_CONST(MaxXValue, 5509);
MEC_IPSO_CONST(MinYValue, 5510);
MEC_IPSO_CONST(MaxYValue, 5511);
MEC_IPSO_CONST(MinZValue, 5512);
MEC_IPSO_CONST(MaxZValue, 5513);
MEC_IPSO_CONST(Latitude, 5514);
MEC_IPSO_CONST(Longitude, 5515);
MEC_IPSO_CONST(Uncertainty, 5516);
MEC_IPSO_CONST(Velocity, 5517);
MEC_IPSO_CONST(Timestamp, 5518);
MEC_IPSO_CONST(MinLimit, 5519);
MEC_IPSO_CONST(MaxLimit, 5520);
MEC_IPSO_CONST(DelayDuration, 5521);
MEC_IPSO_CONST(Clip, 5522);
MEC_IPSO_CONST(Trigger, 5523);
MEC_IPSO_CONST(Duration, 5524);
MEC_IPSO_CONST(MinimumOffTime, 5525);
MEC_IPSO_CONST(TimerMode, 5526);
MEC_IPSO_CONST(Text, 5527);
MEC_IPSO_CONST(XCoordinate, 5528);
MEC_IPSO_CONST(YCoordinate, 5529);
MEC_IPSO_CONST(ClearDisplay, 5530);
MEC_IPSO_CONST(Contrast, 5531);
MEC_IPSO_CONST(IncreaseInputState, 5532);
MEC_IPSO_CONST(DecreaseInputState, 5533);
MEC_IPSO_CONST(Counter, 5534);
MEC_IPSO_CONST(CalibrationOffset, 5535);
MEC_IPSO_CONST(CurrentPosition, 5536);
MEC_IPSO_CONST(TransitionTime, 5537);
MEC_IPSO_CONST(RemainingTime, 5538);
MEC_IPSO_CONST(UpCounter, 5541);
MEC_IPSO_CONST(DownCounter, 5542);
MEC_IPSO_CONST(DigitalState, 5543);
MEC_IPSO_CONST(CumulativeTime, 5544);
MEC_IPSO_CONST(MaxXCoordinate, 5545);
MEC_IPSO_CONST(MaxYCoordinate, 5546);
MEC_IPSO_CONST(MultiStateInput, 5547);
MEC_IPSO_CONST(Level, 5548);
MEC_IPSO_CONST(DigitalOutputState, 5550);
MEC_IPSO_CONST(DigitalOutputPolarity, 5551);
MEC_IPSO_CONST(AnalogInputCurrentValue, 5600);
MEC_IPSO_CONST(MinMeasuredValue, 5601);
MEC_IPSO_CONST(MaxMeasuredValue, 5602);
MEC_IPSO_CONST(MinRangeValue, 5603);
MEC_IPSO_CONST(MaxRangeValue, 5604);
MEC_IPSO_CONST(ResetMinMaxMeasuredValues, 5605);
MEC_IPSO_CONST(AnalogOutputCurrentValue, 5650);
MEC_IPSO_CONST(SensorValue, 5700);
MEC_IPSO_CONST(SensorUnits, 5701);
MEC_IPSO_CONST(XValue, 5702);
MEC_IPSO_CONST(YValue, 5703);
MEC_IPSO_CONST(ZValue, 5704);
MEC_IPSO_CONST(CompassDirection, 5705);
MEC_IPSO_CONST(Colour, 5706);
MEC_IPSO_CONST(ApplicationType, 5750);
MEC_IPSO_CONST(SensorType, 5751);
MEC_IPSO_CONST(InstantaneousActivePower, 5800);
MEC_IPSO_CONST(MinMeasuredActivePower, 5801);
MEC_IPSO_CONST(MaxMeasuredActivePower, 5802);
MEC_IPSO_CONST(MinRangeActivePower, 5803);
MEC_IPSO_CONST(MaxRangeActivePower, 5804);
MEC_IPSO_CONST(CumulativeActivePower, 5805);
MEC_IPSO_CONST(ActivePowerCalibration, 5806);
MEC_IPSO_CONST(InstantaneousReactivePower, 5810);
MEC_IPSO_CONST(MinMeasuredReactivePower, 5811);
MEC_IPSO_CONST(MaxMeasuredReactivePower, 5812);
MEC_IPSO_CONST(MinRangeReactivePower, 5813);
MEC_IPSO_CONST(MaxRangeReactivePower, 5814);
MEC_IPSO_CONST(CumulativeReactivePower, 5815);
MEC_IPSO_CONST(ReactivePowerCalibration, 5816);
MEC_IPSO_CONST(PowerFactor, 5820);
MEC_IPSO_CONST(CurrentCalibration, 5821);
MEC_IPSO_CONST(ResetCumulativeEnergy, 5822);
MEC_IPSO_CONST(EventIdentifier, 5823);
MEC_IPSO_CONST(StartTime, 5824);
MEC_IPSO_CONST(DurationInMin, 5825);
MEC_IPSO_CONST(CriticalityLevel, 5826);
MEC_IPSO_CONST(AvgLoadAdjPct, 5827);
MEC_IPSO_CONST(DutyCycle, 5828);
MEC_IPSO_CONST(OnOff, 5850);
MEC_IPSO_CONST(Dimmer, 5851);
MEC_IPSO_CONST(OnTime, 5852);
MEC_IPSO_CONST(MultiStateOutput, 5853);
MEC_IPSO_CONST(OffTime, 5854);
MEC_IPSO_CONST(SetPointValue, 5900);
MEC_IPSO_CONST(BusyToClearDelay, 5903);
MEC_IPSO_CONST(ClearToBusyDelay, 5904);

}; // namespace Resource

namespace Object {

MEC_IPSO_CONST(DigitalInput, 3200);
MEC_IPSO_CONST(DigitalOutput, 3201);
MEC_IPSO_CONST(AnalogInput, 3202);
MEC_IPSO_CONST(AnalogOutput, 3203);
MEC_IPSO_CONST(GenericSensor, 3300);
MEC_IPSO_CONST(Illuminance, 3301);
MEC_IPSO_CONST(Presence, 3302);
MEC_IPSO_CONST(Temperature, 3303);
MEC_IPSO_CONST(Humidity, 3304);
MEC_IPSO_CONST(PowerMeasurement, 3305);
MEC_IPSO_CONST(Actuation, 3306);
MEC_IPSO_CONST(SetPoint, 3308);
MEC_IPSO_CONST(LoadControl, 3310);
MEC_IPSO_CONST(LightControl, 3311);
MEC_IPSO_CONST(PowerControl, 3312);
MEC_IPSO_CONST(Accelerometer, 3313);
MEC_IPSO_CONST(Magnetometer, 3314);
MEC_IPSO_CONST(Barometer, 3315);
MEC_IPSO_CONST(Voltage, 3316);
MEC_IPSO_CONST(Current, 3317);
MEC_IPSO_CONST(Frequency, 3318);
MEC_IPSO_CONST(Depth, 3319);
MEC_IPSO_CONST(Percentage, 3320);
MEC_IPSO_CONST(Altitude, 3321);
MEC_IPSO_CONST(Load, 3322);
MEC_IPSO_CONST(Pressure, 3323);
MEC_IPSO_CONST(Loudness, 3324);
MEC_IPSO_CONST(Concentration, 3325);
MEC_IPSO_CONST(Acidity, 3326);
MEC_IPSO_CONST(Conductivity, 3327);
MEC_IPSO_CONST(Power, 3328);
MEC_IPSO_CONST(PowerFactor, 3329);
MEC_IPSO_CONST(Distance, 3330);
MEC_IPSO_CONST(Energy, 3331);
MEC_IPSO_CONST(Direction, 3332);
MEC_IPSO_CONST(Time, 3333);
MEC_IPSO_CONST(Gyrometer, 3334);
MEC_IPSO_CONST(Colour, 3335);
MEC_IPSO_CONST(Location, 3336);
MEC_IPSO_CONST(Positioner, 3337);
MEC_IPSO_CONST(Buzzer, 3338);
MEC_IPSO_CONST(AudioClip, 3339);
MEC_IPSO_CONST(Timer, 3340);
MEC_IPSO_CONST(AddressableTextDisplay, 3341);
MEC_IPSO_CONST(OnOffSwitch, 3342);
MEC_IPSO_CONST(Dimmer, 3343);
MEC_IPSO_CONST(UpDownControl, 3344);
MEC_IPSO_CONST(MultipleAxisJoystick, 3345);
MEC_IPSO_CONST(Rate, 3346);
MEC_IPSO_CONST(PushButton, 3347);
MEC_IPSO_CONST(MultiStateSelector, 3348);
MEC_IPSO_CONST(Bitmap, 3349);
MEC_IPSO_CONST(Stopwatch, 3350);

}; // namespace Object

} // namespace ipso
} // namespace mec

#endif

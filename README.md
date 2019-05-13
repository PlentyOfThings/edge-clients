# Plenty of Things - A framework for monitoring and telemetry handling for embedded & low-level devices

This project is designed around providing various edge clients that can be loaded onto embedded or low-power devices which can then read sensor data and push these results up to a cloud system.

## Communication

All communication is based on the IPSO standard, meaning all inputs and ouputs are driven by the relative object/resource IDs.

### MQTT

The MQTT framework is based on an 'udge' system, where each letter is the action that is being performed.

- `u`
  - Send data up from the data to the MQTT broker
- `d`
  - Send data down from the MQTT broker to the device
- `g`
  - A request from the MQTT broker to the device that will cause the next up payload to include all of the resources requested
  - This is used to read values from resources that are not normally sent up on every up push
- `e`
  - A request from the MQTT broker to the device that will trigger the event resources listed

The MQTT topics look like this:

```
device/{deviceId}/{udge}/{messageType}(/{messageFormat})?
```

- `{deviceId}`
  - The id of the device that was given on registration
- `{udge}`
  - One of `u`, `d`, `g`, `e`
- `{messageType}`
  - Currently only `ipso`
  - Messages on this topic can be either JSON or BSON, so listeners should support both
- `{messageFormat}`
  - One of `json`, `bson`
  - Only used if configured on registration, otherwise it will be completely omitted

#### Payloads

The payload looks like this (described using TypeScript-like syntax):

```ts
interface Payload<T> {
  id: integer;
  instance: integer;
  timestamp: integer;
  resources: T;
}
```

In this payload, `T` depends on the udge request being performed. For `u` and `d`, it is

```ts
type ud = Record<integer, string | integer | float | boolean>
```

For the keys, JSON only allows strings, however they are always the resource ID (integer).

For `g` and `e`, `T` is

```ts
type ge = Array<integer>
```

Where each item is the resource ID to be requested, or to trigger.

### Timestamp

All timestamps are in standard unix time using seconds.

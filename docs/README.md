# Wokwi Bounce Chip

This custom chip for [Wokwi](https://wokwi.com/) adds a Bounce pattern to a digital signal.

- Modes: Off, Rise, Fall, Both (0-3)

- Duration: 100-5000 microseconds

## Pin names

| Name | Description                                                  |
| ---- | ------------------------------------------------------------ |
| OUT  | Signal output with bounce depending upon mode and duration settings |
| GND  | Ground                                                       |
| VCC  | Supply voltage                                               |

## Usage

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
  "dependencies": {
    "chip-bounce": "github:Dlloydev/Wokwi-Chip-Bounce@1.0.1"
  }
```

Then, add the chip to your circuit by adding a `chip-bounce` item to the `parts` section of `diagram.json`:

```json
  "parts": {
    ...,
    { "type": "chip-bounce", "id": "bounce1" }
  },
```

For a complete example, see [the inverter chip test project](https://wokwi.com/projects/350946636543820370).


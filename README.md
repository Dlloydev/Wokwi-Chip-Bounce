# Wokwi-Chip-Bounce
## Description

Add Bounce to digital signals

![image](https://user-images.githubusercontent.com/63488701/214121685-77287bfb-f89e-4659-bc47-1a539cc024c3.png)



![image](https://user-images.githubusercontent.com/63488701/214122079-1ff2a70b-f8e1-42f0-898e-86e880fe0507.png)

- Modes: Off, Rise, Fall, Both (0-3)
- Duration: 50-5000 microseconds
- Default control settings can be changed in `diagram.json`


## Usage

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
"dependencies": { "chip-bounce": "github:Dlloydev/Wokwi-Chip-Bounce@1.0.5" }
```

Then, add the chip to your circuit by adding a `chip-scope` item to the `parts` section of `diagram.json`:

```json
  "parts": {
    ...,
    {
      "type": "chip-bounce",
      "id": "bounce1",
      "top": -37.38,
      "left": -61.6,
      "attrs": { "mode": "3", "microseconds": "1000" }
    },
```

The actual source code for the chip lives in [src/main.c](https://github.com/Dlloydev/Wokwi-Chip-Bounce/blob/main/src/main.c), and the pins are described in [chip.json](https://github.com/Dlloydev/Wokwi-Chip-Bounce/blob/main/chip.json).

## Examples

[![Wokwi_badge](https://user-images.githubusercontent.com/63488701/212449119-a8510897-c860-4545-8c1a-794169547ba1.svg)](https://wokwi.com/projects/354227800838111233) Test a PWM signal with bounce added.

## License

This project is licensed under the MIT license. See the [LICENSE](https://github.com/Dlloydev/Wokwi-Chip-Bounce/blob/main/LICENSE) file for more details.

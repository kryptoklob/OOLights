# OOLights - Object-oriented based LED control system
## Summary
This project is a framework, incorporating FastLED, that runs LED patterns using
an object-oriented class system. All pattern effects are subclasses of `src/ledeffect.cpp`.

## Code Details
The main program loop (in `src/main.cpp`) iterates through each active effect, calling `render()`
and grabs the rendered pixel data stored in the effect's instance data, and then decides how to
combine rendered effects to send to the actual LED strip.


Timing is controlled by the `EVERY_N_MILLIS` function at the bottom of `main.cpp`; on an Arduino Mega 2560,
I was able to achieve a minimum frame-time of 10ms (200fps) with 6 effects running at once.
This would be much higher on a Teensy.


Configuration settings can be found in `include/vars.h` for things such as # of leds and pin assignments.

## Setup
This code probably will not open or compile within the base Arduino IDE; I use
[PlatformIO](https://platformio.org/platformio-ide) to code/compile/upload. You /can/
use this codebase with the Arduino IDE, but you'll have to mess around with the imports
and locations of files in order for the IDE to see everything it needs to.

## TODO (Soon)
- Implement a way to add/remove effects live

## TODO (SoonTM)
- Implement ESP32 + web dashboard support

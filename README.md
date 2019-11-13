# OOLights - Object-oriented based LED control system
This project is a framework, incorporating FastLED, that runs LED patterns using
an object-oriented class system. All pattern effects are subclasses of `src/ledeffect.cpp`.


The main program loop (in `src/main.cpp`) iterates through each active effect, calling `render()`
and grabs the rendered pixel data stored in the effect's instance data, and then decides how to
combine rendered effects to send to the actual LED strip.


Timing is controlled by the `EVERY_N_MILLIS` loop at the bottom of `main.cpp`; on an Arduino Mega 2560,
I was able to achieve a minimum frame-time of 10ms (200fps). This would be much higher on a Teensy.


Configuration settings can be found in `include/vars.h` for things such as # of leds and pin assignments.

#include <FastLED.h>
#include "variables.h"
#include "LedEffect.cpp"

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;
CRGBSet ledData(leds(0, NUM_LEDS));

// Holds all active led effect instances
LedEffect effects[3] = {1, 50, 100};

void setup() {
  // Set up serial connection
  Serial.begin(57600);
  Serial.setTimeout(1500);
  delay(1000);

  // Setup LEDs
  FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS);

  // Clear LEDS and show the empty frame
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Our main loop consists of the following logic:
  // 1 - iterate through our list of effects and call render() on each one to advance one step
  // 2 - use a blending technique to blend the effects and render to the output array
  // 3 - check keyboard/serial/other devices
  // 4 - write any output data to serial if necessary

  for(int i=0; i<3; i++) {
    effects[i].render();
  }

  // Grab & blend the data from each of our effects
  // I'm sure there's a better way to do this, right now we're just xoring!
  for(int i=0; i<NUM_LEDS-1; i++) {
    ledData[i] = effects[0].leddata[i] + effects[1].leddata[i] + effects[2].leddata[i];
  }

  FastLED.show();
}

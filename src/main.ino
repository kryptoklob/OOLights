#include <FastLED.h>
#include "variables.h"

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;

void setup() {
  // Set up serial connection
  Serial.begin(57600);
  Serial.setTimeout(1500);
  delay(1000);

  // Setup LEDs
  FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS);
}

void loop() {
  static uint8_t hue=0;
  leds(0, NUM_LEDS/2 - 1).fill_rainbow(hue++);
  leds(NUM_LEDS/2, NUM_LEDS-1) = leds(NUM_LEDS/2-1,0);
  FastLED.delay(30);
}

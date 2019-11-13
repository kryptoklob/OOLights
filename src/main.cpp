// --- This basic sketch / example uses 1 LED strip with 144 Leds
// --- You can change this in vars.h inside the /include folder

// Fast LED & other system imports
#include <FastLED.h>

// Our custom defines
#include "vars.h"

// Our led effect classes
#include "ledeffect.cpp"
#include "trails.cpp"
#include "bpm.cpp"
#include "strobe.cpp"
#include "halloween.cpp"
#include "cylon.cpp"

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;
CRGBSet ledData(leds(0, NUM_LEDS));

// Create effects here:
CylonEffect effect1(160,4);

// Note that these effects are disabled by default!
// @TODO switch to c++ vectors and implement a queue instead of array
// This array holds all effects:
LedEffect *effects[] = { &effect1 };
uint8_t num_effects = 1;

void setup() {
  delay(1000);

  // Setup LEDs
  FastLED.addLeds<APA102, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHT);
  FastLED.setCorrection(TypicalLEDStrip);

  // Clear LEDS and then flash red, green, blue just as a quick test
  FastLED.clear(); FastLED.show(); FastLED.delay(500);

  if (STARTUP_DEBUG) {
    leds.fill_solid(CRGB::Red); FastLED.show(); FastLED.delay(500);
    leds.fill_solid(CRGB::Green); FastLED.show(); FastLED.delay(500);
    leds.fill_solid(CRGB::Blue); FastLED.show(); FastLED.delay(500);
    FastLED.clear(); FastLED.show(); FastLED.delay(500);
  }

  // Enable whatever effects we want
  effect1.enable();
}

void renderActiveEffects() {
  // Iterate over every effect
  for(int i=0; i<num_effects; i++) {
    // Skip inactive / disabled effects
    if (!(effects[i] -> enabled)) {
      continue;
    }

    // Call the effect's render() method, which stores the rendered led data in an instance var
    effects[i] -> render();

    // Copy the led data over to the global array (additively)
    for (uint8_t j=0; j<NUM_LEDS-1; j++) {
      ledData[j] += (effects[i] -> leddata)[j];
    }
  }
}

// 10ms = 200fps
void loop() {
  EVERY_N_MILLIS(10) {
    FastLED.clear();
    renderActiveEffects();
    FastLED.show();
  }
}

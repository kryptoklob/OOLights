// --- This basic sketch / example uses 1 LED strip with 144 Leds
// --- You can change this in vars.h inside the /include folder

// Fast LED & other system imports
#include <FastLED.h>

// Our custom defines
#include "vars.h"

// Our classes
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

// Holds all active led effect instances
CylonEffect effect1;

// Note that these effects are disabled by default!
LedEffect *effects[] = { &effect1 };
uint8_t num_effects = 5;
uint32_t frame_number = 0;
unsigned long last_frame_time = 1;
unsigned long last_frame_length = 1;
unsigned long current_frame_time = 1;
unsigned long framerate = 1;

void setup() {
  // Set up serial connection
  //Serial.begin(57600);
  //Serial.setTimeout(1500);

  delay(1000);

  /*
  if (DEBUG) { Serial.println("DEBUG ON"); }
  else { Serial.println("DEBUG OFF"); }
  */

  // Setup LEDs
  FastLED.addLeds<APA102, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHT);
  FastLED.setCorrection(TypicalLEDStrip);

  // Clear LEDS and then flash red, green, blue just as a quick test
  FastLED.clear(); FastLED.show(); FastLED.delay(500);
  if (DEBUG) {
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
    // Skip any effects that are disabled
    if (!(effects[i] -> enabled)) {
      //if (DEBUG) { Serial.print("Effect render skipped - effect disabled for effect: "); Serial.println(i); }
      continue;
    }

    // Render each effect (data gets stored in the effects' leddata variable)
    //if (DEBUG) { Serial.print("Beginning effect & frame: "); Serial.print(i); Serial.print(" "); Serial.println(frame_number); }
    effects[i] -> render();
    //if (DEBUG) { Serial.print("Done with effect & frame: "); Serial.print(i); Serial.print(" "); Serial.println(frame_number); }

    // Copy the data over to the global array (additively)
    for (uint8_t j=0; j<NUM_LEDS-1; j++) {
      ledData[j] += (effects[i] -> leddata)[j];
    }
  }
}

void loop() {
  EVERY_N_MILLIS(10) {
    FastLED.clear();
    renderActiveEffects();
    FastLED.show();
  }
}

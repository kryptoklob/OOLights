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

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;
CRGBSet ledData(leds(0, NUM_LEDS));

// Holds all active led effect instances
TrailEffect effect1(1, 0, false);
TrailEffect effect2(NUM_LEDS-1, 1, true);
StrobeEffect effect3;
BPMEffect effect4(240);
// Note that these effects are disabled by default!
LedEffect *effects[] = { &effect1, &effect2, &effect3, &effect4 };
uint8_t num_effects = 4;
uint32_t frame_number = 0;
unsigned long last_frame_time = 1;
unsigned long last_frame_length = 1;
unsigned long current_frame_time = 1;
unsigned long framerate = 1;

void setup() {
  // Set up serial connection
  Serial.begin(57600);
  Serial.setTimeout(1500);

  delay(1000);

  if (DEBUG) { Serial.println("DEBUG ON"); }
  else { Serial.println("DEBUG OFF"); }

  // Setup LEDs
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHT);

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
  effect2.enable();
  effect3.enable();
  effect4.enable();
}

void loop() {
  // Our main loop consists of the following logic:
  // 1 - iterate through our list of effects and call render() on each one to advance one step
  // 2 - use a blending technique to blend the effects and render to the output array
  // 3 - check keyboard/serial/other devices
  // 4 - write any output data to serial if necessary

  FastLED.clear();

  // Iterate over every effect
  for(int i=0; i<num_effects; i++) {
    // Skip any effects that are disabled
    if (!(effects[i] -> enabled)) {
      if (DEBUG) { Serial.print("Effect render skipped - effect disabled for effect: "); Serial.println(i); }
      continue;
    }

    // Render each effect (data gets stored in the effects' leddata variable)
    if (DEBUG) { Serial.print("Beginning effect & frame: "); Serial.print(i); Serial.print(" "); Serial.println(frame_number); }
    effects[i] -> render();
    if (DEBUG) { Serial.print("Done with effect & frame: "); Serial.print(i); Serial.print(" "); Serial.println(frame_number); }

    // Copy the data over to the global array (additively)
    for (uint8_t j=0; j<NUM_LEDS-1; j++) {
      ledData[j] += (effects[i] -> leddata)[j];
    }
  }

  if (DEBUG) { Serial.print("Global frame complete: "); Serial.println(frame_number); }
  frame_number++;

  if (FRAMERATE_DEBUG) {
    current_frame_time = micros();
    last_frame_length = current_frame_time - last_frame_time;
    last_frame_time = current_frame_time;
    framerate = 1000000 / last_frame_length;
    // framerate = 1,000,000 / micros_frametime;
    // print framerate every 100 cycles so that the serial printing time doesn't affect it much
    if(frame_number % 100 == 1) {
      Serial.print("Framerate, frametime: ");
      Serial.print(framerate);
      Serial.print(" ");
      Serial.println(last_frame_length);
    }
  }

  FastLED.show();
}

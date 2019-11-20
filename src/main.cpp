// --- This basic sketch / example uses 1 LED strip with 144 Leds
// --- You can change this in vars.h inside the /include folder

// Fast LED & other system imports
#include <FastLED.h>
#include <Vector.h>

// Our custom defines
#include "vars.h"

// Our led effect classes
#include "ledeffect.cpp"
#include "trails.cpp"
#include "bpm.cpp"
#include "strobe.cpp"
#include "halloween.cpp"
#include "cylon.cpp"
#include "cubiccylon.cpp"
#include "fadingwaves.cpp"

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;
CRGBSet ledData(leds(0, NUM_LEDS));

// Create effects here:
//CylonEffect effect1(160,4);
CubicCylonEffect effect1;

// Vector class to hold the effects
// Very similar to c++ std::vector - see https://github.com/tomstewart89/Vector
Vector<LedEffect*> effects;

void setup() {
  Serial.println("<BEGIN SETUP>");

  // Enable Serial
  Serial.begin(SERIAL_BAUDRATE);
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

  // Add effects to the Vector array
  effects.PushBack(&effect1);

  // Enable whatever effects we want
  effect1.enable();

  Serial.println("<END SETUP>");
  Serial.println(" ");
}

void renderActiveEffects() {
  // Iterate over every effect
  for(int i=0; i<effects.Size(); i++) {
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

// Handle input - just a single character.
// This could come from anywhere, but right now it's just Serial/keyboard.
void handleInput(char input) {
  Serial.println("--> Input Received");

  // Super basic right now - just enable the number specified.
  // If not 0-9, do nothing.
  // Note: 0-9 is represented by char codes 48 thru 57
  if (input < 48 || input > 57) {
    Serial.print("   Garbage input detected: ");
    Serial.println(input);
    return;
  }

  Serial.print("--> Valid input detected: ");
  Serial.println(input);

  Serial.print("--> Toggling effect ");
  Serial.println(input - 48);
  Serial.println(" ");

  effects[input - 48]->toggle();
}

// Print all current effects to console (and their status)
void displayEffectData() {
  Serial.println("--- Current Effects ---");

  for(uint8_t i=0; i<effects.Size(); i++){
    Serial.print("--> Effect ");
    Serial.print(i);
    Serial.print(": ");

    if (effects[i]->enabled) {
      Serial.print("enabled ");
    } else {
      Serial.print("disabled ");
    }

    Serial.println(" ");
  }

  Serial.println("-----------------------");
  Serial.println(" ");
}

// 10ms = 200fps
void loop() {
  EVERY_N_MILLIS(10) {
    FastLED.clear();
    renderActiveEffects();
    FastLED.show();
  }

  EVERY_N_MILLIS(5000) {
    displayEffectData();
  }

  if (Serial.available() > 0) {
    handleInput(Serial.read());
  }
}

#ifndef HALLOWEEN_H
#define HALLOWEEN_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LEDEffect abstract class.
class HalloweenEffect: public LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables
    CRGB fading_to = CRGB(CRGB::Purple);
    uint8_t num_leds_left = NUM_LEDS;

  public:
    // Default constructor
    HalloweenEffect() {
      leddata(0, NUM_LEDS-1) = CRGB::DarkOrange;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // Randomly pick leds to fade to purple
      // Once done, start fading to orange, then goto 1
      uint8_t led_number = random8() % NUM_LEDS; // picks a random number between 0 and NUM_LEDS-1
      if (leddata.leds[led_number] != fading_to) {
        num_leds_left--;
        leddata[led_number] = fading_to;
      }
      if (num_leds_left == 0) {
        if (fading_to == CRGB(CRGB::Purple)) { fading_to = CRGB::DarkOrange; } else { fading_to = CRGB::Purple; }
        num_leds_left = NUM_LEDS;
      }
    }
};

#endif

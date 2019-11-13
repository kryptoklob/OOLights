#ifndef HALLOWEEN_H
#define HALLOWEEN_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LEDEffect abstract class.
class HalloweenEffect: public LedEffect {
  private:
    CRGB fading_to = CRGB(CRGB::Purple);
    uint8_t num_leds_left = NUM_LEDS/2;
    uint8_t counter;
    uint8_t speedDivisor;

  public:
    // Default constructor - 4x slowdown
    HalloweenEffect() {
      leddata(11, NUM_LEDS-1) = CRGB::DarkOrange;
      counter = 0;
      speedDivisor = 4;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // At 200 fps, this goes about 4x too fast. Let's slow it down.
      // Only render once every 4 calls to render (by defaul, also uses provided speed divisor)
      counter++;
      if (counter%speedDivisor != 0) { return; }

      // Randomly pick leds to fade to purple
      // Once done, start fading to orange, then goto 1
      uint8_t led_number = random8() % NUM_LEDS/2 + 15; // picks a random number between 0 and NUM_LEDS-1

      if (leddata.leds[led_number] != fading_to) {
        num_leds_left--;
        leddata[led_number] = fading_to;
        leddata[NUM_LEDS - led_number - 1] = fading_to;
      }

      if (num_leds_left == 0) {
        if (fading_to == CRGB(CRGB::Purple)) { fading_to = CRGB::DarkOrange; } else { fading_to = CRGB::Purple; }
        num_leds_left = NUM_LEDS/2;
      }
      leddata.fadeToBlackBy(5);
    }
};

#endif

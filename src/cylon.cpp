#ifndef CYLON_H
#define CYLON_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
class CylonEffect: public LedEffect {
  private:
    uint8_t index;
    uint8_t hue;
    char direction; // 0 = right, 1 = left

  public:
    // Default constructor - color red, 4x slowdown
    CylonEffect(uint8_t providedHue=0, uint8_t providedSpeedDivisor=4) {
      index = 0;
      direction = 0;
      counter = 0;
      speedDivisor = providedSpeedDivisor;
      hue = providedHue;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // At 200 fps, this goes about 4x too fast. Let's slow it down.
      // Only render once every 4 calls to render (by defaul, also uses provided speed divisor)
      counter++;
      if (counter%speedDivisor != 0) { return; }

      if (index == 0 && direction == 1) {
        // Going left and we're at the first led, reverse direction
        direction = 0;
      } else if (index == NUM_LEDS-1 && direction == 0) {
        // Going right and we're at the last led, reverse direction
        direction = 1;
      }

      // Increment or decrement the led per direction
      if (direction==0) { index++; } else { index--; }

      // Turn on the led.
      leddata[index] = CHSV(hue, 255, 255);

      // Fade the whole damn thing
      leddata.nscale8(225);
    }
};

#endif

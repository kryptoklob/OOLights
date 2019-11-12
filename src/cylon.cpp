#ifndef CYLON_H
#define CYLON_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
class CylonEffect: public LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables
    uint8_t index;
    uint8_t hue;
    uint8_t counter;
    char direction; // 0 = right, 1 = left

  public:
    // Default constructor - random starting index, random hue, going forward
    CylonEffect() {
      index = 0;
      direction = 0;
      hue = 0;
      counter = 0;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // At 200 fps, this goes about 4x too fast. Let's slow it down.
      // Only render once every 4 calls to render.
      counter++;
      if (counter%4 != 0) { return; }


      if (index == 0 && direction == 1) {
        // Going left and we're at the first led, reverse direction
        direction = 0;
      } else if (index == NUM_LEDS-1 && direction == 0) {
        // Going right and we're at the last led, reverse direction
        direction = 1;
      }

      if (direction==0) { index++; } else { index--; }

      leddata[index] = CRGB::Red;
      leddata.nscale8(225);
    }
};

#endif

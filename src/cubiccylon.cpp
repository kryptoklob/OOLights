#ifndef CUBICCYLON_H
#define CUBICCYLON_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
// CubicCylonEffect uses cubicwave8 to achieve SyFy-Approved Realistic Cylon Eyes. Supposedly.
class CubicCylonEffect: public LedEffect {
  private:


  public:
    // Default constructor - color red, 4x slowdown
    CubicCylonEffect(uint8_t providedHue=0, uint8_t providedSpeedDivisor=4) {

    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      leddata.fadeToBlackBy(20);
      uint8_t index = beatsin16(13, 0, NUM_LEDS-1);
      leddata[index] = CRGB::Red;
    }
};

#endif

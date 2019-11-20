#ifndef CUBICCYLON_H
#define CUBICCYLON_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
// CubicCylonEffect uses cubicwave8 to achieve SyFy-Approved Realistic Cylon Eyes. Supposedly.
class CubicCylonEffect: public LedEffect {
  private:
    uint8_t numDots;
    uint16_t phaseOffset; // How many leds apart each set is
    uint8_t hueOffset; // How offset each dot is in hue from the other
    uint8_t bpm; // How many cycles we complete in a minute
    bool trails; // Whether or not each dot is going to have trails

  public:
    // Default constructor
    // Note: many dots with trails make for a cool Aurora-like effect!
    // 48 dots with 15 bpm is pretty.
    CubicCylonEffect(uint8_t howManyDots=1, uint8_t providedBPM = 13, bool trailsEnabled=false) {
      numDots = howManyDots;
      phaseOffset = 32678 / numDots;
      hueOffset = 255 / numDots;
      bpm = providedBPM;
      trails = trailsEnabled;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    // Spread out the dots so they're evenly placed
    void render() {
      if (!trails) { leddata(0, NUM_LEDS-1) = CRGB::Black; }
      else { leddata.fadeToBlackBy(20); }

      for (uint8_t i=0; i<numDots; i++) {
        uint8_t index = beatsin16(bpm, 1, NUM_LEDS-2, 2513, phaseOffset*(i*2));
        leddata(index-1, index+1) |= CHSV(i*hueOffset, 255, 255);
      }
    }
};

#endif

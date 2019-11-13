#ifndef STROBE_H
#define STROBE_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LEDEffect abstract class.
class StrobeEffect: public LedEffect {
  private:
    uint8_t bright;
    uint8_t hue;

  public:
    // Default constructor
    StrobeEffect(uint8_t providedHue=0) {
      bright = 0;
      if (hue == 0) { hue = random8(); } else { hue = providedHue; }
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      if (bright >= 254) { bright = 0; hue=random8(); }
      leddata.fill_solid(CHSV(hue, 255, bright+=15));
    }
};

#endif

#ifndef FADINGWAVES_H
#define FADINGWAVES_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
class FadingWavesEffect: public LedEffect {
  private:


  public:
    // Default constructor - color red, 4x slowdown
    FadingWavesEffect() {

    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // At 200 fps, this goes about 4x too fast. Let's slow it down.
      // Only render once every 4 calls to render (by default, also uses provided speed divisor)


    }
};

#endif

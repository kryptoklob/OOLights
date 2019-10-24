#ifndef SYMMETRIC_TRAILS_H
#define SYMMETRIC_TRAILS_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
class SymmetricTrailsEffect: public LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables
    int index;
    int direction;
    int hue;


  public:
    // Each LedEffect instance has its own array to write led data to
    // The below line is commented out, because the abstract class ledEffect already has this variable implemented.
    //CRGBArray<NUM_LEDS> leddata;

    // Default constructor - random starting index, random hue
    SymmetricTrailsEffect(uint8_t startIndex=0, uint8_t startHue=0, bool reverse=false) {
      index=startIndex;
      if (startIndex == 0) {
        index = random16() % NUM_LEDS;
      } else index = startIndex;
      if (reverse) { direction = 1; } else { direction = 0; }
      if (startHue == 0) {
        hue = random8();
      } else hue = startHue;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // This example effect just moves a dot up and down the strip
      // Dot has a trail of less-saturated leds
      if (direction == 0) { index++; } else { index--; }
      if (index == 0 && direction == 1) { direction = 0; }
      if (index == NUM_LEDS-1 && direction == 0) { direction = 1; }

      leddata.fadeToBlackBy(10);
      leddata[index] = CHSV(hue++, 255, 128);
    }
};

#endif

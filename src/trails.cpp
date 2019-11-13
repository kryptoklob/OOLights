#ifndef TRAIL_H
#define TRAIL_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LedEffect abstract class
class TrailEffect: public LedEffect {
  private:
    uint8_t index;
    bool direction;
    uint8_t hue;
    uint8_t rotate_hue;

  public:
    // Default constructor - random starting index, random hue, going forward
    TrailEffect(uint8_t startIndex=0, uint8_t startHue=0, bool reverse=false, bool enableHueRotation=true) {
      index=startIndex;
      rotate_hue = enableHueRotation;
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
      if (direction == 0) { index++; } else { index--; }
      if (index == 0 && direction == 1) { direction = 0; }
      if (index == NUM_LEDS-1 && direction == 0) { direction = 1; }

      leddata.fadeToBlackBy(13);
      leddata[index] = CHSV(hue, 255, 128);
      if (rotate_hue) {hue++;}
    }
};

#endif

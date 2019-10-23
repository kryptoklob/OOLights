#include <FastLed.h>
#include "variables.h"

// The LedEffect super class. All instances of leds effects should subclass from this
class LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables
    int index;
    int direction;


  public:
    // Each LedEffect instance has its own array to write led data to
    CRGBArray<NUM_LEDS> leddata;

    // Default constructor
    LedEffect(uint8_t startIndex=0) {
      index=startIndex;
      direction=0; // (0 - moving right; 1 - moving left)
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // This example effect just moves a dot up and down the strip
      if (direction == 0) { index++; } else { index--; }
      if (index == 0 && direction == 1) { direction = 0; }
      if (index == NUM_LEDS-1 && direction == 0) { direction = 1; }

      leddata.fill_solid(CRGB::Black);
      leddata[index] = CRGB::Red;
    }
};

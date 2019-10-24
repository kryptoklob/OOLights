#ifndef LED_EFFECT_H
#define LED_EFFECT_H

#include <FastLED.h>
#include "vars.h"

// This is the LedEffect abstract class. All other led effects should implement the required functions here.
class LedEffect {
  public:
    bool enabled;
    CRGBArray<NUM_LEDS> leddata;
    virtual void render() = 0;

    void enable() {
      enabled = true;
    }

    void disable() {
      enabled = false;
    }

    void toggle() {
      enabled = !enabled;
    }
};

// That's it! Any class that implements this interface just has to impelement render.
#endif

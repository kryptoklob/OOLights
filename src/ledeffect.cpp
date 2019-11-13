#ifndef LED_EFFECT_H
#define LED_EFFECT_H

#include <FastLED.h>
#include "vars.h"

// This is the LedEffect abstract class. All other led effects should implement the required functions here.
class LedEffect {
  protected:
    // The speed divisor controls how fast the effect runs.
    // Higher speed divisor = slower effect.
    // 1 = full speed.
    uint8_t speedDivisor;

    // The counter is used with the speed divisor to track how many times
    // we've called into render(); we only render when counter%speedDivisor=0 is true.
    uint8_t counter;

  public:
    // Whether or not the effect is enabled or not.
    // Disabled effects are not called into from the main loop.
    bool enabled;

    // Each effect has its own leddata storage, which is populated when render() is called.
    CRGBArray<NUM_LEDS> leddata;

    // Each effect class must implement render(), which populates the led array when called.
    virtual void render() = 0;

    // Some premade functions for every class:
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

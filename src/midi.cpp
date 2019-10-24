#ifndef SYMMETRIC_TRAILS_H
#define SYMMETRIC_TRAILS_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LEDEffect abstract class.
class MidiEffect: public LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables



  public:
    // Each LedEffect instance has its own array to write led data to
    // The below line is commented out, because the abstract class ledEffect already has this variable implemented.
    //CRGBArray<NUM_LEDS> leddata;

    // Default constructor - random starting index, random hue
    MidiEffect() {

    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {

    }
};

#endif

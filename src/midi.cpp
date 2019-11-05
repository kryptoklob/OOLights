#ifndef SYMMETRIC_TRAILS_H
#define SYMMETRIC_TRAILS_H

#include <FastLED.h>
#include <MIDI.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LEDEffect abstract class.
class MidiEffect: public LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables
    uint16_t counter;


  public:
    // Default constructor
    MidiEffect() {
      counter = 0;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      leddata.fadeToBlackBy(1);
    }

    void NoteOn(byte channel, byte pitch, byte velocity) {
      //leddata(15) = CRGB::Blue;
    }

    void Note(byte key, byte intensity){
      // lowest key - 40
      // highest - 90
      // [0-50]
      // lowest led - 22
      // highest led - 122
      // [0-100]
      // 100 leds, 50 keys
      // simple - every key gets 2 leds
      uint8_t starting_led = ((key-40)*2) + 22;

      leddata(NUM_LEDS - starting_led, NUM_LEDS - starting_led + 1) |= CHSV(intensity, 255, 255);
      leddata(0, 22).addToRGB(5);
      leddata(NUM_LEDS-22, NUM_LEDS-1).addToRGB(5);
      //leddata(0, 10).addToRGB(intensity*2);
      //leddata(NUM_LEDS-10, NUM_LEDS-1).addToRGB(intensity*2);
    }

    void NoteOff(byte channel, byte pitch, byte velocity) {
      //leddata(0, pitch) = CRGB::Red;
    }
};

#endif

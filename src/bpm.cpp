#ifndef BPM_H
#define BPM_H

#include <FastLED.h>
#include "vars.h"
#include "ledeffect.cpp"

// We subclass from the LEDEffect abstract class.
class BPMEffect: public LedEffect {
  // BPM Effect flashes different segments of the LED strip to a variable BPM!
  // It's cool and stuff.

  private:
    // Each LedEffect subclass will have its own private variables
    uint32_t bpm;
    uint8_t hue;
    // The length the leds will be on, as demarked in note-size
    // So 2 = 1/2 note, or half of the beat length
    // 8 = 1/8th note, or 1/8th of the beat length
    uint8_t beat_size;
    uint16_t cutoff;

  public:
    // Default constructor - random starting index, random hue
    BPMEffect(uint32_t suppliedBpm) {
      bpm = suppliedBpm;
      hue = 0;
      beat_size = 4;
      cutoff = 65536 / beat_size;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      if (beat16(bpm) < cutoff) { leddata(NUM_LEDS-11, NUM_LEDS-1) = CHSV(hue++, 255, 255); leddata(0, 10) = CHSV(hue, 255, 255); }
      else { leddata.fill_solid(CRGB::Black); }
    }

    void setBPM(uint32_t suppliedBPM) {
      bpm = suppliedBPM;
    }
};

#endif

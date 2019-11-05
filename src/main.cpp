// --- This basic sketch / example uses 1 LED strip with 144 Leds
// --- You can change this in vars.h inside the /include folder

// Fast LED & other system imports
#include <FastLED.h>
#include <MIDI.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>


// Our custom defines
#include "vars.h"

// Our classes
#include "ledeffect.cpp"
#include "trails.cpp"
#include "bpm.cpp"
#include "strobe.cpp"
#include "halloween.cpp"
#include "midi.cpp"

// Some forward declarations:
void NoteOn(byte channel, byte pitch, byte velocity);
void NoteOff(byte channel, byte pitch, byte velocity);

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;
CRGBSet ledData(leds(0, NUM_LEDS));

// Holds all active led effect instances
//TrailEffect effect1(1, 0, false);
//TrailEffect effect2(NUM_LEDS-1, 1, true);
//StrobeEffect effect3;
//BPMEffect effect4(127);
//HalloweenEffect effect5;
MidiEffect effect1;
// Note that these effects are disabled by default!
LedEffect *effects[] = {&effect1};
uint8_t num_effects = 1;
uint32_t frame_number = 0;
unsigned long last_frame_time = 1;
unsigned long last_frame_length = 1;
unsigned long current_frame_time = 1;
unsigned long framerate = 1;

byte incomingByte;
uint8_t state;
byte channel = 1;
byte note;
byte noteDown;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);
//MIDI_CREATE_DEFAULT_INSTANCE();
//SoftwareSerial softSerial(10, 11);
//MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, MIDI);

void setup() {
  // Set up serial connection
  //if (DEBUG || DEBUG_FRAMERATE) {
  //  Serial.begin(57600);
  //  Serial.setTimeout(1500);
  //}
  //Serial.begin(115200);


  delay(1000);

  // Setup LEDs
  //FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<APA102, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHT);
  FastLED.setCorrection(TypicalLEDStrip);

  // Setup midi
  MIDI.begin(1);
  MIDI.turnThruOff();
  //MIDI.turnThruOff();
  //MIDI.setHandleNoteOn(NoteOn);
  //MIDI.setHandleNoteOff(NoteOff);

  // Clear LEDS and then flash red, green, blue just as a quick test
  FastLED.clear(); FastLED.show(); FastLED.delay(500);

  if (DEBUG_STARTCOLOR) {
    //leds.fill_solid(CRGB::Red); FastLED.show(); FastLED.delay(500);
    //leds.fill_solid(CRGB::Green); FastLED.show(); FastLED.delay(500);
    leds.fill_solid(CRGB::Blue); FastLED.show(); FastLED.delay(500);
    FastLED.clear(); FastLED.show(); FastLED.delay(500);
  }

  // Enable whatever effects we want
  //effect1.enable();
  //effect2.enable();
  //effect3.enable();
  //effect4.enable();
  //effect5.enable();
  effect1.enable();
}

/*
void NoteOn(byte channel, byte pitch, byte velocity) {
  effect1.NoteOn(channel, pitch, velocity);
}

void NoteOff(byte channel, byte pitch, byte velocity) {
  effect1.NoteOff(channel, pitch, velocity);
}*/

void loop() {
  // Our main loop consists of the following logic:
  // 1 - iterate through our list of effects and call render() on each one to advance one step
  // 2 - use a blending technique to blend the effects and render to the output array
  // 3 - check keyboard/serial/other devices
  // 4 - write any output data to serial if necessary

  //FastLED.clear();

  EVERY_N_MILLIS(10) {
    effects[0]->render();
    ledData = effects[0]->leddata;
    FastLED.show();
  }

  if (MIDI.read()) {
    byte type = MIDI.getType();
    byte data1 = MIDI.getData1();
    byte data2 = MIDI.getData2();

    /*
    Serial.print(type);
    Serial.print(" ");
    Serial.print(data1);
    Serial.print(" ");
    Serial.print(data2);
    Serial.print("    ");
    Serial.print(type, BIN);
    Serial.print(" ");
    Serial.print(data1, BIN);
    Serial.print(" ");
    Serial.println(data2, BIN);
    */

    if (type == 144 && data1 >= 40 && data1 <= 90) {
      //Serial.println(data1);
      effect1.Note(data1, data2);
    }
  }



  /*
  // Iterate over every effect
  for(int i=0; i<num_effects; i++) {
    // Skip any effects that are disabled
    if (!(effects[i] -> enabled)) {
      if (DEBUG) { Serial.print("Effect render skipped - effect disabled for effect: "); Serial.println(i); }
      continue;
    }

    // Render each effect (data gets stored in the effects' leddata variable)
    if (DEBUG) { Serial.print("Beginning effect & frame: "); Serial.print(i); Serial.print(" "); Serial.println(frame_number); }
    effects[i] -> render();
    if (DEBUG) { Serial.print("Done with effect & frame: "); Serial.print(i); Serial.print(" "); Serial.println(frame_number); }

    // Copy the data over to the global array (additively)
    for (uint8_t j=0; j<NUM_LEDS-1; j++) {
      ledData[j] += (effects[i] -> leddata)[j];
    }
  }

  if (DEBUG) { Serial.print("Global frame complete: "); Serial.println(frame_number); }
  frame_number++;

  if (DEBUG_FRAMERATE) {
    current_frame_time = micros();
    last_frame_length = current_frame_time - last_frame_time;
    last_frame_time = current_frame_time;
    framerate = 1000000 / last_frame_length;
    // framerate = 1,000,000 / micros_frametime;
    // print framerate every 100 cycles so that the serial printing time doesn't affect it much
    if(frame_number % 100 == 1) {
      Serial.print("Framerate, frametime: ");
      Serial.print(framerate);
      Serial.print(" ");
      Serial.println(last_frame_length);
    }
  }*/
  //effects[0]->render();
  //ledData = effects[0]->leddata;
  //FastLED.show();
}

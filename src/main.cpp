// --- This basic sketch / example uses 1 LED strip with 144 Leds
// --- You can change this in vars.h inside the /include folder

// Fast LED & other system imports
#include <FastLED.h>
#include <Vector.h>

// Comment out the below if NOT using ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Our custom defines
#include "vars.h"
//#include "cube_side_defines.h"

// Our led effect classes
#include "ledeffect.cpp"
#include "trails.cpp"
#include "bpm.cpp"
#include "strobe.cpp"
#include "halloween.cpp"
#include "cylon.cpp"
#include "cubiccylon.cpp"
#include "fadingwaves.cpp"

// Create the master led array
// Declarations such as NUM_LEDS... are in variables.h
CRGBArray<NUM_LEDS> leds;
CRGBSet ledData(leds(0, NUM_LEDS));

// The actual led data arrays (see RGBSet / CRGBArray reference on FastLED Github)
/*
CRGBArray<NUM_LEDS_FACE_ONE> leds_face_one;
CRGBArray<NUM_LEDS_FACE_TWO> leds_face_two;
CRGBArray<NUM_LEDS_FACE_THREE> leds_face_three;
CRGBArray<NUM_LEDS_FACE_FOUR> leds_face_four;
CRGBArray<NUM_LEDS_FACE_FIVE> leds_face_five;
CRGBArray<NUM_LEDS_FACE_SIX> leds_face_six;
*/

// CRGBSets to control the leds
// @TODO figure out which one is backwards and apply the negative length modifier to fix
/*
CRGBSet face_one_mapping(leds_face_one, NUM_LEDS_FACE_ONE);
CRGBSet face_two_mapping(leds_face_two, NUM_LEDS_FACE_TWO);
CRGBSet face_three_mapping(leds_face_three, NUM_LEDS_FACE_THREE);
CRGBSet face_four_mapping(leds_face_four, NUM_LEDS_FACE_FOUR);
CRGBSet face_five_mapping(leds_face_five, NUM_LEDS_FACE_FIVE);
CRGBSet face_six_mapping(leds_face_six, NUM_LEDS_FACE_SIX);
*/

// Here we go:
/*
CRGBSet face_one_mappings[4] = {
  CRGBSet(face_one_mapping, FACE_ONE_SIDE_ONE_START, FACE_ONE_SIDE_ONE_END),
  CRGBSet(face_one_mapping, FACE_ONE_SIDE_TWO_START, FACE_ONE_SIDE_TWO_END),
  CRGBSet(face_one_mapping, FACE_ONE_SIDE_THREE_START, FACE_ONE_SIDE_THREE_END),
  CRGBSet(face_one_mapping, FACE_ONE_SIDE_FOUR_START, FACE_ONE_SIDE_FOUR_END)
};

CRGBSet face_two_mappings[4] = {
  CRGBSet(face_two_mapping, FACE_TWO_SIDE_ONE_START, FACE_TWO_SIDE_ONE_END),
  CRGBSet(face_two_mapping, FACE_TWO_SIDE_TWO_START, FACE_TWO_SIDE_TWO_END),
  CRGBSet(face_two_mapping, FACE_TWO_SIDE_THREE_START, FACE_TWO_SIDE_THREE_END),
  CRGBSet(face_two_mapping, FACE_TWO_SIDE_FOUR_START, FACE_TWO_SIDE_FOUR_END)
};

CRGBSet face_three_mappings[4] = {
  CRGBSet(face_three_mapping, FACE_THREE_SIDE_ONE_START, FACE_THREE_SIDE_ONE_END),
  CRGBSet(face_three_mapping, FACE_THREE_SIDE_TWO_START, FACE_THREE_SIDE_TWO_END),
  CRGBSet(face_three_mapping, FACE_THREE_SIDE_THREE_START, FACE_THREE_SIDE_THREE_END),
  CRGBSet(face_three_mapping, FACE_THREE_SIDE_FOUR_START, FACE_THREE_SIDE_FOUR_END)
};

CRGBSet face_four_mappings[4] = {
  CRGBSet(face_four_mapping, FACE_FOUR_SIDE_ONE_START, FACE_FOUR_SIDE_ONE_END),
  CRGBSet(face_four_mapping, FACE_FOUR_SIDE_TWO_START, FACE_FOUR_SIDE_TWO_END),
  CRGBSet(face_four_mapping, FACE_FOUR_SIDE_THREE_START, FACE_FOUR_SIDE_THREE_END),
  CRGBSet(face_four_mapping, FACE_FOUR_SIDE_FOUR_START, FACE_FOUR_SIDE_FOUR_END)
};
*/

// Now that we have these mappings, let's create a data structure that holds which direction the
// leds need to go in order to have things like "all up", "all down", "all towards mid" and so on.
// Note that the shortest side length we have is 57 leds.
// The led effect will ahve a "reference" lenght of 60 leds (max side length), which can be adjusted
// down to the min of 57 leds for sides that need it (by selectively copying to cut out non-vital leds)

// Create effects here:
// CylonEffect effect1(160,4);
CubicCylonEffect effect1(24, 15, true, true);

// Vector class to hold the effects
// Very similar to c++ std::vector - see https://github.com/tomstewart89/Vector
Vector<LedEffect*> effects;

void setup() {
  // Enable Serial
  if (SERIAL_ENABLED) {
    Serial.begin(SERIAL_BAUDRATE);
    delay(1000);
  }

  //enableWifi();

  Serial.println("<BEGIN SETUP>");

  /*
  // -- Six strips of LEDS, each nominally 240 leds (but slightly less) -------------------- //
	FastLED.addLeds<LED_TYPE, LED_PIN_ONE, COLOR_ORDER>(leds_face_one, NUM_LEDS_FACE_ONE);
  FastLED.addLeds<LED_TYPE, LED_PIN_TWO, COLOR_ORDER>(leds_face_two, NUM_LEDS_FACE_TWO);
	FastLED.addLeds<LED_TYPE, LED_PIN_THREE, COLOR_ORDER>(leds_face_three, NUM_LEDS_FACE_THREE);
	FastLED.addLeds<LED_TYPE, LED_PIN_FOUR, COLOR_ORDER>(leds_face_four, NUM_LEDS_FACE_FOUR);
	FastLED.addLeds<LED_TYPE, LED_PIN_FIVE, COLOR_ORDER>(leds_face_five, NUM_LEDS_FACE_FIVE);
	FastLED.addLeds<LED_TYPE, LED_PIN_SIX, COLOR_ORDER>(leds_face_six, NUM_LEDS_FACE_SIX);
  // --------------------------------------------------------------------------------------- //
  */

  FastLED.addLeds<APA102, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

  FastLED.setBrightness(MAX_BRIGHT);
  FastLED.setCorrection(TypicalLEDStrip);

  // Clear LEDS and then flash red, green, blue just as a quick test
  FastLED.clear(); FastLED.show(); FastLED.delay(500);

  if (STARTUP_DEBUG) {
    leds.fill_solid(CRGB::Red); FastLED.show(); FastLED.delay(500);
    leds.fill_solid(CRGB::Green); FastLED.show(); FastLED.delay(500);
    leds.fill_solid(CRGB::Blue); FastLED.show(); FastLED.delay(500);
    FastLED.clear(); FastLED.show(); FastLED.delay(500);
  }

  // Add effects to the Vector array
  effects.PushBack(&effect1);

  // Enable whatever effects we want
  effect1.enable();

  Serial.println("<END SETUP>");
  Serial.println(" ");
}

/*
// Given a pointer to a source set & a destination set, shrink the source
// to fit the destination and copy elements over (additively)
void shrinkCopy(CRGBSet* source, CRGBSet* destination) {
  // Quick and dirty - leds 20-22, 38-40 are subject to destruction
  int size = destination -> size();

  // If size is 60 just do a standard copy
  if (size == 60) { *destination = *source; return; }

  // If size is 59 remove 20
  if (size == 59) {
    (*destination)(0, 19) = (*source)(0, 19); // lengths: 20, 20
    (*destination)(20, 58) = (*source)(21, 59); // lengths: 39, 39
    return;
  }

  if (size == 58) {
    // If size is 58, remove 20 and 40
    (*destination)(0, 19) = (*source)(0, 19); // lengths: 20, 20
    (*destination)(20, 38) = (*source)(21, 39); // lengths: 19, 19
    (*destination)(39, 57) = (*source)(41, 59); // lengths: 19, 19
    return;
  }

  if (size == 57) {
    // If size is 57, remove 20, 40, and 41
    (*destination)(0, 19) = (*source)(0, 19); // lengths: 20, 20
    (*destination)(20, 38) = (*source)(21, 39); // lengths: 19, 19
    (*destination)(39, 56) = (*source)(42, 59); // lengths: 18, 18
    return;
  }
}
*/

void renderActiveEffects() {
  // Iterate over every effect
  for(int i=0; i<effects.Size(); i++) {
    // Skip inactive / disabled effects
    if (!(effects[i] -> enabled)) {
      continue;
    }

    // Call the effect's render() method, which stores the rendered led data in an instance var
    effects[i] -> render();

		// Copy the led data ovber to the global array (additively)
		for (uint8_t j=0; j<NUM_LEDS-1; j++) {
			ledData[j] += (effects[i] -> leddata)[j];
		}

		/*
    // Copy the led data over to the global array (additively)
    for (uint8_t j=0; j<4; j++) {
      shrinkCopy(&(effects[i] -> leddata), &(face_one_mappings[j]));
      shrinkCopy(&(effects[i] -> leddata), &(face_two_mappings[j]));
      shrinkCopy(&(effects[i] -> leddata), &(face_three_mappings[j]));
      shrinkCopy(&(effects[i] -> leddata), &(face_four_mappings[j]));
    }
		*/
  }
}

// Handle input - just a single character.
// This could come from anywhere, but right now it's just Serial/keyboard.
void handleInput(char input) {
  Serial.println("--> Input Received");

  // Super basic right now - just enable the number specified.
  // If not 0-9, do nothing.
  // Note: 0-9 is represented by char codes 48 thru 57
  if (input < 48 || input > 57) {
    Serial.print("   Garbage input detected: ");
    Serial.println(input);
    return;
  }

  Serial.print("--> Valid input detected: ");
  Serial.println(input);

  Serial.print("--> Toggling effect ");
  Serial.println(input - 48);
  Serial.println(" ");

  effects[input - 48]->toggle();
}

// Print all current effects to console (and their status)
void displayEffectData() {
  Serial.println("--- Current Effects ---");

  for(uint8_t i=0; i<effects.Size(); i++){
    Serial.print("--> Effect ");
    Serial.print(i);
    Serial.print(": ");

    if (effects[i]->enabled) {
      Serial.print("enabled ");
    } else {
      Serial.print("disabled ");
    }

    Serial.println(" ");
  }

  Serial.println("-----------------------");
  Serial.println(" ");
}

void enableWifi() {
  // Enable Wifi (!)
  // Comment out the below if NOT using ESP32
  WiFi.mode(WIFI_STA);
  WiFi.begin("klobfi", "nootnoot");
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Wifi connection failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Give our wireless guy a friendly name
  ArduinoOTA.setHostname("firefly");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// 10ms = 200fps
void loop() {
  //ArduinoOTA.handle();

  EVERY_N_MILLIS(10) {
    FastLED.clear();
    renderActiveEffects();
    FastLED.show();
  }

  EVERY_N_MILLIS(5000) {
    displayEffectData();
  }

  if (Serial.available() > 0) {
    handleInput(Serial.read());
  }
}

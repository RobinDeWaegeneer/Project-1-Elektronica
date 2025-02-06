#include <FastLED.h>

#define NUM_LEDS 25

#define DATA_PIN 33

CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    
}

void loop() {
  for(int j=0; j<NUM_LEDS; j++){
    for(int i= 0; i<256; i++) {
      leds[j].setRGB(55,i,55);
      FastLED.show();
  }
}
  for(int j=25; j>=0; j--) {
    for(int i=255; i>=0; i--) {
      leds[j].setRGB(55, i, 55);
      FastLED.show();
    }
  }
  // Turn the LED on, then pause
  // leds[0] = CRGB::Blue;
  // FastLED.show();
  // delay(250);
  // // Now turn the LED off, then pause
  // leds[0] = CRGB::Red;
  // FastLED.show();
  // delay(250);
}

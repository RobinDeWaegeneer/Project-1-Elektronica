#include <FastLED.h>

#define NUM_LEDS 25  // Aantal LEDs in de strip

#define DATA_PIN 33  // Pin waarop de LED-strip is aangesloten

CRGB leds[NUM_LEDS]; // Array om de kleuren van de LEDs op te slaan

void setup() { 
    // Initialiseer de LED-strip met het WS2812B protocol en verbind deze aan de DATA_PIN
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // Laat de helderheid van de groene kleurcomponent van elke LED geleidelijk toenemen
  for(int j = 0; j < NUM_LEDS; j++) {
    for(int i = 0; i < 256; i++) {
      leds[j].setRGB(55, i, 55); // Zet de LED-kleur met een vaste rood en blauw waarde (55) en een variabele groen waarde (i)
      FastLED.show(); // Update de LED-strip om de wijzigingen weer te geven
    }
  }

  // Laat de helderheid van de groene kleurcomponent van elke LED geleidelijk afnemen
  for(int j = 25; j >= 0; j--) { // Loop achteruit door de LEDs
    for(int i = 255; i >= 0; i--) { 
      leds[j].setRGB(55, i, 55); // Verminder de groenwaarde geleidelijk
      FastLED.show(); // Update de LED-strip
    }
  }

  // Uitgecommentarieerde code voor het knipperen van een LED tussen blauw en rood:
  // leds[0] = CRGB::Blue;
  // FastLED.show();
  // delay(250);
  // leds[0] = CRGB::Red;
  // FastLED.show();
  // delay(250);
}

#include <FastLED.h>

#define WIDTH 5   // Aantal kolommen
#define HEIGHT 5  // Aantal rijen
#define NUM_LEDS (WIDTH * HEIGHT)  // Totaal aantal LEDs
#define DATA_PIN 33  // Pin waarop de LED-strip is aangesloten

CRGB leds[NUM_LEDS]; // Array om de LED-kleuren op te slaan

// Functie om een (rij, kolom) positie om te zetten naar een LED-index in de array
int getLedIndex(int row, int col) {
    // Serpentine routing: rijen wisselen van richting per rij
    if (row % 2 == 0) {
        return row * WIDTH + col; // Lijn loopt van links naar rechts
    } else {
        return row * WIDTH + (WIDTH - 1 - col); // Lijn loopt van rechts naar links
    }
}

void setup() { 
    // Initialiseer de LED-strip met WS2812B LEDs
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
    // Laat de helderheid van de groene kleurcomponent per LED toenemen
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            for (int i = 0; i < 256; i++) {
                leds[getLedIndex(row, col)].setRGB(55, i, 55);
                FastLED.show();
            }
        }
    }

    // Laat de helderheid van de groene kleurcomponent per LED afnemen
    for (int row = HEIGHT - 1; row >= 0; row--) {
        for (int col = WIDTH - 1; col >= 0; col--) {
            for (int i = 255; i >= 0; i--) {
                leds[getLedIndex(row, col)].setRGB(55, i, 55);
                FastLED.show();
            }
        }
    }
}

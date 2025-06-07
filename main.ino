// ------------------------Patroon 1---------------------
#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 25
#define NUM_STRIPS 5
#define TOTAL_LEDS (NUM_LEDS_PER_STRIP * NUM_STRIPS)
#define DATA_PIN_1 18
#define DATA_PIN_2 19
#define DATA_PIN_3 21
#define DATA_PIN_4 22
#define DATA_PIN_5 23

// Define arrays for each LED strip
CRGB leds1[NUM_LEDS_PER_STRIP];
CRGB leds2[NUM_LEDS_PER_STRIP];
CRGB leds3[NUM_LEDS_PER_STRIP];
CRGB leds4[NUM_LEDS_PER_STRIP];
CRGB leds5[NUM_LEDS_PER_STRIP];

// Helper function to set LED color by global index
void setLED(int index, CRGB color) {
    if (index < 0 || index >= TOTAL_LEDS) return;
    int strip = index / NUM_LEDS_PER_STRIP;
    int led = index % NUM_LEDS_PER_STRIP;
    switch (strip) {
        case 0: leds1[led] = color; break;
        case 1: leds2[led] = color; break;
        case 2: leds3[led] = color; break;
        case 3: leds4[led] = color; break;
        case 4: leds5[led] = color; break;
    }
}

void setup() { 
    // Initialize each LED strip
    FastLED.addLeds<WS2812B, DATA_PIN_1, RGB>(leds1, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_2, RGB>(leds2, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_3, RGB>(leds3, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_4, RGB>(leds4, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, DATA_PIN_5, RGB>(leds5, NUM_LEDS_PER_STRIP);
    
    // Clear all LEDs
    FastLED.clear();
    FastLED.show();
}

void loop() {
    // Clear LEDs for fresh frame
    FastLED.clear();
    
    // Static variable to track wave position
    static uint8_t wavePos = 0;
    
    // Create diagonal sparkle wave
    for (int i = 0; i < TOTAL_LEDS; i++) {
        int row = i % NUM_LEDS_PER_STRIP;
        int strip = i / NUM_LEDS_PER_STRIP;
        
        // Calculate diagonal position (row + strip) for wave effect
        int diagPos = (row + strip + wavePos) % 30;
        
        // Add sparkles based on wave position
        if (diagPos < 10 && random8(100) < 30) { // 30% chance for sparkle in active wave
            // Color gradient from blue to purple based on strip
            uint8_t hue = map(strip, 0, NUM_STRIPS - 1, 160, 200); // Blue to purple
            uint8_t brightness = random8(150, 255); // Random brightness for sparkle
            setLED(i, CHSV(hue, 200, brightness));
        }
    }
    
    // Fade all LEDs slightly to create trailing effect
    for (int i = 0; i < TOTAL_LEDS; i++) {
        int strip = i / NUM_LEDS_PER_STRIP;
        int led = i % NUM_LEDS_PER_STRIP;
        switch (strip) {
            case 0: leds1[led].fadeToBlackBy(50); break;
            case 1: leds2[led].fadeToBlackBy(50); break;
            case 2: leds3[led].fadeToBlackBy(50); break;
            case 3: leds4[led].fadeToBlackBy(50); break;
            case 4: leds5[led].fadeToBlackBy(50); break;
        }
    }
    
    FastLED.show();
    delay(50); // Frame rate for smooth animation
    
    // Increment wave position
    wavePos = (wavePos + 1) % 30;
    
    // Occasional full reset for variety
    if (random8(200) == 0) { // 0.5% chance per frame
        FastLED.clear();
        FastLED.show();
        delay(100);
    }
}

// ----------------PATROON 2---------------

// void loop() {
//     // Wave effect across all strips
//     for (int center = 0; center < TOTAL_LEDS; center++) {
//         // Clear all LEDs
//         FastLED.clear();
        
//         // Define wave width (e.g., 10 LEDs wide)
//         int waveWidth = 5;
//         for (int i = -waveWidth; i <= waveWidth; i++) {
//             int ledIndex = center + i;
//             if (ledIndex >= 0 && ledIndex < TOTAL_LEDS) {
//                 // Calculate fade based on distance from center
//                 uint8_t fade = map(abs(i), 0, waveWidth, 255, 0);
//                 CRGB color = CRGB(fade, 0, 255 - fade); // Red to blue transition
//                 setLED(ledIndex, color);
//             }
//         }
        
//         FastLED.show();
//         delay(50); // Delay for smooth wave movement
//     }

//     delay(500); // Pause between cycles

//     // Fade-out effect for all strips
//     for (int i = 255; i >= 0; i -= 5) {
//         for (int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//             leds1[j] = leds1[j].fadeToBlackBy(10);
//             leds2[j] = leds2[j].fadeToBlackBy(10);
//             leds3[j] = leds3[j].fadeToBlackBy(10);
//             leds4[j] = leds4[j].fadeToBlackBy(10);
//             leds5[j] = leds5[j].fadeToBlackBy(10);
//         }
//         FastLED.show();
//         delay(30);
//     }
// }

#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>

#define WIDTH 5   
#define HEIGHT 5  
#define NUM_LEDS (WIDTH * HEIGHT)
#define DATA_PIN 33  

CRGB leds[NUM_LEDS];

// WiFi-instellingen
const char* ssid = "JOUW_WIFI_NAAM";
const char* password = "JOUW_WIFI_WACHTWOORD";

WebServer server(80);  // Maak een webserver op poort 80

// Converteer rij, kolom naar LED-index
int getLedIndex(int row, int col) {
    if (row % 2 == 0) {
        return row * WIDTH + col;
    } else {
        return row * WIDTH + (WIDTH - 1 - col);
    }
}

// **Patroon 1: Fade-in fade-out effect**
void pattern1() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            for (int i = 0; i < 256; i++) {
                leds[getLedIndex(row, col)].setRGB(55, i, 55);
                FastLED.show();
                delay(5);
            }
        }
    }
}

// **Patroon 2: Willekeurige kleuren**
void pattern2() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(random(255), random(255), random(255));
    }
    FastLED.show();
}

// **Webserver: Ontvang commando's**
void handlePattern() {
    if (server.hasArg("mode")) {
        int mode = server.arg("mode").toInt();
        
        if (mode == 1) {
            pattern1();
            server.send(200, "text/plain", "Pattern 1 gestart!");
        } else if (mode == 2) {
            pattern2();
            server.send(200, "text/plain", "Pattern 2 gestart!");
        } else {
            server.send(400, "text/plain", "Ongeldig patroon.");
        }
    } else {
        server.send(400, "text/plain", "Geen mode opgegeven.");
    }
}

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

    WiFi.begin(ssid, password);
    Serial.print("Verbinden met WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nVerbonden!");
    Serial.print("IP-adres: ");
    Serial.println(WiFi.localIP());

    server.on("/pattern", handlePattern);  // Koppel de functie aan het pad "/pattern"
    server.begin();
}

void loop() {
    server.handleClient();
}

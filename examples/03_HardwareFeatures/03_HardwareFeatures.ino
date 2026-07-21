// Example: 03_HardwareFeatures for I2Connect: Digit Display
// Last Update: July 20, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Exercises the internal HT16K33A hardware to natively control 16-step 
// pulse width modulation dimming and integrated oscillator blink rates.
//
// SKILLS LEARNED
// setBrightness()
// blinkRate()
//
// DESCRIPTION
// The I2Connect: Digit Display is a compact 8-digit (dual 4-digit) 7-segment 
// display module based on the HT16K33A LED controller. It provides a simple and 
// reliable way to add numerical readouts and user interfaces to embedded systems.
// The module communicates over the standard I2C interface with a default address 
// of 0x70. If multiple Digit Display modules are required in the same system, an I2C 
// multiplexer must be used.
// Like all I2Connect modules, it features dual Qwiic compatible connectors for 
// easy daisy-chaining and an angled male header for breadboard use. It is 
// fully compatible with both 3.3V and 5V microcontroller systems.

#include <Wire.h>
#include <PTSolns_I2Connect_DigitDisplay.h>

// User Settings
const uint32_t SERIAL_BAUD  = 115200; // Serial baud setting
const uint32_t I2C_CLOCK_HZ = 100000; // I2C clock speed. Keep at 100 kHz most of the time.
const uint8_t  I2C_ADDRESS  = 0x70;   // Default address for the HT16K33A Digit Display

PTSolns_I2Connect_DigitDisplay display;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) { }

    Wire.begin();
    Wire.setClock(I2C_CLOCK_HZ);
    
    if (!display.begin(I2C_ADDRESS, Wire)) {
        Serial.println("Digit Display not detected. Please check your wiring!");
        while (1) { } // Halt execution
    }
    
    Serial.println("Digit Display detected and initialized.");
    Serial.println("-------------------------------------");
}

void loop() {
    // Fill the screen with '8's to make hardware effects visible
    display.print8(88888888); 
    display.writeDisplay();

    // --- DIMMING TEST ---
    Serial.println("Fading brightness DOWN...");
    for (int8_t b = 15; b >= 0; b--) {
        display.setBrightness(b);
        delay(200);
    }
    
    Serial.println("Fading brightness UP...");
    for (uint8_t b = 0; b <= 15; b++) {
        display.setBrightness(b);
        delay(200);
    }
    delay(2000);

    // --- BLINKING TEST ---
    Serial.println("Hardware Blink: Fast (2Hz)");
    display.blinkRate(1); 
    delay(4000);

    Serial.println("Hardware Blink: Medium (1Hz)");
    display.blinkRate(2); 
    delay(4000);

    Serial.println("Hardware Blink: Slow (0.5Hz)");
    display.blinkRate(3); 
    delay(4000);

    Serial.println("Hardware Blink: OFF (Solid)");
    display.blinkRate(0); 
    delay(4000);
}

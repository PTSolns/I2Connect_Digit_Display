// Example: 04_MarqueeAnimation for I2Connect: Digit Display
// Last Update: July 20, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Demonstrates how to use raw hexadecimal bitmasks to create custom characters 
// and slide an 8-character window across a larger array to create a scrolling marquee.
//
// SKILLS LEARNED
// writeDigitRaw()
// Array Manipulation
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

// The text "PTSOLNS" constructed using raw 7-segment bitmasks.
// P = 0x73, t = 0x78, S = 0x6D, O = 0x3F, L = 0x38, n = 0x54, S = 0x6D
// The array is padded with 8 blanks on both sides so it scrolls completely on and off screen.
const uint8_t marqueeText[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x73, 0x78, 0x6D, 0x3F, 0x38, 0x54, 0x6D, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const int marqueeLength = sizeof(marqueeText) / sizeof(marqueeText[0]);

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) { }

    Wire.begin();
    Wire.setClock(I2C_CLOCK_HZ);
    
    if (!display.begin(I2C_ADDRESS, Wire)) {
        Serial.println("Digit Display not detected. Please check your wiring!");
        while (1) { } // Halt execution
    }
    
    display.setBrightness(15);
    Serial.println("Digit Display detected. Beginning Marquee Animation...");
    Serial.println("-------------------------------------");
}

void loop() {
    // Slide an 8-digit window across the padded array
    for (int offset = 0; offset <= marqueeLength - 8; offset++) {
        
        // Grab 8 characters and write them to the local buffer
        for (int i = 0; i < 8; i++) {
            display.writeDigitRaw(i, marqueeText[offset + i]);
        }
        
        // Push the updated buffer to the display
        display.writeDisplay();
        
        // Adjust this delay to change the scroll speed
        delay(250); 
    }

    delay(1000); // Pause before repeating
}

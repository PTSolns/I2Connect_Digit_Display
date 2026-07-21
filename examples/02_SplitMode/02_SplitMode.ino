// Example: 02_SplitMode for I2Connect: Digit Display
// Last Update: July 20, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Demonstrates how to treat the physical display as two independent 
// 4-digit blocks, allowing you to update the left or right side separately.
//
// SKILLS LEARNED
// printLeft()
// printRight()
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
#include <PTSolns_I2Connect_Digit_Display.h>

// User Settings
const uint32_t SERIAL_BAUD  = 115200; // Serial baud setting
const uint32_t I2C_CLOCK_HZ = 100000; // I2C clock speed. Keep at 100 kHz most of the time.
const uint8_t  I2C_ADDRESS  = 0x70;   // Default address for the HT16K33A Digit Display

PTSolns_I2Connect_Digit_Display display;

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
    display.clear();

    // 1. Standard Right-Justified independent blocks
    Serial.println("Left block: 4444 | Right block: 88");
    display.printLeft(4444);
    display.printRight(88);
    display.writeDisplay();
    delay(3000);

    // 2. Left-Justified independent blocks
    Serial.println("Left block: 7 (Left) | Right block: 9 (Left)");
    display.printLeft(7, true);
    display.printRight(9, true);
    display.writeDisplay();
    delay(3000);
    
    // 3. Mixed formatting
    Serial.println("Left block: -25 (Right) | Right block: 100 (Left)");
    display.printLeft(-25);
    display.printRight(100, true);
    display.writeDisplay();
    delay(4000); 
}

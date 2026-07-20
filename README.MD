# PTSolns *I2Connect: Digit Display* Library

![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Display](https://img.shields.io/badge/Display-7__Segment-orange)

Library for the PTSolns *I2Connect: Digit Display* module. Available through both the Arduino Library Manager and the PTSolns IDE Library Manager, this library provides simple and advanced access to the dual 4-digit displays, while automatically managing I2C communication and hardware multiplexing.

---

## Overview

The *I2Connect: Digit Display* is a compact, high-visibility 8-digit (dual 4-digit) 7-segment display module driven by the HT16K33A LED controller[cite: 1]. Designed as part of the I2Connect Series, the module provides a simple and reliable way to add numerical readouts, timers, and UI elements to embedded systems. 

The display communicates over the industry standard I2C interface, offloading all LED multiplexing, blinking, and dimming tasks to the integrated hardware driver to ensure zero software overhead[cite: 1]. The module is compatible with both 3.3V and 5V systems, making it suitable for use with a wide range of popular microcontroller platforms. 

Like all I2Connect modules, it connects using dual Qwiic® compatible connectors to easily integrate into existing I2C systems without soldering, while the preinstalled right-angle header provides direct access to the I2C bus for breadboard-based prototyping.

---

## *I2Connect* Series

The PTSolns *I2Connect* Series is a family of plug and play expansion modules designed to simplify the integration of sensors, displays, user interfaces, and other peripherals into embedded systems. Built around the industry standard I2C communication protocol and featuring convenient Qwiic® compatible connectors (4 pin, 1 mm JST SH), *I2Connect* modules can be quickly connected without soldering or complex wiring.

Each module is fully assembled and includes a preinstalled male header that is compatible with standard solderless breadboards, enabling immediate use and rapid prototyping. Designed to work seamlessly with a wide range of microcontroller platforms, I2Connect modules combine compact hardware, comprehensive documentation, and easy to use software libraries. The _I2Connect_ Series enables makers, students, educators, and professionals to rapidly prototype, evaluate, and develop reliable electronic systems.

The following modules are part of the *I2Connect* Series:

* [**AHT20**](https://ptsolns.com/products/i2connect-aht20) — Temperature & Humidity
* [**VEML7700**](https://ptsolns.com/products/i2connect-veml7700) — Light & Lux
* [**EEPROM**](https://ptsolns.com/products/i2connect-eeprom) — 2 Mbit Memory
* **Buttons** — User Input via 4×4 Matrix of Buttons
* **Digit Display** — Dual 7 Segment Display
* **ICP-20100** — Pressure & Temperature
* **KXTJ3-1057** — 3 Axis Accelerometer
* **MUX** — 4 Channel I2C Multiplexer
* **OLED** — 0.96" 128×64 OLED Display
* **I2C Doctor** — I2C Bus Recovery and Diagnostics
* **...and more!**

---

## Key Features

* Dual 4-digit 7-segment displays (8 digits total).
* Native hardware multiplexing via HT16K33A[cite: 1].
* Default I2C address of 0x70.
* 3.3V and 5V logic and power compatibility.
* 16-step hardware digital dimming via pulse width modulation[cite: 1].
* Integrated hardware blink rates (0.5Hz, 1Hz, 2Hz)[cite: 1].
* Unified 8-digit or split independent 4-digit formatting control.
* Dual Qwiic® compatible 4-pin JST SH connectors for daisy-chaining.
* Breadboard-friendly 4-pin 2.54mm angled male header.

---

## I2Connect Ecosystem

The *I2Connect: Digit Display* is part of the PTSolns I2Connect ecosystem.

All *I2Connect* modules utilize a standardized 4 pin JST SH 1.0 mm connector carrying:

| Pin | Function |
| --- | -------- |
| 1   | GND      |
| 2   | VCC      |
| 3   | SDA      |
| 4   | SCL      |

This connector follows the widely adopted Qwiic® standard, allowing modules and compatible boards to be connected without soldering.

For maximum compatibility, the module also includes a preinstalled angled male header, allowing use with virtually any 3.3 V or 5 V microcontroller platform even when a Qwiic compatible connector is unavailable.

---

## Digit Display Specifications

| Parameter               | Value                               |
| ----------------------- | ----------------------------------- |
| Display Type            | 2x 4-Digit 7-Segment (8 Digits)     |
| Interface               | I2C                                 |
| I2C Address             | 0x70 (Default)                      |
| Operating Voltage       | 3.3 V / 5 V Rated                   |
| Connectors              | 2x 4-pin 1mm JST SH                 |

---

## I2C Addressing & Multiplexing

The *I2Connect: Digit Display* module uses a default I2C address of:

```text
0x70
```
If multiple Digit Display modules are required in the same system, an I2C multiplexer can be used. The PTSolns I2Connect: MUX module provides four independent I2C channels, allowing up to four identical displays to be connected to a single microcontroller bus.

---

## *PTSolns IDE*

The [*PTSolns IDE*](https://ptsolns.com/ide) is a free desktop application for programming PTSolns microcontroller development boards and compatible Arduino platforms.

This library is available directly through both the PTSolns IDE Library Manager and the Arduino Library Manager.

To install:

1. Open the PTSolns IDE (or Arduino IDE).
2. Open the Library Manager.
3. Search for:

```text
I2Connect_DigitDisplay
```

4. Click Install.

Features of the [*PTSolns IDE*](https://ptsolns.com/ide) include:

* Integrated board management
* Built in serial monitor
* Library management
* Example project browser
* Support for over 8,500 third party libraries
* Built in CH340 USB driver support
* Open source and community driven

The [*PTSolns IDE*](https://ptsolns.com/ide) can be used alongside the Arduino IDE and supports many PTSolns development boards out of the box.

---

## Quick Start

```cpp
#include <Wire.h>
#include <PTSolns_I2Connect_DigitDisplay.h>

PTSolns_I2Connect_DigitDisplay display;

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    if (display.begin(0x70, Wire)) {
        Serial.println("Digit Display initialized!");
    } else {
        Serial.println("Failed to find Digit Display.");
        while(1);
    }
}

void loop()
{
    // Print a number across all 8 digits and push to hardware
    display.print8(12345678);
    display.writeDisplay();
    delay(2000);
    
    // Clear the screen and print to independent sides
    display.clear();
    display.printLeft(100);
    display.printRight(99);
    display.writeDisplay();
    delay(2000);
}
```
---

## Library Functions

| Function          | Description                                   |
| ----------------- | ----------------------------------------------|
| begin()           | Initialize the display driver and I2C bus     |
| clear()           | Clear the local memory buffer                 |
| writeDisplay()    | Push the local buffer to the HT16K33A hardware|
| print8()          | Print an integer across all 8 digits          |
|printLeft()        | Print an integer to the left 4-digit block    |
| printRight()      | Print an integer to the right 4-digit block   |
|setBrightness()    |Set 16-step hardware dimming (0 to 15)         |
|blinkRate()        |Set hardware blink rate (0=off, 1, 2, or 3)    |
|writeDigitRaw()    |Write raw hexadecimal bitmasks to digits       |


---

## Basic Functions

## Initialization

```cpp
// Initializes display at default address 0x70
display.begin();
```
---
Printing Justified Data
```cpp
// Print the number 42 pushed to the far left of the display
display.print8(42, true);
display.writeDisplay();

// Print the number 42 pushed to the far right of the display
display.print8(42, false);
display.writeDisplay();
```
---
Hardware Dimming
```cpp
// Set the display brightness to maximum (15)
display.setBrightness(15);

// Set the display brightness to minimum visibility (0)
display.setBrightness(0);
```
---


/*
 * PTSolns I2Connect Digit Display Library
 * Target: PTSolns 2x 4-Digit Display (I2Connect Series)
 * Driver: HT16K33A
 */

#ifndef PTSOLNS_I2CONNECT_Digit_Display_H
#define PTSOLNS_I2CONNECT_Digit_Display_H

#include <Arduino.h>
#include <Wire.h>

// HT16K33 I2C Commands
#define HT16K33_BLINK_CMD       0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_CMD_BRIGHTNESS  0xE0
#define HT16K33_OSCILATOR_ON    0x21

class PTSolns_I2Connect_Digit_Display {
  public:
    PTSolns_I2Connect_Digit_Display();

    bool begin(uint8_t address = 0x70, TwoWire &wirePort = Wire);
    void clear();
    void writeDisplay();
    
    void setBrightness(uint8_t b);
    void blinkRate(uint8_t b);

    void print8(int32_t number, bool leftJustify = false);
    void printLeft(int16_t number, bool leftJustify = false);
    void printRight(int16_t number, bool leftJustify = false);

    void writeDigitRaw(uint8_t digit, uint8_t bitmask);

  private:
    uint8_t _i2c_addr;
    TwoWire *_wire;
    uint16_t displayBuffer[8]; 

    void initHT16K33();
    uint8_t encodeDigit(uint8_t digit);
};

#endif
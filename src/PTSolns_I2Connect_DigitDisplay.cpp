#include "PTSolns_I2Connect_DigitDisplay.h"

static const uint8_t numberFont[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40, 0x00
};

PTSolns_I2Connect_DigitDisplay::PTSolns_I2Connect_DigitDisplay() {
  _i2c_addr = 0x70; 
}

bool PTSolns_I2Connect_DigitDisplay::begin(uint8_t address, TwoWire &wirePort) {
  _i2c_addr = address;
  _wire = &wirePort;
  
  _wire->begin();
  
  _wire->beginTransmission(_i2c_addr);
  if (_wire->endTransmission() != 0) {
    return false;
  }
  
  initHT16K33();
  return true;
}

void PTSolns_I2Connect_DigitDisplay::initHT16K33() {
  _wire->beginTransmission(_i2c_addr);
  _wire->write(HT16K33_OSCILATOR_ON);
  _wire->endTransmission();
  
  blinkRate(0); 
  setBrightness(15); 
  clear();
  writeDisplay();
}

void PTSolns_I2Connect_DigitDisplay::setBrightness(uint8_t b) {
  if (b > 15) b = 15;
  _wire->beginTransmission(_i2c_addr);
  _wire->write(HT16K33_CMD_BRIGHTNESS | b);
  _wire->endTransmission();
}

void PTSolns_I2Connect_DigitDisplay::blinkRate(uint8_t b) {
  if (b > 3) b = 0; 
  _wire->beginTransmission(_i2c_addr);
  _wire->write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
  _wire->endTransmission();
}

void PTSolns_I2Connect_DigitDisplay::writeDigitRaw(uint8_t digit, uint8_t bitmask) {
  if (digit > 7) return;
  displayBuffer[digit] = bitmask;
}

void PTSolns_I2Connect_DigitDisplay::clear() {
  for (uint8_t i = 0; i < 8; i++) {
    displayBuffer[i] = 0;
  }
}

void PTSolns_I2Connect_DigitDisplay::writeDisplay() {
  _wire->beginTransmission(_i2c_addr);
  _wire->write((uint8_t)0x00); 
  
  // HARDWARE MAPPING FIX:
  // Maps logical layout (0-7) to the physical PCB trace layout.
  // COM0-3 = Logical Right (4,5,6,7), COM4-7 = Logical Left (0,1,2,3)
  uint8_t hwToLogical[8] = {4, 5, 6, 7, 0, 1, 2, 3};
  
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t l_idx = hwToLogical[i];
    _wire->write(displayBuffer[l_idx] & 0xFF);    
    _wire->write(displayBuffer[l_idx] >> 8); 
  }
  _wire->endTransmission();
}

uint8_t PTSolns_I2Connect_DigitDisplay::encodeDigit(uint8_t digit) {
  if (digit > 9) return 0x00; 
  return numberFont[digit];
}

void PTSolns_I2Connect_DigitDisplay::printLeft(int16_t number, bool leftJustify) {
  for(int i = 0; i < 4; i++) displayBuffer[i] = 0;
  
  String numStr = String(number);
  if(numStr.length() > 4) numStr = "-Er-"; 
  
  int startIdx = leftJustify ? 0 : (4 - numStr.length());
  
  for(size_t i = 0; i < numStr.length(); i++) {
    char c = numStr[i];
    uint8_t code = 0;
    if (c >= '0' && c <= '9') code = encodeDigit(c - '0');
    else if (c == '-') code = numberFont[10];
    
    writeDigitRaw(startIdx + i, code);
  }
}

void PTSolns_I2Connect_DigitDisplay::printRight(int16_t number, bool leftJustify) {
  for(int i = 4; i < 8; i++) displayBuffer[i] = 0;
  
  String numStr = String(number);
  if(numStr.length() > 4) numStr = "-Er-"; 
  
  int startIdx = leftJustify ? 4 : (8 - numStr.length());
  
  for(size_t i = 0; i < numStr.length(); i++) {
    char c = numStr[i];
    uint8_t code = 0;
    if (c >= '0' && c <= '9') code = encodeDigit(c - '0');
    else if (c == '-') code = numberFont[10];
    
    writeDigitRaw(startIdx + i, code);
  }
}

void PTSolns_I2Connect_DigitDisplay::print8(int32_t number, bool leftJustify) {
  clear();
  String numStr = String(number);
  if(numStr.length() > 8) {
    printLeft(9999); 
    printRight(9999);
    return;
  }
  
  int startIdx = leftJustify ? 0 : (8 - numStr.length());
  
  for(size_t i = 0; i < numStr.length(); i++) {
    char c = numStr[i];
    uint8_t code = 0;
    if (c >= '0' && c <= '9') code = encodeDigit(c - '0');
    else if (c == '-') code = numberFont[10];
    
    writeDigitRaw(startIdx + i, code);
  }
}
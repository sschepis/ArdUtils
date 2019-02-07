#include "TerminalLogger.h"

#include <U8g2lib.h>
#include <Wire.h>

#define U8LOG_WIDTH 32
#define U8LOG_HEIGHT 10
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
U8G2LOG u8g2log;

TerminalLogger* TerminalLogger::getInstance() {
  if(!instance) instance = new TerminalLogger;
  return instance;
}

TerminalLogger* TerminalLogger::instance = nullptr;

TerminalLogger::TerminalLogger() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);  // set the font for the terminal window
  u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8g2log.setLineHeightOffset(0); // set extra space between lines in pixel, this can be negative
  u8g2log.setRedrawMode(0);   // 0: Update screen with newline, 1: Update screen for every char    
}

TerminalLogger::~TerminalLogger() {
}

void TerminalLogger::log(String output, bool newline) {
  if(newline) {
    u8g2log.println(output);
    Serial.println(output);
  }
  else {
    u8g2log.print(output);
    Serial.print(output);
  }
}

void TerminalLogger::log(int output, bool newline) {
  if(newline) {
    u8g2log.println(output);
    Serial.println(output);
  }
  else {
    u8g2log.print(output);
    Serial.print(output);
  }
}

void TerminalLogger::log(char *output, bool newline) {
  if(newline) {
    u8g2log.println(output);
    Serial.println(output);
  }
  else {
    u8g2log.print(output);
    Serial.print(output);
  }
}

void TerminalLogger::log(char output, bool newline) {
  if(newline) {
    u8g2log.println(output);
    Serial.println(output);
  }
  else {
    u8g2log.print(output);
    Serial.print(output);
  }  
}

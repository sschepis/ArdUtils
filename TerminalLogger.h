#ifndef TERMINAL__LOGGER_H
#define TERMINAL__LOGGER_H

#include <Arduino.h>
#include <string.h>
#include <Wire.h>

#include "SSD1306Wire.h"

#ifdef __GNUC__
#  define TLOG_NOINLINE __attribute__((noinline))
#  define TLOG_SECTION(name) __attribute__ ((section (name)))
#  define TLOG_UNUSED __attribute__((unused))
#else
#  define TLOG_SECTION(name)
#  define TLOG_NOINLINE
#  define TLOG_UNUSED
#endif

//class SSD1306Log;

class TerminalLogger {
  public:
    static TerminalLogger* getInstance(SSD1306Wire *d);

    void log(String output, bool newline = true);
    void log(int output, bool newline = true);
    void log(char *output, bool newline = true);
    void log(char output, bool newline = true);

    void debug(String output, bool newline = true);
    
    void clear();
    
    void setDebugMode(bool v) { debugMode = v; }
    bool getDebugMode() { return debugMode; }

  private:
    TerminalLogger(SSD1306Wire *d);
    ~TerminalLogger();
    
    bool debugMode;
    void addLine(const char *line);
    void draw();
    
    static TerminalLogger* instance;

    SSD1306Wire *ssd1306display;
//    SSD1306Log *ssd1306log;
};

//class SSD1306Log : public Print {
//  public:
//    SSD1306Wire *display;
//    uint8_t *buffer;
//  
//    /* the constructor does nothing, use begin() instead */
//    SSD1306Log(void) {
//      display = NULL;
//      buffer = NULL;
//    }
//  
//    /* connect to u8g2, draw to u8g2 whenever required */
//    bool begin(SSD1306Wire *d, uint8_t width, uint8_t height, uint8_t *buf)  {
//      display = d;
//      buffer = buf;
//      return true;
//    }
//    
//    void setLineHeightOffset(int8_t lho) {
//      line_height_offset = lho;
//    }
//
//    void setRedrawMode(uint8_t rm) {
//      redraw_mode = rm; 
//    }
//    
//    /* virtual function for print base class */    
//    size_t write(uint8_t v) {
//      return 1;
//    }
//
//    size_t write(const uint8_t *buffer, size_t size) {
//      size_t cnt = 0;
//      while( size > 0 ) {
//        cnt += write(*buffer++); 
//        size--;
//      }
//      return cnt;
//    }  
//    
//  private:
//    int8_t line_height_offset;
//    uint8_t redraw_mode;
//
//};

#endif // TERMINAL__LOGGER_H

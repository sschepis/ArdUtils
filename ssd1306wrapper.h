#pragma once

#include <stdint.h>
#include <string.h>

#include <SSD1306Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum DISPLAY_TYPE {
  ESP_SSD1306WIRE = 0,
  ADA_SSD1306     = 1
};

enum DISPLAY_GEOMETRY {
  __GEOMETRY_128_64   = 0,
  __GEOMETRY_128_32   = 1,
  __GEOMETRY_64_32    = 2
};

enum DISPLAY_COLOR {
  __BLACK   = 0,
  __WHITE   = 1,
  __INVERSE = 2
};

enum DISPLAY_TEXT_ALIGNMENT {
  __TEXT_ALIGN_LEFT        = 0,
  __TEXT_ALIGN_RIGHT       = 1,
  __TEXT_ALIGN_CENTER      = 2,
  __TEXT_ALIGN_CENTER_BOTH = 3
};

typedef byte (*FTLookupFunction)(const byte ch);
typedef void *DisplayObject; 

class SSD1306Wrapper {

  public:
    SSD1306Wrapper(
        DISPLAY_TYPE d_type, 
        uint8_t _address, 
        uint8_t _sda, 
        uint8_t _scl, 
        uint8_t _rst, 
        uint32_t freq = 100000, 
        DISPLAY_GEOMETRY g = __GEOMETRY_128_64);

    ~SSD1306Wrapper(void) {
        if(esp_display_ == NULL) {
            delete esp_display_;
        }
        else if(ada_display_ == NULL) {
            delete ada_display_;
        }
    }

    uint16_t width(void) const;
    uint16_t height(void) const;
    bool init(void);
    void end(void);
    void sleep(void);
    void wakeup(void);
    void resetDisplay(void);
    void setColor(DISPLAY_COLOR color);
    DISPLAY_COLOR getColor(void);
    void setPixel(int16_t x, int16_t y);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void drawRect(int16_t x, int16_t y, int16_t width, int16_t height);
    void fillRect(int16_t x, int16_t y, int16_t width, int16_t height);
    void drawCircle(int16_t x, int16_t y, int16_t radius);
    void drawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads);
    void fillCircle(int16_t x, int16_t y, int16_t radius);
    void drawHorizontalLine(int16_t x, int16_t y, int16_t length);
    void drawVerticalLine(int16_t x, int16_t y, int16_t length);
    void drawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress);
    void drawFastImage(int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t *image);
    void drawXbm(int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t *xbm);
    void drawString(int16_t x, int16_t y, String text);
    void drawStringMaxWidth(int16_t x, int16_t y, uint16_t maxLineWidth, String text);
    uint16_t getStringWidth(const char* text, uint16_t length);
    uint16_t getStringWidth(String text);
    void setTextAlignment(DISPLAY_TEXT_ALIGNMENT textAlignment);
    void setFont(const uint8_t *fontData);
    void setFontTableLookupFunction(FTLookupFunction function);
    void displayOn(void);
    void displayOff(void);
    void invertDisplay(void);
    void normalDisplay(void);
    void setContrast(uint8_t contrast, uint8_t precharge = 241, uint8_t comdetect = 64);
    void setBrightness(uint8_t b);
    void resetOrientation(void);
    void flipScreenVertically(void);
    void mirrorScreen(void);
    void clear(void);
    bool setLogBuffer(uint16_t lines, uint16_t chars);
    void drawLogBuffer(uint16_t x, uint16_t y);
    uint16_t getWidth(void);
    uint16_t getHeight(void);
    size_t write(uint8_t c);
    size_t write(const char* s);
    DisplayObject getDisplayObject(void);
  
  private:

    DISPLAY_TYPE _type;
    bool _initialized;
    SSD1306Wire *esp_display_;
    Adafruit_SSD1306 *ada_display_;

};
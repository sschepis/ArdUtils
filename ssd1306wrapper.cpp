#include "ssd1306wrapper.h"

#include <SPI.h>
#include <Wire.h>

SSD1306Wrapper::SSD1306Wrapper(
    DISPLAY_TYPE d_type, 
    uint8_t _address, 
    uint8_t _sda, 
    uint8_t _scl, 
    uint8_t _rst, 
    uint32_t freq, 
    DISPLAY_GEOMETRY g) {
    _type = d_type;
    _initialized = false;
    esp_display_ = NULL;
    ada_display_ = NULL;       
    _initialized = false;
    if(d_type == ESP_SSD1306WIRE) {
        esp_display_ = new SSD1306Wire(0x3c, 11, 12, -1, 100000);
        esp_display_->init();
        esp_display_->setI2cAutoInit(true);
        esp_display_->flipScreenVertically();
        esp_display_->setBrightness(255);
        esp_display_->clear();
        esp_display_->display();
    } 
    else if(d_type == ADA_SSD1306) {
        uint8_t width, height;
        if(g == __GEOMETRY_128_64) {
            width = 128;
            height = 64;
        } else if(g == __GEOMETRY_128_32) {
            width = 128;
            height = 32;
        } else if(g == __GEOMETRY_64_32) {
            width = 64;
            height = 32;
        }
        ada_display_ = new Adafruit_SSD1306(width, height, &Wire, -1);
        if(!ada_display_->begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
            return;
        }
        _initialized = true;
    }
}

uint16_t SSD1306Wrapper::width(void) const {
    if(_type == ESP_SSD1306WIRE) {
        return esp_display_->width();
    } else if(_type == ESP_SSD1306WIRE) {
        return ada_display_->width();
    }
}

uint16_t SSD1306Wrapper::height(void) const {
    if(_type == ESP_SSD1306WIRE) {
        return esp_display_->height();
    } else if(_type == ESP_SSD1306WIRE) {
        return ada_display_->height();
    }
}

bool SSD1306Wrapper::init() {
    if(_type == ESP_SSD1306WIRE) {
        return esp_display_->init();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->startWrite();
    }
}

void SSD1306Wrapper::end() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->end();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->endWrite();
    }
}

void SSD1306Wrapper::sleep() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->sleep();
    }
}

void SSD1306Wrapper::wakeup() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->wakeup();
    }
}

void SSD1306Wrapper::resetDisplay() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->resetDisplay();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->clearDisplay();
    }
}

// void SSD1306Wrapper::setColor(DISPLAY_COLOR color) {
//     if(_type == ESP_SSD1306WIRE) {
//         esp_display_->setColor(color);
//     } else if(_type == ESP_SSD1306WIRE) {
//         ada_display_->setColor(color);
//     }
// }

// DISPLAY_COLOR SSD1306Wrapper::getColor() {
//     if(_type == ESP_SSD1306WIRE) {
//         return esp_display_->getColor();
//     } else if(_type == ESP_SSD1306WIRE) {
//         return ada_display_->getColor();
//     }
// }

void SSD1306Wrapper::setPixel(int16_t x, int16_t y) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setPixel(x, y);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawPixel(x, y, WHITE);
    }
}

void SSD1306Wrapper::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawLine(x0, y0, x1, y1);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawLine(x0, y0, x1, y1, WHITE);
    }
}

void SSD1306Wrapper::drawRect(int16_t x, int16_t y, int16_t width, int16_t height) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawRect(x, y, width, height);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawRect(x, y, width, height, WHITE);
    }
}

void SSD1306Wrapper::fillRect(int16_t x, int16_t y, int16_t width, int16_t height) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->fillRect(x, y, width, height);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->fillRect(x, y, width, height, WHITE);
    }
}

void SSD1306Wrapper::drawCircle(int16_t x, int16_t y, int16_t radius) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawCircle(x, y, radius);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawCircle(x, y, radius, WHITE);
    }
}

void SSD1306Wrapper::drawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawCircleQuads(x0, y0, radius, quads);
    }
}

void SSD1306Wrapper::fillCircle(int16_t x, int16_t y, int16_t radius) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->fillCircle(x, y, radius);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->fillCircle(x, y, radius, WHITE);
    }
}

void SSD1306Wrapper::drawHorizontalLine(int16_t x, int16_t y, int16_t length) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawHorizontalLine(x, y, length);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawFastHLine(x, y, length, WHITE);
    }
}

void SSD1306Wrapper::drawVerticalLine(int16_t x, int16_t y, int16_t length) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawVerticalLine(x, y, length);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawFastVLine(x, y, length, WHITE);
    }
}

void SSD1306Wrapper::drawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawProgressBar(x, y, width, height, progress);
    }
}

void SSD1306Wrapper::drawFastImage(int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t *image) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawFastImage(x, y, width, height, image);
    }
}

void SSD1306Wrapper::drawXbm(int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t *xbm) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawXbm(x, y, width, height, xbm);
    }
}

void SSD1306Wrapper::drawString(int16_t x, int16_t y, String text) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawString(x, y, text);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawString(x, y, text);
    }
}

void SSD1306Wrapper::drawStringMaxWidth(int16_t x, int16_t y, uint16_t maxLineWidth, String text) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawStringMaxWidth(x, y, maxLineWidth, text);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->drawStringMaxWidth(x, y, maxLineWidth, text);
    }
}

uint16_t SSD1306Wrapper::getStringWidth(const char* text, uint16_t length) {
    if(_type == ESP_SSD1306WIRE) {
        return esp_display_->getStringWidth(text, length);
    } else if(_type == ESP_SSD1306WIRE) {
        return ada_display_->.getStringWidth(text, length);
    }
}

uint16_t SSD1306Wrapper::getStringWidth(String text) {
    if(_type == ESP_SSD1306WIRE) {
        return esp_display_->getStringWidth(text);
    } else if(_type == ESP_SSD1306WIRE) {
        return ada_display_->getStringWidth(text);
    }
}

void SSD1306Wrapper::setTextAlignment(DISPLAY_TEXT_ALIGNMENT textAlignment) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setTextAlignment(textAlignment);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->setTextAlignment(textAlignment);
    }
}

void SSD1306Wrapper::setFont(const uint8_t *fontData) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setFont(fontData);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->setFont(fontData);
    }
}

void SSD1306Wrapper::setFontTableLookupFunction(FTLookupFunction function) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setFontTableLookupFunction(function);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->setFontTableLookupFunction(function);
    }
}

void SSD1306Wrapper::displayOn(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->displayOn();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->displayOn();
    }
}

void SSD1306Wrapper::displayOff(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->displayOff();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->displayOff();
    }
}

void SSD1306Wrapper::invertDisplay(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->invertDisplay();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->invertDisplay();
    }
}

void SSD1306Wrapper::normalDisplay(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->normalDisplay();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->normalDisplay();
    }
}

void SSD1306Wrapper::setContrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setContrast(contrast, precharge, comdetect);
    }

void SSD1306Wrapper::setBrightness(uint8_t b) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setBrightness(b);
    }
}

void SSD1306Wrapper::resetOrientation() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->resetOrientation();
    }
}

void SSD1306Wrapper::flipScreenVertically() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->flipScreenVertically();
    }
}

void SSD1306Wrapper::mirrorScreen() {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->mirrorScreen();
    }
}

void SSD1306Wrapper::clear(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->clear();
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->clear();
    }
}

bool SSD1306Wrapper::setLogBuffer(uint16_t lines, uint16_t chars) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->setLogBuffer(lines, chars);
    }
}

void SSD1306Wrapper::drawLogBuffer(uint16_t x, uint16_t y) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->drawLogBuffer(x, y);
    }
}

uint16_t SSD1306Wrapper::getWidth(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->getWidth();
    } else if(_type == ESP_SSD1306WIRE) {
        if(__GEOMETRY_128_64 == _type || __GEOMETRY_128_32 == _type) return 128;
        else return 64;
    }
}

uint16_t SSD1306Wrapper::getHeight(void) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->getHeight();
    } else if(_type == ESP_SSD1306WIRE) {
        if(__GEOMETRY_128_64 == _type) return 64;
        if(__GEOMETRY_128_32 == _type || __GEOMETRY_64_32 == _type) return 32;
        else return 64;
    }
}

size_t SSD1306Wrapper::write(uint8_t c) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->write(c);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->write(c);
    }
}

size_t SSD1306Wrapper::write(const char* s) {
    if(_type == ESP_SSD1306WIRE) {
        esp_display_->write(s);
    } else if(_type == ESP_SSD1306WIRE) {
        ada_display_->write(s);
    }
}

DisplayObject SSD1306Wrapper::getDisplayObject(void) {
    if(_type == ESP_SSD1306WIRE) {
        return (DisplayObject) esp_display_;
    } else if(_type == ESP_SSD1306WIRE) {
        return (DisplayObject) ada_display_;
    }
}

#include "TerminalLogger.h"

#include "Vector.h"
#include <stdint.h>

#define BUFFER_WIDTH 32
#define BUFFER_HEIGHT 8

Vector<uint8_t*> terminalLog_buffer;

char buf[BUFFER_WIDTH + 1];

TerminalLogger* TerminalLogger::getInstance(SSD1306Wire *d) {
  if(!instance) instance = new TerminalLogger(d);
  return instance;
}

TerminalLogger* TerminalLogger::instance = nullptr;

TerminalLogger::TerminalLogger(SSD1306Wire *d) {
  ssd1306display = d;
  debugMode = false;
}

TerminalLogger::~TerminalLogger() {
}

void TerminalLogger::clear() {
  if(ssd1306display != NULL) {
    ssd1306display->clear();
    ssd1306display->display();    
  }
}

void TerminalLogger::addLine(const char *line) {
  if(terminalLog_buffer.size() >= BUFFER_HEIGHT) {
    uint8_t *tailLine = terminalLog_buffer.front();
    terminalLog_buffer.remove(0);
    free(tailLine);
  }
  terminalLog_buffer.push_back((uint8_t *)line);
}

void TerminalLogger::draw() {
  if(ssd1306display != NULL) {
    if(terminalLog_buffer.size() >= BUFFER_HEIGHT) {
      ssd1306display->clear();
      for(size_t idx = 0; idx < terminalLog_buffer.size(); idx++) {
        ssd1306display->drawString(0, idx * 8, (const char*)terminalLog_buffer[idx]);
      }
    } else ssd1306display->drawString(0, (terminalLog_buffer.size()-1) * 8, (const char*)terminalLog_buffer.back());
    ssd1306display->display();    
  }
}

void TerminalLogger::log(String output, bool newline) {
  snprintf(buf, BUFFER_WIDTH, "%s%s", output.c_str(), newline ? "\n" : "");  
  Serial.print(buf);
  if(ssd1306display != NULL) {
    char *newLine = (char *) malloc((sizeof(char) * strlen(buf)) + 1);
    strcpy(newLine, buf);
    addLine(newLine);
    draw();
  }
}

void TerminalLogger::debug(String output, bool newline) {
    if(debugMode)  log(output, newline);
    else {
        snprintf(buf, BUFFER_WIDTH, "%s%s", output.c_str(), newline ? "\n" : "");
        Serial.print(buf);
    }
}

void TerminalLogger::log(int output, bool newline) {
  snprintf(buf, BUFFER_WIDTH, "%d%s", output, newline ? "\n" : "");  
  Serial.print(buf);
  if(ssd1306display != NULL) {
    char *newLine = (char *) malloc((sizeof(char) * strlen(buf)) + 1);
    strcpy(newLine, buf);
    addLine(newLine);
    draw();
  }
}

void TerminalLogger::log(char *output, bool newline) {
  snprintf(buf, BUFFER_WIDTH, "%s%s", output, newline ? "\n" : "");  
  Serial.print(buf);
  if(ssd1306display != NULL) {
    char *newLine = (char *) malloc((sizeof(char) * strlen(buf)) + 1);
    strcpy(newLine, buf);
    addLine(newLine);
    draw();
  }
}

void TerminalLogger::log(char output, bool newline) {
  snprintf(buf, BUFFER_WIDTH, "%c%s", output, newline ? "\n" : "");  
  Serial.print(buf);
  if(ssd1306display != NULL) {
    char *newLine = (char *) malloc((sizeof(char) * strlen(buf)) + 1);
    strcpy(newLine, buf);
    draw();
  }
}

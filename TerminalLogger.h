#ifndef TERMINAL__LOGGER_H
#define TERMINAL__LOGGER_H

#include <Arduino.h>

class TerminalLogger {

  public:
    static TerminalLogger* getInstance();

    void log(String output, bool newline = true);
    void log(int output, bool newline = true);
    void log(char *output, bool newline = true);
    void log(char output, bool newline = true);

  private:
     TerminalLogger();
    ~TerminalLogger();
    
    static TerminalLogger* instance;
};

#endif // TERMINAL__LOGGER_H

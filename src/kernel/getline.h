// Tue Aug  1 23:21:00 UTC 2017
// 4735-b0c-01-

#include <Arduino.h>
#include "../../yaffa.h"

extern char getKey(void);
extern uint8_t getLine(char* ptr, uint8_t buffSize);

extern uint8_t flags;                 // Internal Flags

extern uint8_t spiFlashReading; // = -1; // TRUE  // Adafruit SPI flash: reading
extern uint8_t spiFlashWaiting; // visit ainsuforthsketch.cpp or similar-named file
extern uint8_t fileClosed; // visit ainsuforthsketch.cpp or similar-named file

extern void setup_spi_flash(void);

// Sun Jun  -- edit me
// 4735-a0g -- edit me

#include <Arduino.h>
#include "../../yaffa.h"
// #include "Error_Codes.h"

#include "load.h"
const char load_str[] = "load";
void _load(void) {

  spiFlashReading = TRUE ; // TRUE      // Adafruit SPI flash: reading

  if (spiFlashReading) {
    int fake = 0;
    //    Serial.println("\r\n SEEN spiFlash boolean on Line 13:\r\n");
  }
}

// #endif

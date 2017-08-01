// Sun Jun 18 15:04:16 UTC 2017
// 4735-a0m

#include <Arduino.h>
#include "../../yaffa.h"

extern char getKey(void);
extern uint8_t getLine(char* ptr, uint8_t buffSize);

extern uint8_t flags;                 // Internal Flags

extern char getKey(void);


//  spiFlashReading = -1; // TRUE
// ../../ainsuForthsketch.cpp:
// 105 uint8_t spiFlashReading;       // Adafruit SPI flash: reading
extern uint8_t spiFlashReading;       // Adafruit SPI flash: reading



// Sun Jun 18 15:04:16 UTC 2017
// 4735-a0m

// extern void xxsetup_spi_flash(void);
extern void setup_spi_flash(void);

extern void xxcreate_test_directory(void);

extern void xxwrite_a_test_file(void);

extern void xxread_a_test_file(void);

#ifndef HAS_STANDARD_BUILD_HERE
extern void xxread_from_code_py_file(void);
#endif

extern void xxtail_code_bb(void);

extern void xxspi_flash_main(void);


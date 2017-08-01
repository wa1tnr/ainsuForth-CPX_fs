// Tue Aug  1 23:21:00 UTC 2017
// 4735-b0c-01-

#include <Arduino.h>
#include "../../yaffa.h"
// #include "../../Error_Codes.h"

#ifdef EXT_KERN_GETLINE
#include "getline.h"

#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>

#define FLASH_TYPE     SPIFLASHTYPE_W25Q16BV  // Flash chip type.
#define FLASH_SS       SS                    // Flash chip SS pin.
#define FLASH_SPI_PORT SPI                   // What SPI port is Flash on?

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT);     // Use hardware SPI 

Adafruit_W25Q16BV_FatFs fatfs(flash);

void setup_spi_flash(void) {
  // Serial.println("SPI Flash - reading");
  if (!flash.begin(FLASH_TYPE)) {
    Serial.println("E: flash chip init fault.");
    while(1);
  }
  // Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.GetJEDECID(), HEX);

  if (!fatfs.begin()) {
    Serial.println("E: fatfs.begin() fault.");
    // Serial.println("Was the flash chip formatted with the fatfs_format example?");
    while(1);
  }
  // Serial.println("fatfs is mounted.");
}


/******************************************************************************/
/** getLine                                                                  **/
/**   read in a line of text ended by a Carriage Return (ASCII 13)           **/
/**   Valid characters are:  Backspace, Carriage Return, Escape, Tab, and    **/
/**   standard printable characters. Passed the address to store the string, **/
/**   and Returns the length of the string stored                            **/
/******************************************************************************/

File thisFile;

uint8_t getLine(char* ptr, uint8_t buffSize) {
  char inChar;
  uint8_t count = 0;

  // uint8_t fileClosed = TRUE ;

  // Serial.println("debug: is fileClosed TRUE or not?");

  // if (fileClosed) { Serial.println("Indeed, fileClosed is TRUE"); }

  if (spiFlashReading) {
      // Serial.println("\r\nSEEN: getline.cpp   line:  60  was 140\r\n");
      if (fatfs.exists("/forth/job.fs")) {
          if (fileClosed) {

            // Serial.println("(re)opening fatfs .. verify it is okay to do so.");

            File forthSrcFile = fatfs.open("/forth/job.fs", FILE_READ);
            thisFile = (File) forthSrcFile;
            fileClosed = FALSE ; // it is open, now.
          }
      }
  }




  do {
    if (spiFlashReading) {
        if (thisFile) {
            if (thisFile.available()) {
             // this is where every character of job.fs is read from SPI flash:
                inChar = thisFile.read();

                spiFlashWaiting = FALSE;
                if (thisFile.available()) {
                    spiFlashWaiting = TRUE;
                } else {
                    fileClosed = TRUE; // want to close the file - set a flag
                    spiFlashReading = FALSE; // shutdown the reading mechanism
                }
            }
        }

    } else {
        inChar = getKey(); 
    }

    // inChar is now populated; either by keypress or by byte stored in SPI flash.

    if (inChar == ASCII_BS || inChar == ASCII_DEL) {  // new: was only ASCII_BS
       if (count) {
         *--ptr = 0;
         count--; // ainsuForth improvement -- backspace behavior
        if (flags & ECHO_ON) Serial.print("\b \b");
      }
    }
    else if (inChar == ASCII_TAB || inChar == ASCII_ESC) {
      if (flags & ECHO_ON) Serial.print("\a");
    }
    else if (inChar == ASCII_CR || inChar == ASCII_NL) { // ainsuForth improvement

                          // iirc, this was for use during colon definition upload,
                          // using copy and paste into the serial terminal.

                          // Basis: lack of newline sensitivity; added some.

                          // Test: revert, attempt a multi-line code paste.  If
                          // it fails or behaves poorly, reenable this code.
                          // Compare the two behaviors.

                          // iirc, interactive typing to the interpreter masks
                          // this behavior, whereas a paste-in unmasks it.

      if (flags & ECHO_ON) Serial.print(" "); // seems to want a space after 'dot' for example.

      // debug // Serial.println("EVERYONE");
      // Serial.println("debug: is flash waiting or not?");
      if (spiFlashWaiting) {
          // Serial.println("Flash is WAITING .. more to read.");
      }


#ifdef NEVERDEFINEDNOTNOW
      if (spiFlashReading) {
          spiFlashReading = FALSE ; // tripwire

          // DISCUSSION: If this isn't here (spiFlashReading becomes FALSE)
          // the program in its present configuration continues to loop,
          // reading the same first line of source, over and over, and
          // recompiling it into the vm symbols S Wood devised ('compiles').
      }
#endif




      break;

    } else {
      if (flags & ECHO_ON) Serial.print(inChar);
      *ptr++ = inChar;
      *ptr = 0;
      count++;
    }
  } while (count < buffSize);
  return (count);
}

#endif


#ifdef EXT_KERN_GETKEY

/******************************************************************************/
/** getKey                                                                   **/
/**   waits for the next valid key to be entered and return its value        **/
/**   Valid characters are:  Backspace, Carriage Return (0x0d), Escape,      **/
/**   Tab, Newline (0x0a) and standard (printable) characters                **/
/******************************************************************************/
char getKey(void) {
    char inChar;
    // the load word provides this boolean:
    if (spiFlashReading) {
        if (inChar == ASCII_BS  ||
            inChar == ASCII_TAB ||
            inChar == ASCII_CR  ||  
            inChar == ASCII_NL  ||   // new
            inChar == ASCII_DEL ||   // new
            inChar == ASCII_ESC ||
            isprint(inChar)) {
            return inChar;
        }
    } else {
        while (1) {
            if (Serial.available()) {
                inChar = Serial.read();
                if (inChar == ASCII_BS  ||
                    inChar == ASCII_TAB ||
                    inChar == ASCII_CR  ||  
                    inChar == ASCII_NL  ||   // new
                    inChar == ASCII_DEL ||   // new
                    inChar == ASCII_ESC ||
                    isprint(inChar)) {
                    return inChar;
                }
            }
        }
    }
}

#endif



// Tue Jun 27 01:07:58 UTC 2017
// 4735-a0r-06-

#include <Arduino.h>
#include "../../yaffa.h"
// #include "../../Error_Codes.h"

#ifdef EXT_KERN_GETLINE
#include "getline.h"

// Sat Jun 24 17:00:15 UTC 2017
// 4735-a0r-01-

#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>

#define FLASH_TYPE     SPIFLASHTYPE_W25Q16BV  // Flash chip type.
#define FLASH_SS       SS                    // Flash chip SS pin.
#define FLASH_SPI_PORT SPI                   // What SPI port is Flash on?

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT);     // Use hardware SPI 

Adafruit_W25Q16BV_FatFs fatfs(flash);


// void xxsetup_spi_flash(void) {
void setup_spi_flash(void) {

  // Serial.println("Adafruit SPI Flash FatFs Full Usage Example");
  Serial.println("Adafruit SPI Flash - reading");
  
  // Initialize flash library and check its chip ID.
  if (!flash.begin(FLASH_TYPE)) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1);
  }
  Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.GetJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin()) {
    Serial.println("Error, failed to mount newly formatted filesystem!");
    Serial.println("Was the flash chip formatted with the fatfs_format example?");
    while(1);
  }
  Serial.println("Mounted filesystem!");
}





void xxcreate_test_directory(void) {
}



void xxwrite_a_test_file(void) {
}

void xxread_a_test_file(void) {
  // Now open the same file but for reading.
  File readFile = fatfs.open("/forth/job.fs", FILE_READ);
  if (!readFile) {
    Serial.println("Error, failed to open job.fs for reading!");
    while(1);
  }

  // Read data using the same read, find, readString, etc. functions as when using
  // the serial class.  See SD library File class for more documentation:
  //   https://www.arduino.cc/en/reference/SD
  // Read a line of data:
  String line = readFile.readStringUntil('\n');
  Serial.print("First line of job.fs: "); Serial.println(line);

  // You can get the current position, remaining data, and total size of the file:
  Serial.print("Total size of job.fs (bytes): "); Serial.println(readFile.size(), DEC);
  Serial.print("Current position in job.fs: "); Serial.println(readFile.position(), DEC);
  Serial.print("Available data to read in job.fs: "); Serial.println(readFile.available(), DEC);

  // And a few other interesting attributes of a file:
  Serial.print("File name: "); Serial.println(readFile.name());
  Serial.print("Is file a directory? "); Serial.println(readFile.isDirectory() ? "Yes" : "No");

  // You can seek around inside the file relative to the start of the file.
  // For example to skip back to the start (position 0):
  if (!readFile.seek(0)) {
    Serial.println("Error, failed to seek back to start of file!");
    while(1);
  }

  // And finally to read all the data and print it out a character at a time
  // (stopping when end of file is reached):
  Serial.println("Entire contents of job.fs:");
  while (readFile.available()) {
    char c = readFile.read();
    Serial.print(c);
  }

  // Close the file when finished reading.
  readFile.close();
}



#ifndef HAS_STANDARD_BUILD_HERE
void xxread_from_code_py_file(void) {
}
#endif


void xxtail_code_bb(void) {
  // You can open a directory to list all the children (files and directories).
  // Just like the SD library the File type represents either a file or directory.

// hold: while(1); Serial.println("WILL ROBINSON.");
         while(1); Serial.println("WILL ROBINSON.");
}

void xxspi_flash_main(void) {
}




/******************************************************************************/
/** getLine                                                                  **/
/**   read in a line of text ended by a Carriage Return (ASCII 13)           **/
/**   Valid characters are:  Backspace, Carriage Return, Escape, Tab, and    **/
/**   standard printable characters. Passed the address to store the string, **/
/**   and Returns the length of the string stored                            **/
/******************************************************************************/

uint8_t getLine(char* ptr, uint8_t buffSize) {
  char inChar;
  uint8_t count = 0;
  File thisFile;

  uint8_t fileClosed = TRUE ;

  if (spiFlashReading) { // if TRUE
      Serial.println("\r\nSEEN: getline.cpp   line: 140\r\n");
      if (fatfs.exists("/forth/job.fs")) {
          if (fileClosed) {
            File forthSrcFile = fatfs.open("/forth/job.fs", FILE_READ);
            thisFile = (File) forthSrcFile;
            fileClosed = FALSE ; // it is open, now.
          }
      }
  }

  do {
    if (spiFlashReading) { // if TRUE
        if (thisFile) {
            if (thisFile.available()) {
                inChar = thisFile.read();
            }
        }

    } else {
        inChar = getKey(); 
    }

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





if (spiFlashReading) {
  Serial.println("\r\n getLine SEEN line: 59\r\n");
  spiFlashReading = FALSE ; // tripwire
}


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
// #include "getkey.h"

/******************************************************************************/
/** getKey                                                                   **/
/**   waits for the next valid key to be entered and return its value        **/
/**   Valid characters are:  Backspace, Carriage Return (0x0d), Escape,      **/
/**   Tab, Newline (0x0a) and standard (printable) characters                **/
/******************************************************************************/
char getKey(void) {
  char inChar;

  // load -- provides this boolean:
  if (spiFlashReading) { // if TRUE

    // Serial.println("\r\nSEEN: line 35\r\n");

    // if (fatfs.exists("/forth/job.fs"))
          // File forthSrcFile = fatfs.open("/forth/job.fs", FILE_READ);

                  if (inChar == ASCII_BS  ||
                      inChar == ASCII_TAB ||
                      inChar == ASCII_CR  ||  
                      inChar == ASCII_NL  ||   // new
                      inChar == ASCII_DEL ||   // new
                      inChar == ASCII_ESC ||
                      isprint(inChar)) {
                        return inChar;
                  }
  } // end of 'if (spiFlashReading) code block
    else {


//  75   if (dataFile) {
//  76     // File was opened, now print out data character by character until at the
//  77     // end of the file.
//  78     Serial.println("Opened file, printing contents below:");
//  79     while (dataFile.available()) {
//  80       // Use the read function to read the next character.
//  81       // You can alternatively use other functions like readUntil, readString, etc.
//  82       // See the fatfs_full_usage example for more details.
//  83       char c = dataFile.read();
//  84       Serial.print(c);
//  85     }
//  86   }


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
  } // while

  } // end of large 'else' after the spi reading test

}

#endif



# ainsuForth-CPX_fs

EXPERIMENTAL -- the below, plus a limited use of the SPI flash
to author forth source code on the device.  Currently, this
amounts to reading a full program (a multi-line forth source
program) from /forth/job.fs on the SPI flash volume.


Platform: Circuit Playground Express (an M0 board w/SPI 2MB flashROM) - 29 July 2017

A Forth for SAMD21G18A based on YAFFA-ARM Forth - 2012 by Stuart Wood.



See compatibility.h for (some) configuration options across
target board devices.

------------------------------------------------------------
Current platform is the Adafruit CPX (Circuit Playground Express) - PRODUCT ID: 3333
which is ATSAMD21 Cortex M0+ based.
------------------------------------------------------------

Platform will change frequently -- five different targets are
tested on a (somewhat) rotating basis:

  * Arduino M0 Pro
  * Adafruiit Feather M0 Express
  * Adafruit Metro M0 Express
  * Adafruit Circuit Playground Express (which is also an M0 board)
  * Adafruit Gemma M0

Tue Aug  1 23:21:00 UTC 2017

ed91c

old:

# YAFFA-ARM
YAFFA for Arduino ARM Processors 

See:
 [ https://github.com/sdwood68/YAFFA-ARM ]


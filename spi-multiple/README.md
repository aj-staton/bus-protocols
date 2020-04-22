# SPI (Multiple)
This lab used a software-defined implementation of SPI to communicate with a sensor and flash memory. The sensor had values that were read; those values were written to off-chip flash memory.

## Major Accomplishments
From a high-level, these are the major things that I completed:
 * Wrote a function to support a streaming SPI transaction. This function allowed a variable amount of data to be read in a single SPI transaction. 
 * Wrote a function to write in SPI. So, an 8-bit address was sent on MOSI, then it was followed by another 8-bits of DATA (still on MOSI).
 * Took the variable amount of data from the `spi_read_streaming()` function and wrote it to a specific page and offset in flash memory.

/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels 
 * Used and modified by Austin Staton for CSCE317, Project lab_virtspi_multi
 */

#include "support.h"
#include <stdlib.h>

/* number of SPI SCK cycles per system clock cycle */
#define SPI_CLK_RATIO 16

#define DEBUG 0 

/* Aliases for the chip select lines. */
#define SENSOR IO_CS1 // A.K.A VD-002
#define FLASH  IO_CS2 // A.K.A. VD-003

/* Aliases for the registers on the peripherals */
#define WHO_AM_I  0x0F
#define S_DATA    0x10
#define S_DATACNT 0x11
#define F_NPAGE   0x01
#define F_PAGESEL 0x10
#define F_OFFSET  0x11
#define F_DATA    0x12

uint8_t _buffer[129];
uint8_t _datacnt = 0;

uint8_t spi_read_single(simulation_state* s, uint8_t addr, simulation_io CS);
void spi_read_streaming(simulation_state* s);
void spi_write(simulation_state *s, uint8_t addr, uint8_t data, 
      simulation_io CS); 

int main(int argc, char **argv) { 
	simulation_state* s = initialize_simulation(argc, argv);
  // Query WHO_AM_I
  if (spi_read_single(s, WHO_AM_I, SENSOR) != 0x35 || 
      spi_read_single(s, WHO_AM_I, FLASH) != 0x36) {
    printf("error: WHO_AM_I failed.\n");
  } else {
    printf("Read Successful.\n");
  }
  // Get the number of available memory pages from flash memory.
  uint8_t total_pages = spi_read_single(s, F_NPAGE, FLASH);
  if (DEBUG) printf("There are  %hhu  pages in flash.\n", total_pages);
  //total_pages++;
  int active_page = 0;
  while (active_page < total_pages) {
    /* The READ from the SENSOR */
    spi_read_streaming(s);
    if (DEBUG) printf("Sensor Data retrieved.\n");
    /* The WRITE to FLASH */
    // Make a Page's header. 
    spi_write(s, F_PAGESEL, active_page, FLASH);
    spi_write(s, F_OFFSET, 0, FLASH);
    spi_write(s, F_DATA, 0x11, FLASH); // 0x11 signals that a page holds sensor
    spi_write(s, F_OFFSET, 1, FLASH);
    spi_write(s, F_DATA, active_page, FLASH);
    spi_write(s, F_OFFSET, 2, FLASH);
    spi_write(s, F_DATA, _datacnt, FLASH);
    // Write the Actual data.
    for (int i = 0; i < _datacnt-1; ++i) {
      spi_write(s, F_OFFSET, 3+i, FLASH);
      spi_write(s, F_DATA, _buffer[i], FLASH);
    }
    active_page += 1;
  }

}

/*
 *  @brief -- a bit-banged representation of SPI.`
 *  This will be written where CPOL = 1, CPHA = 1 (Mode 3)
 *  and the MSB is transmitted first.
 *  
 *  @params: s    -- the hardware simulation on Verilator.
 *           addr -- the address to read from the peripheral.
             CS   -- the chip to read from.
 */
uint8_t spi_read_single(simulation_state* s, uint8_t addr, simulation_io CS) {
  uint8_t data = 0x00;
  // IO_SCK is supposed to be active-low. I don't want
  // and immediate sample at the first pulldown of CS.
  write_io(s, IO_SCK, 1);
  delay_cycles(s, 1);
  // Pull CS Low to signal transaction.
  write_io(s, CS, 0);
  delay_cycles(s, SPI_CLK_RATIO);
  /* Transactions:  
   *  First Loop: Write the address to the sensor on MOSI.
   *  Second Loop: Read the data from the sensor on MISO. */
  for (int i = 7; i >= 0; --i) {
    // Make sure clock is at zero for 8 cycles.
    write_io(s, IO_SCK, 0);
    // Write to MOSI:
    write_io(s, IO_MOSI, ((addr >> i) & 0x01));
    delay_cycles(s, SPI_CLK_RATIO/2);
    // Make sure clock is at one for 8 cycles.
    write_io(s, IO_SCK, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
  }
  for (int i = 7; i >= 0; --i) {
    // Make sure clock is at zero for 8 cycles.
    write_io(s, IO_SCK, 0);
    // Write a Dummy Value to MOSI:
    write_io(s, IO_MOSI, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
    // Make sure clock is at one for 8 cycles.
    // Read MISO:
    data |= (read_io(s, IO_MISO) << i);
    write_io(s, IO_SCK, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
  }
  // Pull CS high--transaction ended.
  write_io(s, CS, 1);
  return data;
}

/*
 * @brief -- this is done similarly to the spi_single_read() function above. It
 * is meant to transmit an address on MOSI, then read values back. The
 * difference is that the MISO wil return a variable amount of 8-bit 
 * sensor readings continuously.
 * 
 * Note: this function is only applicable to the SENSOR.
 * 
 * @params: s -- the hardware simulation in Verilatory
 */
void spi_read_streaming(simulation_state* s) {
  memset(_buffer, 0, sizeof(_buffer)); // Reset the array to 0's.
  _datacnt = spi_read_single(s, S_DATACNT, SENSOR); /* The number of bytes that will come back. */
  /* Busy wait to until a non-zero value comes back. This indicates that the
   * sensor is ready to write values. */
  while (_datacnt == 0) {
    if (DEBUG) printf("Polled\n");write_io(s, IO_SCK, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
    _datacnt = spi_read_single(s, S_DATACNT, SENSOR);
  }

  if (DEBUG) printf("  Data count can read  %hhu  bytes.\n", _datacnt);

  // Pull CS low for the entirety of the transaction.
  write_io(s, SENSOR, 0);

  // Write to DATA register.
  uint8_t data = S_DATA;
   for (int i = 7; i >= 0; --i) { 
    // Make sure clock is at zero for 8 cycles.
    write_io(s, IO_SCK, 0);
    // Write to MOSI:
    write_io(s, IO_MOSI, ((data >> i) & 0x01));
    delay_cycles(s, SPI_CLK_RATIO/2);
    // Make sure clock is at one for 8 cycles.
    write_io(s, IO_SCK, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
  }

  // Read the variable amount of data.
  //   Idea: Read one byte, write it to an array.
  for (int i = 0; i < _datacnt; ++i) {
    uint8_t tmp = 0x00;
    for (int i = 7; i >= 0; --i) {
      // Make sure clock is at zero for 8 cycles.
      write_io(s, IO_SCK, 0);
      // Write a Dummy Value to MOSI:
      write_io(s, IO_MOSI, 1);
      delay_cycles(s, SPI_CLK_RATIO/2);
      // Make sure clock is at one for 8 cycles.
      // Read MISO:
      tmp |= (read_io(s, IO_MISO) << i);
      write_io(s, IO_SCK, 1);
      delay_cycles(s, SPI_CLK_RATIO/2);
    }
    _buffer[i] = tmp;
    if (DEBUG) printf("    The value of  %hhu  is going to index %d\n", tmp, i);
  } 

  // Pull CS High at the end.
  write_io(s, SENSOR, 1);
  delay_cycles(s, SPI_CLK_RATIO/2);
}

/*
 * @brief -- write() will transmit two bytes (from the master, on MOSI)
 * sequentially. There is no reading of MISO and it is assumed to be held low
 * by the peripheral.
 * 
 * Note: The MSB of the register address must be 1 -- it's the read/write flag.
 * 
 * @params: s    -- the hardware simulation in Verilatory
 *          addr -- the register address to write to
 *          data -- the data to write to the address
 *          CS   -- the peripheral to write to
 */
void spi_write(simulation_state *s, uint8_t addr, uint8_t data, 
      simulation_io CS) {
  addr = (0x80 | addr); // First bit is always 1.
  write_io(s, IO_SCK, 1);
  delay_cycles(s, 1);
  // Pull CS Low to signal transaction.
  write_io(s, CS, 0);
  delay_cycles(s, SPI_CLK_RATIO);
  /* Transactions:  
   *  First Loop: Write the address to the peripheral on MOSI.
   *  Second Loop: Write the data from the peripheral on MOSI. */
  for (int i = 7; i >= 0; --i) {
    // Make sure clock is at zero for 8 cycles.
    write_io(s, IO_SCK, 0);
    // Write to MOSI:
    write_io(s, IO_MOSI, ((addr >> i) & 0x01));
    delay_cycles(s, SPI_CLK_RATIO/2);
    // Make sure clock is at one for 8 cycles.
    write_io(s, IO_SCK, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
  }
  if (DEBUG) printf("Writing  %hhu  to store on flash.", data);
  for (int i = 7; i >= 0; --i) {
    // Make sure clock is at zero for 8 cycles.
    write_io(s, IO_SCK, 0);
    // Write a value to MOSI:
    write_io(s, IO_MOSI, ((data >> i) & 0x01));
    delay_cycles(s, SPI_CLK_RATIO/2);
    // Make sure clock is at one for 8 cycles.
    write_io(s, IO_SCK, 1);
    delay_cycles(s, SPI_CLK_RATIO/2);
  }
  // Pull CS high--transaction ended.
  write_io(s, CS, 1);
}


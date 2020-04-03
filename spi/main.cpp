/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/* Used and modified by Austin Staton for CSCE317. */

#include "support.h"

/* number of SPI SCK cycles per system clock cycle */
#define SPI_CLK_RATIO 16

uint8_t spi_read(simulation_state* s, uint8_t addr);

int main(int argc, char **argv) {
  simulation_state* s = initialize_simulation(argc, argv);
  
  uint8_t whoami = spi_read(s, 0x0F); 
  if (whoami == 0x34) {
    printf("WHO_AM_I read correctly.\n");
    for (int i = 0; i < 4; ++i){
       uint8_t data = spi_read(s, 0x10);
       printf("DATA read %d value is: %hhu\n", i, data);
    }
  } else {
    printf("Error: WHO_AM_I was not read correctly.\n");
  }
}

/*
 *  @brief -- a bit-banged representation of SPI.
 *  This will be written where CPOL = 1, CPHA = 1 (Mode 3)
 *  and the MSB is transmitted first.
 *  
 *  @params: s   -- the hardware simulation on Verilator.
 *           addr -- the adress to read from the sensor.
 */
uint8_t spi_read(simulation_state* s, uint8_t addr) {
  uint8_t data = 0x00;
  // IO_SCK is supposed to be active-low. I don't want
  // and immediate sample at the first pulldown of CS.
  write_io(s, IO_SCK, 1);
  delay_cycles(s, 1);
  // Pull CS Low to signal transaction.
  write_io(s, IO_CS, 0);
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
  write_io(s, IO_CS, 1);
  return data;
}

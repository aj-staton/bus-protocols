/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/* Used and modified by Austin Staton for CSCE317. */

#include "support.h"

/* number of SPI SCK cycles per system clock cycle */
#define SPI_CLK_RATIO 16

uint16_t spi_read(simulation_state* s, uint16_t addr);

int main(int argc, char **argv) {
  simulation_state* s = initialize_simulation(argc, argv);
	
  printf("WHO_AM_I returned: %hu\n", spi_read(s, 0x0F));
  // printf("DATA returned: %hu\n", spi_read(s, 0x10));
}

/*
 *  @breif -- a bit-banged representation of SPI.
 *  This will be written where CPOL = 1, CPHA = 1, (Mode 3)
 *  and the MSB is transmitted first.
 *  
 *  @params: s   -- the hardware simulation on Verilator.
 *           req -- the address to read from the sensor.
 */
uint16_t spi_read(simulation_state* s, uint16_t addr) {
 uint16_t data = 0x00;
 // Pull CS Low to signal transaction.
 write_io(s, IO_CS, 0);
 delay_cycles(s, 1);
 /* Transactions:
  *  First: Write the address to the sensor on MOSI.
  *  Second: Read the data from the sensor on MISO.
  */
 for (int i = 0; i < 8; ++i) {
   write_io(s, IO_CS, 0);
   if (i % 2 == 1) {
     write_io(s, IO_SCK, 1);
   } else {
     write_io(s, IO_SCK, 0);
   }
   delay_cycles(s, 1);
 }
 for (int i = 0; i < 8; ++i) {
   write_io(s, IO_CS, 0);
   delay_cl
 }
 return data;
}

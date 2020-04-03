/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/* Used and modified by Austin Staton for CSCE317. */

#include "support.h"

/* number of SPI SCK cycles per system clock cycle */
#define SPI_CLK_RATIO 16
#define MASK(byte, mask) (byte & mask)


typedef enum {
  TRUE,
  FALSE
} bool_t;


bool_t is_high(uint8_t byte, uint8_t N);
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
 *  This will be written where CPOL = 1, CPHA = 1, (Mode 3)
 *  and the MSB is transmitted first.
 *  
 *  @params: s   -- the hardware simulation on Verilator.
 *           req -- the address to read from the sensor.
 */

uint8_t spi_read(simulation_state* s, uint8_t addr) {
 
 uint8_t data = 0x00;
 // IO_SCK is supposed to be active-low. I don't want
 // and immediate sample at the first pulldown of CS.
 write_io(s, IO_SCK, 1);
 delay_cycles(s, 1);
 // Pull CS Low to signal transaction.
 write_io(s, IO_CS, 0);

 /* Transactions:  *  First: Write the address to the sensor on MOSI.
  *  Second: Read the data from the sensor on MISO. */
 // The Write
 for (int i = 15; i >= 0; --i) {
   write_io(s, IO_CS, 0);
   if (i % 2 == 1) { // This is NOT active
     write_io(s, IO_SCK, 1);
   } else {
     write_io(s, IO_SCK, 0);
     if (is_high(addr, i/2) == TRUE) {
       write_io(s, IO_MOSI, 1);
     } else {
       write_io(s, IO_MOSI, 0);
     }
   }
   delay_cycles(s, 1);
 }
 write_io(s, IO_MOSI, 1);
 delay_cycles(s, 1);
 // The Read
 for (int i = 15; i >= 0; --i) {
   write_io(s, IO_CS, 0);
   if (i % 2 == 1) { // This is NOT active
     write_io(s, IO_SCK, 1);
   } else {
     write_io(s, IO_SCK, 0);
     data |= (read_io(s, IO_MISO) << (i/2+1));
   }
   delay_cycles(s, 1);
 }
 return data;
}
/*
 * @breif is_high() will get determine if the Nth bit of
 *   byte is 1 or 0. N is wrt big-endian order.
 */
bool_t is_high(uint8_t byte, uint8_t N) {
 if ((byte >> N) & 0x1) {
   return TRUE;
 } else {
   return FALSE;
 }
}

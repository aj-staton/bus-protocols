/*
 *  Written by Robert Carff and Austin Staton
 *  Date: Feb 26th, 2020
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "lis3dh.h"

#define SCL PORTB5
#define SDA PORTB3
#define SDO PORTB4
#define SS  PORTB2
#define INT PORTD2

#define SPI_SELECT() PORTB &= ~(1<<SS);
#define SPI_DESELECT() PORTB |= (1<SS);

int16_t x, y, z;

void init();
int8_t OffChipRead(int16_t dest_reg);
int8_t OffChipWrite(int16_t dest_reg, uint16_t data);

int main(void) {
  printf("in the init");
  init();
  printf("%c", OffChipRead(WHO_AM_I));
 /*
  while(1) {
    x = OffChipRead(OUT_X_H);
    x <<= 8;
    x |= OffChipRead(OUT_X_L);
    x >>= 6;
    y = OffChipRead(OUT_Y_H);
    y <<= 8;
    y |= OffChipRead(OUT_Y_L);
    y >>= 6;
    z = OffChipRead(OUT_Z_H);
    z <<= 8;
    z |= OffChipRead(OUT_Z_L);
    z >>= 6;
    printf("X: %hd, Y: %hd, Z: %hd", x, y, z);
    _delay_ms(1000);
   }
 */
  
  
  return 0;
}
/*
	int[] = [1,2,3,4,0]
*/
void init(void) {
  // SPI config:
  SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0);
  DDRB = (1<<DDB2) | (1<<DDB3) | (1<<DDB5);
  PORTB |= (1<<SS);
  printf("in the init");
  // Accelerometer Config:
  OffChipWrite(CTRL_REG1,0x07); // Configure output data rate & Enable X,Y,Y axis. 
  OffChipWrite(CTRL_REG5,0x08); // Disable FIFO and enable latching interrupts.
  OffChipWrite(FIFO_CTRL_REG,0x00); // Set FIFO to Bypass mode.
  OffChipWrite(CTRL_REG3,0x10); // Enable DRDY1 interrupt on the Accelerometer INT1 pin.
  OffChipWrite(CTRL_REG6,0x02); // Set INT1 interrupt to be active low.
  
  // Value Instantiations:
  x = 0; y = 0; z = 0;
}
/*
// Read the INT0 register on the uController.
ISR(INT0_vect) {
  // Read from INT1_SOURCE to clear the interrupt.
  // Acknowlede and reset the STATUS_REG which polls for X,Y,Z value updates.
  OffChipRead(STATUS_REG); 
  // Get x, y, z high and low 8 bits.
  //   Each is stored as two's complement, left justified integer. 
  x = OffChipRead(OUT_X_H);
  x <<= 8;
  x |= OffChipRead(OUT_X_L);
  x >>= 6;

  y = OffChipRead(OUT_Y_H);
  y <<= 8;
  y |= OffChipRead(OUT_Y_L);
  y >>= 6;
  z = OffChipRead(OUT_Z_H);
  z <<= 8;
  z |= OffChipRead(OUT_Z_L);
  z >>= 6;
  printf("X: %hd, Y: %hd, Z: %hd", x, y, z);
}
*/

/* @breif AccelRead() will read register values found on the LISD3H. This will
 *        entail manually sending SPI signals to their respective pins.
 * 
 * @params dest_reg -- the location to read the data from, on the accelerometer
 *
 * @return The 8 bits of data found at each reg. TODO: is it 8 or 6??
 */
int8_t OffChipRead(int16_t dest_reg) {
  SPI_SELECT();
  
  SPDR = dest_reg;
  loop_until_bit_is_set(SPDR, 7);
  // dest_reg = SPDR;
  SPDR = 0xFF;
  loop_until_bit_is_set(SPDR, 7);
  
  return SPDR;
}

int8_t OffChipWrite(int16_t dest_reg, uint16_t data) {
  SPI_SELECT();
  
  SPDR = dest_reg;
  loop_until_bit_is_set(SPDR, 7);
  // dest_reg = SPDR; Uncomment to validate what's sent.
  _delay_us(10);
  SPDR = data;
  loop_until_bit_is_set(SPDR,7);

  SPI_DESELECT();
  return SPDR;
}

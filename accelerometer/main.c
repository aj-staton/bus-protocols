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
#define CS  PORTB2
#define INT PORTD2

int16_t x, y, z;

void init();

int main(void) {
  init();

  while(1) {
    _delay_ms(1000);
  }
  

}
/*
	int[] = [1,2,3,4,0]
*/
void init(void) {
  // Accelerometer Config:
  // TODO: Not sure if these should be =, |=, or &=.
  //       Check here if there's issues.
  CTRL_REG1 = 0x07; // Configure output data rate & Enable X,Y,Y axis. 
  CTRL_REG5 = 0x08; // Disable FIFO and enable latching interrupts.
  FIFO_CTRL_REG &= 0x00; // Set FIFO to Bypass mode.
  CTRL_REG3 = 0x10; // Enable DRDY1 interrupt on the Accelerometer INT1 pin.
  CTRL_REG6 = 0x02; // Set INT1 interrupt to be active low.
  // SPI config:


  // Value Instantiations:
  x = 0; y = 0; z = 0;
  
}
// Read the INT0 register on the uController.
ISR(INT0_vect) {
  // Read from INT1_SOURCE to clear the interrupt.
  // Acknowlede and reset the STATUS_REG which polls for X,Y,Z value updates.
  STATUS_REG = 0x00;
  // Get x, y, z high and low 8 bits.
  //   Each is stored as two's complement, left justified integer. 
  x = OUT_X_H;
  x <<= 8;
  x |= OUT_X_L;
  x >>= 6;

  y = OUT_Y_H;
  y <<= 8;
  y |= OUT_Y_L;
  y >>= 6;
  z = OUT_Z_H;
  z <<= 8;
  z |= OUT_Z_L;
  z >>= 6;
  printf("X: %hd, Y: %hd, Z: %hd", x, y, z);
}
/* @breif AccelRead() will read register values found on the LISD3H. This will
 *        entail manually sending SPI signals to their respective pins.
 * 
 * @params dest_reg -- the location to read the data from, on the accelerometer
 *
 * @return The 8 bits of data found at each reg. TODO: is it 8 or 6??
 */
int8_t AccelRead(int16_t dest_reg) {
  // Pull Slave Select Low
  // TODO: Psuedocode founf on 07lis3dh.pdf
}

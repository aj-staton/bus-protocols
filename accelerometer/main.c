/*
 *  Written by Robert Carff and Austin Staton
 *  Date: Feb 26th, 2020
 */
#include <avr/io.h>
#include <avr/interrupt.h>
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
uint8_t OffChipRead(uint8_t dest_reg);
uint8_t OffChipWrite(uint8_t dest_reg, uint8_t data);

int main(void) {
  
  init();
  printf("0x%x\n", OffChipRead(WHO_AM_I));
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
  // UART config (for printf):
  UBRR0=(((F_CPU/(UART_BAUDRATE*16UL)))-1); // set baud rate
  UCSR0B|=(1<<TXEN0); //enable TX 
  UCSR0B|=(1<<RXEN0); //enable RX 

  UCSR0C |= (1 << UCSZ01 ) | (1 << UCSZ00 ); // character size of 8
  UCSR0C &= ~(1 << USBS0 ); // 1 stop bit
  UCSR0C &= ~( (1 << UPM01 ) | (1 << UPM00 )); // disable parity
  UCSR0B |= (1<<RXCIE0); // enable RX interrupt

  // SPI config:
  SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0);
  DDRB = (1<<DDB2) | (1<<DDB3) | (1<<DDB5);
  PORTB |= (1<<SS);

  // Accelerometer Config:
  //OffChipWrite(CTRL_REG1,(0x01 << 4) | 0x07); // Configure output data rate & Enable X,Y,Y axis. 
  //OffChipWrite(CTRL_REG5,0x08); // Disable FIFO and enable latching interrupts.
  //OffChipWrite(FIFO_CTRL_REG,0x00); // Set FIFO to Bypass mode.
  //OffChipWrite(CTRL_REG3,0x10); // Enable DRDY1 interrupt on the Accelerometer INT1 pin.
  //OffChipWrite(CTRL_REG6,0x02); // Set INT1 interrupt to be active low.

  // Enable Atmega Interrupts on INT_0
  //EIMSK = 0x01; 

  // Value Instantiations:
  //x = 0; y = 0; z = 0;
}
/*
// Read the INT0 register on the uController. Look a ISC01 = 0 and ISC00=0, maybe set it?
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

/* @breif OffChipRead() will read register values found on the LISD3H. This will
 *        entail manually sending SPI signals to their respective pins.
 * 
 * @params dest_reg -- the location to read the data from, on the accelerometer
 *
 * @return The 8 bits of data found at each reg.
 */
uint8_t OffChipRead(uint8_t dest_reg) {
  SPI_SELECT();
  
  SPDR = dest_reg | 0x80;
  loop_until_bit_is_set(SPDR, 7);
  // dest_reg = SPDR;
  SPDR = 0xFF;
  loop_until_bit_is_set(SPDR, 7);
  // End Signal
  SPI_DESELECT(); 
  return SPDR;
}

uint8_t OffChipWrite(uint8_t dest_reg, uint8_t data) {
  SPI_SELECT();

  SPDR = dest_reg;
  loop_until_bit_is_set(SPDR, 7);
  dest_reg = SPDR;
  _delay_us(10);
  SPDR = data;
  loop_until_bit_is_set(SPDR,7);

  SPI_DESELECT();
  return SPDR;
}

int uart_putchar(char c, FILE *stream) {
       

        while(!(UCSR0A&(1<<UDRE0))){}; //wait while previous byte is completed
        if (c == '\n') {
                uart_putchar('\r', stream);
        }
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = c;
        
        return 0;
}

/**
 * @brief Read one character from UART0, blocking
 *
 * @param stream for compatibility
 *
 * @return
 */
int uart_getchar(FILE *stream) {
        while(!(UCSR0A & (1<<RXC0))){} // wait until data comes
        return UDR0;
}

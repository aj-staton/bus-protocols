/* Copyright 2020 Charles Daniels, Jason Bakos, Philip Conrad */

/* Used by Robert Carff and Austin Staton for Part C of Lab 1 in CSCE 317. */

/* Demonstration of asynchronous UART receive. Maintains a ring buffer of
 * data read in by the UART interrupt, and displays it's contents from a
 * foreground loop each interval. 
 *
 * NOTE: The bit-banging of UART's software implementation requires a baud rate
 * of 9600 bps. 57600 bps is too high and results in bit skew. 
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#define BUFSZ 64
#define INTERVAL_MS 1000

char buf[BUFSZ+1];
uint8_t cursor;
int state = 0;
// Blinking state definitions.
#define ON 1
#define OFF 0

char str1[] = "on";
char str2[] = "off";

/**
 * @brief output one character via UART, on UART0. UART uses a LOW start bit,
 *        eight data bits, and a HIGH stop bit. 
 * 	  
 * @param c the character
 * @param stream file handle, this is for compatibility
 *
 * @return
 */
int uart_putchar(char c, FILE *stream) {
	/* If using the UART hardware, uncomment this chunk.

        while(!(UCSR0A&(1<<UDRE0))){}; //wait while previous byte is completed
        if (c == '\n') {
                uart_putchar('\r', stream);
        }
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = c;
	*/
	cli(); // Disable interupts during transmission.
	// Pull TX low to send sart bit
	PORTD &= ~(1 << PORTD1);
	// Wait 9600^-1 s (A clock period)
	_delay_us(104UL);
	for (int i = 0; i < 8; i++) {
	  // High Bit Case
	  if (((c >> i) & 0x01) != 0) {
	    PORTD |= (1 << PORTD1);
	  } // Low Bit Case
	  else {
	    /* PORTD &= (0 << PORTD1); */
	    PORTD &= ~(1 << PORTD1);
	  }
	  _delay_us(104UL);
	} 
	// Pull TX high to send stop bit.
	PORTD = PORTD | (1 << PORTD1);
	_delay_us(104UL);
	_delay_us(104UL); // Extra delay for safety.
	sei(); // Re-enable global interrupts.
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


/* interrupt called when a character is received from UART */
ISR (USART_RX_vect) {
	/* read the new character in under the cursor */
	buf[cursor] = UDR0;
	buf[cursor+1] = '\0';
	if (buf[cursor] == '\r' || buf[cursor] == '\n') {
	  if (strncmp(buf,str1,2) ==  0) {
	    //  printf("starting blinking\n");
	    // Update state.
	    state = 1;
	  }
	  else if (strncmp(buf,str2,3) == 0) {
	    // printf("stopped blinking\n");
	    // Update state.
	    state = 0;
	  }
	  else {
	    printf("Invalid command, not changing state\n");
	  }
	  buf[0] = '\0';
	  cursor = 0;
	  printf("Ready>\n");
	  return;
	}
	/* guarantee null termination */
	buf[BUFSZ] = '\0';
	
	/* advance the cursor */
	cursor = (cursor + 1) % BUFSZ;
}

void init(void) {
        // initialize USART
        UBRR0=(((F_CPU/(UART_BAUDRATE*16UL)))-1); // set baud rate
        // UCSR0B|=(1<<TXEN0); //enable TX; DISABLED to allow for hardware UART 
        UCSR0B|=(1<<RXEN0); //enable RX 

        UCSR0C |= (1 << UCSZ01 ) | (1 << UCSZ00 ) ; // character size of 8
        UCSR0C &= ~(1 << USBS0 ) ; // 1 stop bit
        UCSR0C &= ~( (1 << UPM01 ) | (1 << UPM00 ) ); // disable parity
        UCSR0B |= (1<<RXCIE0); // enable RX interrupt

	// Set Port D's data direction register to be PORTD1 (our TX pin).
	// Write 1 since it'll be used as output.
	DDRD = DDRD | (1 << PORTD1);
	// The first byte sent was always incorrect. This delay was added to
	// prevent any jumbling of bits.
	PORTD |= (1 << PORTD1);
	_delay_us(1000);

        // initialize file descriptors
        fdevopen(uart_putchar, NULL);
        fdevopen(NULL, uart_getchar);

	// clear the buffer
	buf[0] = '\0';
	cursor = 0;

	// enable interrupts globally
	sei();
}

int main(void) {
	init();
	printf("Ready>\n");
	while (1) {
	  PORTD |= (1 << PORTD1);
	  _delay_us(10);
	  PORTD &= ~(1 << PORTD1);
	  _delay_us(10);
	} 
}

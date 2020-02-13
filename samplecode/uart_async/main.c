/* Copyright 2020 Charles Daniels, Jason Bakos, Philip Conrad */

/* Demonstration of asynchronous UART receive. Maintains a ring buffer of
 * data read in by the UART interrupt, and displays it's contents from a
 * foreground loop each interval. */

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

/**
 * @brief output one character via UART, on UART0
 *
 * @param c the character
 * @param stream file handle, this is for compatibility
 *
 * @return
 */
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


/* interrupt called when a character is received from UART */
ISR (USART_RX_vect) {

	/* read the new character in under the cursor */
	buf[cursor] = UDR0;

	/* guarantee null termination */
	buf[BUFSZ+1] = '\0';
	
	/* advance the cursor */
	cursor = (cursor + 1) % BUFSZ;
}

void init(void) {
        // initialize USART
        UBRR0=(((F_CPU/(UART_BAUDRATE*16UL)))-1); // set baud rate
        UCSR0B|=(1<<TXEN0); //enable TX
        UCSR0B|=(1<<RXEN0); //enable RX

        UCSR0C |= (1 << UCSZ01 ) | (1 << UCSZ00 ) ; // character size of 8
        UCSR0C &= ~(1 << USBS0 ) ; // 1 stop bit
        UCSR0C &= ~( (1 << UPM01 ) | (1 << UPM00 ) ); // disable parity
        UCSR0B|=(1<<RXCIE0); // enable RX interrupt

        // initialize file descriptors
        fdevopen(uart_putchar, NULL);
        fdevopen(NULL, uart_getchar);

	// clear the buffer
	for (int i = 0 ; i < BUFSZ ; i++) { buf[i] = ' '; }

	cursor = 0;

	// enable interrupts globally
	sei();
}

int main(void) {
	init();

	while (1) {
		_delay_ms(INTERVAL_MS);

		printf("cursor=%3u buf='%s'\n", cursor, buf);

	}
}

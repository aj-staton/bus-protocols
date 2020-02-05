#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief output one character via UART, on UART0
 *
 * @param c the character
 * @param stream file handle, this is for compatibility
 *
 * @return
 */
int uart_putchar(char c, FILE *stream) {
    /* wait for the transmitter to become ready */
    loop_until_bit_is_set(UCSR0A, UDRE0);

    /* because it is assumed by most serial consoles, we automatically
     * rewrite plain LF endings to CRLF line endings */
    if (c == '\n') {
        uart_putchar('\r', stream);
    }

    /* wait for the transmitter to become ready, since we might have just
     * transmitted a CR */
    loop_until_bit_is_set(UCSR0A, UDRE0);

    /* transmit the character */
    UDR0 = c;

    /* signal success */
    return 0;
}

/**
 * @brief Read one character from UART0, blocking
 *
 * @param stream for compatibility
 *
 * @return the character that was read
 */
int uart_getchar(FILE *stream) {

    /* wait for the data to arrive */
    loop_until_bit_is_set(UCSR0A, RXC0);

    /* return the received data */
    return UDR0;

}

/**
 * @brief Initialize UART for use with stdio
 */
void uart_init(void) {
    /* initialize USART0 */
    UBRR0=(((F_CPU/(UART_BAUDRATE*16UL)))-1); // set baud rate
    UCSR0B|=(1<<TXEN0); //enable TX
    UCSR0B|=(1<<RXEN0); //enable RX

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // character size of 8
    UCSR0C &= ~(1 << USBS0); // 1 stop bit
    UCSR0C &= ~( (1 << UPM01) | (1 << UPM00) ); // disable parity

    /* initialize file descriptors, notice the functions we wrote earlier
     * are used as callbacks here */
    fdevopen(uart_putchar, NULL);
    fdevopen(NULL, uart_getchar);
    printf("\n\nUART initialized (%i 8N1)\n", UART_BAUDRATE);
}

void init(void) {
  // Sets PCO as an output.
  DDRC |= (1 << 0);
}

int main(void) {
  init();
  /* while true ... */
  while(1) {
    PORTC |= 1;
    _delay_ms(500);
    PORTC &= ~(1 << 0);
    _delay_ms(500);
  }
  /* sleep for 1/2 second */

  /* set PC0 high */

  /* sleep for 1/2 second */

  /* set PC0 to low */
}


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

/**
 * @breif Sets the appropriate input and output pins on the Atmega board.
 */
void inout_init(void) {
  // Sets PCO as an output.
  DDRC |= (1 << 0);

}

int main(void) {
  inout_init();
  uart_init();

  char buf[65];
  printf("im ready>\n");
  
  // Two states are possible:
  //   0 = LED isn't blinking.
  //   1 = LED is blinking.  
  int state = 0;
 
  while(1) { 
    scanf("%s", &buf);
    // buf = uart_getchar();
    // Check and set the current state.
    if (strcmp(buf,"on") ==  0) {
      printf("starting blinking\n");
      // Update state.
      state = 1;
      // Clear buffer char array. 
      memset(&buf[0], 0, sizeof(buf));   
    } else if (strcmp(buf,"off") == 0) {
      printf("stopped blinking\n");
      // Update state.
      state = 0;
      // Clear buffer.
      memset(&buf[0], 0, sizeof(buf));
    } else if (strlen(buf) == 0) {
      state = state; 
    } else {
      printf("Hello user! That command was wrong.\n");
      memset(&buf[0], 0, sizeof(buf)); 
    }
    // Continute the current state if it is correct.
    if (state == 0) { // No blink.
      while (UCSR0A & (1 << RXC0) == 0) {
        PORTC &= 0;
      }
    } else if (state == 1) { // Blink.
      while (UCSR0A & (1 << RXC0) == 0) { // If this logic is 1, then a char in in buffer.
        PORTC |= 1;
        _delay_ms(500);
        PORTC &= ~(1 << 0);
        _delay_ms(500);
      }
    } else {
      printf("Something is very wrong.");
    }
  }
}

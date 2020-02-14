#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

/* number of bytes for the buffer character data is read into */
#define BUFSZ 64
char buf[BUFSZ];
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

/**
 * @brief Shift all elements the given buffer starting at element 'start' one
 * element to the right
 *
 * @param buf buffer to modify in-place
 * @param used number of used elements in the buffer, must be at least one less
 * than the buffer size (validated by caller)
 * @param start the index of the first element which should be shifted
 */
void shiftright(char* buf, size_t used, size_t start) {
	for (char* c = &(buf[used-1]); c >= &(buf[start]); c -= sizeof(char)) {
		*(c+sizeof(char)) = *c;
	}
}

/**
 * @brief As with shiftright(), but in the other direction
 *
 * @param buf
 * @param used
 * @param start
 */
void shiftleft(char* buf, size_t used, size_t start) {
	for (char* c = &(buf[start]); c <= &(buf[used-1]); c += sizeof(char)) {
		*c = *(c+sizeof(char));
	}

}

/**
 * @brief Implements a simple line editor.
 *
 * This function will read text from the given stream using fgetc, and will
 * echo back appropriately on stdout. It terminates when the user enters
 * return.
 *
 * This function supports VT100-style home, end, delete, backspace, and arrow
 * keys. However, history is not supported (up arrow is an error).
 *
 * @param buf buffer to write user data into (will be overwritten)
 * @param prompt prompt to display
 * @param bufsz length of buffer
 * @param stream stream to read from
 */
void readline(char* buf, char* prompt, size_t bufsz, FILE* stream) {
	size_t cursor;
	size_t used;
	char recv;
	char prev;
	typedef enum {NORM, ESC, ESC3} mode_t;
	mode_t mode;

	mode = NORM;

	cursor = 0;
	used = 0;
	buf[0] = '\0';
	recv = '\0';

	/* display the prompt */
	// printf(prompt);

	while (1) {
		prev = recv;
		recv = fgetc(stream);

		if (recv == 0x1b) { /* ESC */
			/* handles things like arrow keys and DEL which use
			 * ANSI escapes */
			mode = ESC;

		} else if ( ((recv == ']') || (recv == ']')) && (mode == ESC)) {
			/* do nothing -- we're about to get an escape code */

		} else if ((recv == 'H') && (mode == ESC)) { /* home */
			/* return the cursor to the beginning of the buffer */
			cursor = 0;
			mode = NORM;

			/* move the terminal cursor to the beginning of the
			 * line, then to the end of the prompt */
			printf("%c[%iD", 0x1b, 1000);
			printf("%c[%iC", 0x1b, strlen(prompt));

		} else if ((recv == 'F') && (mode == ESC)) { /* end */
			/* move terminal cursor to the beginning of the line */
			printf("%c[%iD", 0x1b, 1000);

			/* move the cursor to the end of the buffer */
			cursor = used;

			/* move the terminal cursor to the end of the line,
			 * which is the buffer length plus the prompt length */
			printf("%c[%iC", 0x1b, cursor + strlen(prompt));

			mode = NORM;

		} else if ( (mode == NORM) && (recv >= ' ') && (recv != 0x7F) ) {
			if (cursor >= (bufsz -1)) {
				/* overflow */

				/* note that \a is the terminal bell */
				fputc('\a', stdout);

			} else if (cursor == used) { /* append */
				buf[cursor] = recv;

				/* ensure that the string remains null
				 * terminated */
				buf[cursor+1] = '\0';

				cursor ++;
				used++;

				/* echo back the character we just read */
				printf("%c", recv);

			} else { /* insert */

				/* shift everything after the cursor in the
				 * edit buffer one slot to the right */
				shiftright(buf, used, cursor);

				/* overwrite the current location in the
				 * edit buffer */
				buf[cursor] = recv;

				/* The cursor position will already be where we
				 * inserted, so just overwrite the rest of the
				 * line with here on in the edit buffer */
				printf("%s", &(buf[cursor]));

				cursor++;
				used++;

				/* return the beginning of the line, then put
				 * the terminal cursor back at the appropriate
				 * position */
				printf("%c[%iD", 0x1b, 1000);
				printf("%c[%iC", 0x1b, cursor + strlen(prompt));
			}

		} else if ( (mode == NORM) && (recv == 0x8) ){  /* backspace */
			if (cursor == 0) {
				/* underflow */
				fputc('\a', stdout);

			} else if (cursor == used) {
				/* this is the new end of the string */
				buf[cursor-1] = '\0';
				cursor--;
				used--;

				/* go back one, output a space, then go back
				 * one again */
				printf("\b \b");

			} else {

				/* shift everything in the edit buffer one slot
				 * to the left, this will implicitly overwrite
				 * the current cursor position */
				shiftleft(buf, used, cursor-1);
				cursor--;
				used--;

				/* the end of the string has shifted left by
				 * one, so we need to update the null
				 * terminator to reflect this */
				buf[used] = '\0';

				/* go back one spot, re-draw everything in the
				 * edit buffer after the position we just
				 * overwrote, then reset the terminal cursor
				 * position appropriately */
				printf("\b");
				printf("%s ", &(buf[cursor]));
				printf("%c[%iD", 0x1b, 1000);
				printf("%c[%iC", 0x1b, cursor + strlen(prompt));

			}

		} else if ( (mode == NORM) && (recv == 0x12) ) { /* C-r */
			/* Ctrl + R re-draws the line and re-sets the cursor
			 * position. This is useful if garbage has been written
			 * to the terminal */

			/* return to the beginning of the line */
			printf("\r");

			/* overwrite the entire space that the buffer may
			 * occupy with empty spaces */
			for (int i = 0 ; i < bufsz; i++) {
				printf(" ");
			}

			/* return to the beginning of the line, re-draw
			 * everything, and set the terminal cursor position */
			printf("\r");
			printf("%s%s", prompt, buf);
			printf("%c[%iD", 0x1b, 1000);
			printf("%c[%iC", 0x1b, cursor + strlen(prompt));

		} else if ( (mode == NORM) && (recv == 0x03) ) { /* C-c */
			/* Ctrl + C clears the edit buffer */

			/* beginning of the buffer is now also the end */
			buf[0] = '\0';
			cursor = 0;
			used = 0;

			/* clear the line */
			printf("\r");
			for (int i = 0 ; i < bufsz; i++) {
				printf(" ");
			}

			/* redraw the prompt and the now empty buffer */
			printf("\r");
			printf("%s%s", prompt, buf);

		} else if ( (mode == ESC) && (recv == 0x5b) ) {
			/* do nothing (probably about to get arrow key or DEL */

		} else if ( (mode == ESC) && (recv == 'D') && (prev == 0x5b)) {
			/* left arrow key */
			if (cursor > 0) {
				cursor --;
				printf("%c[%iD", 0x1b, 1);
			} else {
				fputc('\a', stdout);
			}
			mode = NORM;

		} else if ( (mode == ESC) && (recv == 'C') && (prev == 0x5b)) {
			/* right arrow key */
			if (cursor < (bufsz-1)) {
				cursor ++;
				printf("%c[%iC", 0x1b, 1);
			} else {
				fputc('\a', stdout);
			}
			mode = NORM;

		} else if ( (mode == ESC) && (recv == 0x33) ) {
			/* we expect to see a DEL next */
			mode = ESC3;

		} else if ( (mode == ESC3) && (recv == 0x7e)) {
			/* delete */

			if (cursor == used) {
				/* already at end */
				fputc('\a', stdout);
			} else {
				/* this works the same as backspace, except
				 * one character to the right */
				shiftleft(buf, used, cursor);
				used--;
				buf[used] = '\0';
				printf("\b");
				printf("%s ", &(buf[cursor-1]));
				printf("%c[%iD", 0x1b, 1000);
				printf("%c[%iC", 0x1b, cursor + strlen(prompt));

			}

			mode = NORM;


		} else if (mode == NORM) {
			/* the user has pressed return, so we are done reading
			 * the line */
			printf("\n");
			return;

		/* everything from here down is just error handling */
		} else if (mode == ESC) {
			printf("Don't know how to handle 0x%x in ESC mode\n", recv);
			mode = NORM;

		} else if (mode == ESC3) {
			printf("Don't know how to handle 0x%x in ESC3 mode\n", recv);
			mode = NORM;

		} else {
			printf("Don't know how to handle 0x%x\n", recv);
		}
	}
}

void init(void) {
	// initialize USART
	UBRR0=(((F_CPU/(UART_BAUDRATE*16UL)))-1); // set baud rate
	UCSR0B|=(1<<TXEN0); //enable TX
	UCSR0B|=(1<<RXEN0); //enable RX

	UCSR0C |= (1 << UCSZ01 ) | (1 << UCSZ00 ) ; // character size of 8
	UCSR0C &= ~(1 << USBS0 ) ; // 1 stop bit
	UCSR0C &= ~( (1 << UPM01 ) | (1 << UPM00 ) ); // disable parity

	// initialize file descriptors
	fdevopen(uart_putchar, NULL);
	fdevopen(NULL, uart_getchar);
	printf("\n\nUART initialized (%u 8N1)\n", UART_BAUDRATE);
	printf("initialization complete.\n\n");
}

int main(void) {
	init();
        int state = 0;
	buf[0] = '\0';
        cursor = 0;

	printf("Ready>\n");

	while(1) {
		_delay_ms(500);
		// Check if a character is ready to transmit.
 		if (UCSR0A & (1 << RXC0)) {
			readline(buf, "> ", BUFSZ, stdin);

			if (strcmp(buf,"on") ==  0) {
				state = 1; // Blinking State
			}
			else if (strcmp(buf,"off") == 0) {
				state = 0; // Non-Blinking State
			}
			else {
				printf("Invalid command, not changing state\n");
			}
			// Clear buffer after its fully reading it.
			// && Prompt user for another input.
			printf("Ready>\n");
			buf[0] = '\0';
			cursor = 0;
		}  

		// Check states in order to implement continuous blinking
		if (state == 0) { // Non-Blinking State 
			PORTC &= 0;
		}
		else if (state == 1) { // Blinking State
			PORTC |= 1;
        		_delay_ms(500);
        		PORTC &= ~(1 << 0);
		}
		else {
		        printf("your state isnt on or off\n");
		}
	}

}


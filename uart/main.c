#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

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


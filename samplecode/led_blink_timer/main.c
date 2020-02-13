/* Copyright 2020 Charles Daniels, Jason Bakos, Philip Conrad */

/* Demonstration of an LED blink program running based on a timer/counter
 * interrupt */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <stdbool.h>

/* be sure to set CS1[2:0] consistently */
#define CLOCK_PRESCALE 1024UL

/* blink interval */
#define INTERVAL_MS 250UL

/* 0xFFFF is the max value for timer/counter 1, and we want TCNTVAL to be
 * the number to initialize TCNT1 to such that it will overflow (triggering our
 * interrupt) after INTERVAL_MS many ms. F_CPU * INTERVAL_MS has units of
 * MHz * ms (unitless), and 10000 ms/s * CLOCK_PRESCALE is also unitless. */
#define TCNTVAL (0xFFFF - ((F_CPU * INTERVAL_MS) / (1000UL * CLOCK_PRESCALE)));

#define LEDPORT PORTC
#define LEDPIN 0
#define LEDDR DDRC

bool led_state;

ISR(TIMER1_OVF_vect) {
	if (led_state) {
		/* LED is on, turn it off */
		LEDPORT &= ~(1 << LEDPIN);
	} else {
		/* LED is off, turn it on */
		LEDPORT |= (1 << LEDPIN);
	}

	/* reset so we overflow again after the given interval */
	TCNT1 = TCNTVAL;

	/* flip states */;
	led_state = !led_state;
}

void init(void) {

	/* Note that we want to use T/C 1, because it is 16 bits, rather than
	 * 8. T/C 0 or 2 would overflow too fast for our use case (we would
	 * have to maintain our own counter to keep track of when to toggle the
	 * LED). */

	/* Set the clock prescaler to 1024^-1, so we should interrupt at a rate
	 * of 16Mhz / 1024 = .015625Mhz. */
	TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);

	TCNT1 = TCNTVAL;

	/* Enable overflow interrupt */
	TIMSK1 |= (1 << TOIE1);

	/* set the LED's GPIO to output mode */
	LEDDR |= (1 << LEDPIN);

	led_state = false;

	// enable interrupts globally
	sei();
}

int main(void) {
	init();

	/* do nothing, loop forever */
	while (1) {}
}

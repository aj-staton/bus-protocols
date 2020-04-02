/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/* This file includes supporting routines for your project. You should not
 * change anything in here.
 */

#ifndef SUPPORT_H
#define SUPPORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

/* The "clock rate" of the simulation. This exists purely to give meaning to
 * stuff like delay_ms and delay_us. */
#define CLOCK_RATE 1000000UL

/* conversion rates */
#define US_PER_SECOND 1000000L
#define MS_PER_SECOND 1000L
#define US_PER_CYCLE (US_PER_SECOND / CLOCK_RATE)
#define MS_PER_CYCLE (MS_PER_SECOND / CLOCK_RATE)
#define CYCLES_PER_US ( CLOCK_RATE / US_PER_SECOND)
#define CYCLES_PER_MS ( CLOCK_RATE / MS_PER_SECOND)

typedef struct {
	Vtop* top;
	VerilatedVcdC* vcd;
	uint64_t cycleno;
} simulation_state;

typedef enum {
	IO_CS,
	IO_SCK,
	IO_MISO,
	IO_MOSI
} simulation_io;

typedef enum {
	IO_CLOSED,
	IO_RDRW,
	IO_RO,
	IO_WO
} simulation_io_direction;

void delay_cycles(simulation_state* s, uint64_t cycles);
void delay_us(simulation_state* s, uint64_t us);
void delay_ms(simulation_state* s, uint64_t ms);
void reset(simulation_state* s);
int read_io(simulation_state* s, simulation_io io);
void write_io(simulation_state* s, simulation_io io, int val);
simulation_state* initialize_simulation(int argc, char** argv);

#define io_direction(__io) ( \
	(__io == IO_SCK)  ? IO_WO : \
	(__io == IO_CS)   ? IO_WO : \
	(__io == IO_MISO) ? IO_RO : \
	(__io == IO_MOSI) ? IO_WO : IO_CLOSED )

#define io2str(__io) \
	(__io == IO_SCK)  ? "sck" : \
	(__io == IO_CS)   ? "cs" : \
	(__io == IO_MISO) ? "miso" : \
	(__io == IO_MOSI) ? "mosi" : "ERROR UNKNOWN IO"

#define dir2str(__dir) \
	(__dir == IO_CLOSED) ? "closed" : \
	(__dir == IO_RDRW)   ? "read/write" : \
	(__dir == IO_RO)     ? "read only" : \
	(__dir == IO_WO)     ? "write only" : "ERROR UNKNOWN DIRECTION"

#define whereat do { \
		fprintf(stderr, "%s:%d:%s()", __FILE__, __LINE__, __func__); \
	} while(0);

#define assert_valid_io(__io) do { \
	if ( \
		(__io != IO_SCK) && \
		(__io != IO_CS) && \
		(__io != IO_MISO) && \
		(__io != IO_MOSI) \
		) { \
			fprintf(stderr, "ERROR: IO %i is unknown, should be one of: \n"); \
			fprintf(stderr, "\tIO_CS, IO_SCK, IO_MISO, IO_MOSI"); \
			fprintf(stderr, "previous error was near: "); \
			whereat; \
			fprintf(stderr, "\n"); \
			exit(1); \
		}\
	} while(0)

#define assert_writeable(__io) do { \
		if ((io_direction(__io) != IO_RDRW) && (io_direction(__io) != IO_WO)) { \
			fprintf(stderr, "ERROR: IO '%s' is not writeable (direction is '%s')\n", \
					io2str(__io), dir2str(io_direction(__io))); \
			fprintf(stderr, "previous error was near: "); \
			whereat; \
			fprintf(stderr, "\n"); \
			exit(1); \
		} \
	} while(0)

#define assert_readable(__io) do { \
		if ((io_direction(__io) != IO_RDRW) && (io_direction(__io) != IO_RO)) { \
			fprintf(stderr, "ERROR: IO '%s' is not readable (direction is '%s')\n", \
					io2str(__io), dir2str(io_direction(__io))); \
			fprintf(stderr, "previous error was near: "); \
			whereat; \
			fprintf(stderr, "\n"); \
			exit(1); \
		} \
	} while(0)


#endif

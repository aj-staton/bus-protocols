/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/* This file includes supporting routines for your project. You should not
 * change anything in here.
 */

#include "support.h"

/* Run the simulation the given number of cycles */
void delay_cycles(simulation_state* s, uint64_t cycles)  {

	while (cycles > 0) {
		s->top->eval();
		if (s->vcd) { s->vcd->dump(s->cycleno * 10 - 2); }
		s->top->clk = 1;
		s->top->eval();
		if (s->vcd) { s->vcd->dump(s->cycleno * 10); }
		s->top->clk = 0;
		s->top->eval();
		if (s->vcd) {
			s->vcd->dump(s->cycleno * 10 + 5);
			s->vcd->flush();
		}
		cycles --;
		s->cycleno++;
	}
}

void delay_us(simulation_state* s, uint64_t us) {
	delay_cycles(s, CYCLES_PER_US * us);
}

void delay_ms(simulation_state* s, uint64_t ms) {
	delay_cycles(s, CYCLES_PER_MS * ms);
}

/* Perform a reset. This will run the simulation for 3 cycles. */
void reset(simulation_state* s) {
	delay_cycles(s, 1);
	s->top->rst = 1;
	delay_cycles(s, 1);
	s->top->rst = 0;
	delay_cycles(s, 1);
}

/* Read the specified I/O */
int read_io(simulation_state* s, simulation_io io) {
	assert_valid_io(io);
	assert_readable(io);

	if (io == IO_CS1) {
		return s->top->cs1;
	} else if (io == IO_CS2) {
		return s->top->cs2;
	} else if (io == IO_SCK) {
		return s->top->sck;
	} else if (io == IO_MISO) {
		return s->top->miso;
	} else if (io == IO_MOSI) {
		return s->top->mosi;
	}
}

/* Write to the specified I/O */
void write_io(simulation_state* s, simulation_io io, int val) {
	assert_valid_io(io);
	assert_writeable(io);

	if (io == IO_CS1) {
		s->top->cs1 = val;
	} else if (io == IO_CS2) {
		s->top->cs2 = val;
	} else if (io == IO_SCK) {
		s->top->sck = val;
	} else if (io == IO_MISO) {
		s->top->miso = val;
	} else if (io == IO_MOSI) {
		s->top->mosi = val;
	}
}

simulation_state* initialize_simulation(int argc, char** argv) {
        Verilated::commandArgs(argc, argv);
	simulation_state* s = (simulation_state*) malloc(sizeof(simulation_state));
	s->top = new Vtop;
	Verilated::traceEverOn(true);
	s->vcd = new VerilatedVcdC;
	s->top->trace(s->vcd, 99);
	s->vcd->open("trace.vcd");
	s->cycleno = 1;
	write_io(s, IO_CS1, 1);
	write_io(s, IO_CS2, 1);
	write_io(s, IO_SCK, 0);
	write_io(s, IO_MOSI, 0);

	reset(s);
	delay_cycles(s, 50);
	return s;
}

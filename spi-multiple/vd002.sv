/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/*
 * Hardware implementation of the VD-002 simulated sensor.
 */

module vd002 (
	input logic clk,
	input logic rst, /* active high, synchronous */
	input logic cs,
	input logic sck,
	input logic mosi,
	output logic miso);

`define ADDR_WHO_AM_I 8'h0f
`define ADDR_DATA 8'h10
`define ADDR_DATACNT 8'h11
`define RESP_ERROR 8'hee
`define RESP_WHO_AM_I 8'h35

logic spi0_rx_dv;
logic [7:0] spi0_rx;
logic spi0_tx_dv;
logic [7:0] spi0_tx;
/* verilator lint_off MULTIDRIVEN */
logic tx_done;
/* verilator lint_on MULTIDRIVEN */

SPI_Slave #(.SPI_MODE(3)) spi0(
	.i_Rst_L(~rst),
	.i_Clk(clk),
	.o_RX_DV(spi0_rx_dv),
	.o_RX_Byte(spi0_rx),
	.i_TX_DV(spi0_tx_dv),
	.i_TX_Byte(spi0_tx),
	.i_SPI_Clk(sck),
	.o_SPI_MISO(miso),
	.i_SPI_MOSI(mosi),
	.i_SPI_CS_n(cs));

logic [7:0] regaddr;
logic [7:0] regresp;
logic [2:0] readcnt;
logic [7:0] streamlen;
logic [12:0] dataidx;
logic stream_firstbyte;

/* The sensor data is internally stored as a linear array of one-byte values,
 * containing end-to-end packed streams. The first byte of each stream is the
 * stream length, and the remaining bytes are the stream contents.  A stream
 * length of 0 means that we should wrap back to the beginning of the
 * sensordata array.
 *
 * For example, this sensordata array:
 *
 * 0x02 0x00 0xb4 0x03 0x01 0xf7 0xab 0x00
 *
 * Signifies that the first stream is of length 2, and contains the bytes
 * 0x00 and 0xb4 in that order, and the second stream is of length 3 and
 * contains the bytes 0x01, 0xf7, 0xab in that order.
 */
logic [7:0] sensordata [8191:0];
initial begin
	$readmemh("sensordata.hex", sensordata);
	dataidx = 0;
end

/* States */

enum logic [1:0] {
	STATE_IDLE,
	STATE_RX_ADDR,
	STATE_TX_DATA_SINGLE,
	STATE_TX_DATA_STREAM
} sensor_state;

initial begin
	sensor_state = STATE_IDLE;
	spi0_tx_dv = 1'b0;
	regaddr = 8'b0;
	regresp = 8'b0;
	tx_done = 0;
	stream_firstbyte = 0;
end

always @(negedge clk) begin
	/* verilator lint_off MULTIDRIVEN */
	tx_done <= spi0_rx_dv;
	/* verilator lint_on MULTIDRIVEN */
end

always @(posedge clk) begin

	if (rst) begin
		spi0_tx_dv <= 1'b0;
		regaddr <= 8'b0;
		regresp <= 8'b0;
		readcnt <= 3'b0;

	end else if (cs == 1) begin

		/* If CS isn't held down, go ahead and drop all the data in
		 * the current stream */
		/* verilator lint_off SYNCASYNCNET */
		if (sensor_state == STATE_TX_DATA_STREAM) begin
			dataidx <= dataidx + {5'b0, streamlen};
			streamlen <= 0;
			sensor_state <= STATE_IDLE;
		end
		/* verilator lint_on SYNCASYNCNET */

	end else  if (sensor_state == STATE_IDLE) begin

		/* default case, keep everything blanked out */
		spi0_tx_dv <= 1'b0;
		regaddr <= 8'b0;
		regresp <= 8'b0;

		/* until we get a data valid pulse from the SPI core */
		if (spi0_rx_dv) begin
			regaddr <= spi0_rx;
			sensor_state <= STATE_RX_ADDR;
		end

	end else if (sensor_state == STATE_RX_ADDR) begin

		/* WHO_AM_I */
		if (regaddr == `ADDR_WHO_AM_I) begin
			regresp <= `RESP_WHO_AM_I;
			sensor_state <= STATE_TX_DATA_SINGLE;

		/* read sensor data */
		end else if (regaddr == `ADDR_DATA) begin
			readcnt <= readcnt + 1;
			streamlen <= sensordata[dataidx];
			dataidx <= dataidx + 1;
			stream_firstbyte <= 1;
			sensor_state <= STATE_TX_DATA_STREAM;

		/* read DATACNT */
		end else if (regaddr == `ADDR_DATACNT) begin
			regresp <= sensordata[dataidx];
			sensor_state <= STATE_TX_DATA_SINGLE;

		/* error */
		end else begin
			regresp <= `RESP_ERROR;
			sensor_state <= STATE_IDLE;
		end

	end else if (sensor_state == STATE_TX_DATA_SINGLE) begin

		/* transmit response */
		spi0_tx <= regresp;
		spi0_tx_dv <= 1'b1;
		sensor_state <= STATE_IDLE;

	end else if (sensor_state == STATE_TX_DATA_STREAM) begin

		if (tx_done || stream_firstbyte) begin
			spi0_tx <= sensordata[dataidx];
			spi0_tx_dv <= 1'b1;
			streamlen <= streamlen - 1;

			/* look ahead to see if we're about to fall off the end */
			if ((streamlen - 1 == 0) && (sensordata[dataidx+1] == 0)) begin
				dataidx <= 0;
			end else begin
				dataidx <= dataidx + 1;
			end

			if (streamlen - 1 == 0) begin
				sensor_state <= STATE_IDLE;
			end else begin
				sensor_state <= STATE_TX_DATA_STREAM;
			end

			/* verilator lint_off MULTIDRIVEN */
			tx_done <= 0;
			/* verilator lint_on MULTIDRIVEN */
			stream_firstbyte <= 0;
		end

	end else begin

		/* this should not happen */
		sensor_state <= STATE_IDLE;

	end

end

endmodule

`undef ADDR_WHO_AM_I
`undef ADDR_DATA
`undef ADDR_DATACNT
`undef RESP_ERROR
`undef RESP_WHO_AM_I

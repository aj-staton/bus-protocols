/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/*
 * This module implement a simple "sensor" which implement an SPI slave with
 * two registers: a WHO_AM_I register, and a DATA register. The DATA register
 * will return a sensor "reading". This is arbitrary; internally the readings
 * are just a repeating pattern of values.
 *
 * Note for students: the sensor "readings" hard-coded in this will be changed
 * during grading, so don't hard-code anything based on them them!
 *
 * The memory map of this sensor is as follows:
 *
 * address 0x0F: WHO_AM_I register, always returns 0x34
 *
 * address 0x10: DATA register, returns the sensor reading
 *
 * The protocol to read a register is as follows:
 *
 * * Transmit the 1-byte register address.
 *
 * * The 1-byte register contents will be returned.
 *
 * This sensor does not include any write-able registers.
 *
 * When an invalid register address is read, the return value is defined to
 * be 0xEE.
 *
 * Note that if a further data byte is transmitted before the transaction is
 * completed, it will be dropped. However this is very unlikely to happen.
 */

module sensor(
	input logic clk,
	input logic rst, /* active high, synchronous */
	input logic cs,
	input logic sck,
	input logic mosi,
	output logic miso);

`define ADDR_WHO_AM_I 8'h0f
`define ADDR_DATA 8'h10
`define RESP_ERROR 8'hee
`define RESP_WHO_AM_I 8'h34

logic spi0_rx_dv;
logic [7:0] spi0_rx;
logic spi0_tx_dv;
logic [7:0] spi0_tx;

SPI_Slave #(.SPI_MODE(0)) spi0(
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
logic [7:0] sensorval;

/* "random" values */
assign sensorval = (readcnt == 3'b000) ? 8'd7 :
	(readcnt == 3'b001) ? 8'd85 :
	(readcnt == 3'b010) ? 8'd161 :
	(readcnt == 3'b011) ? 8'd240 :
	(readcnt == 3'b100) ? 8'd36 :
	(readcnt == 3'b101) ? 8'd49 :
	(readcnt == 3'b110) ? 8'd204 :
	(readcnt == 3'b111) ? 8'd10 : 8'd193;

/* States */

enum logic [1:0] {
	STATE_IDLE,
	STATE_RX_ADDR,
	STATE_TX_DATA
} sensor_state;

initial begin
	sensor_state = STATE_IDLE;
	spi0_tx_dv = 1'b0;
	regaddr = 8'b0;
	regresp = 8'b0;
end

always @(posedge clk) begin

	if (rst) begin
		spi0_tx_dv <= 1'b0;
		regaddr <= 8'b0;
		regresp <= 8'b0;
		readcnt <= 3'b0;

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

		/* read sensor data */
		end else if (regaddr == `ADDR_DATA) begin
			regresp <= sensorval;
			readcnt <= readcnt + 1;

		/* error */
		end else begin
			regresp <= `RESP_ERROR;
		end
		sensor_state <= STATE_TX_DATA;

	end else if (sensor_state == STATE_TX_DATA) begin

		/* transmit response */
		spi0_tx <= regresp;
		spi0_tx_dv <= 1'b1;
		sensor_state <= STATE_IDLE;

	end else begin

		/* this should not happen */
		sensor_state <= STATE_IDLE;

	end

end

endmodule

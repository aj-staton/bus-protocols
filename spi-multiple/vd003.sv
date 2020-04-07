/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

/*
 * Hardware implementation of the VD-003 flash memory.
 */

module vd003 (
	input logic clk,
	input logic rst, /* active high, synchronous */
	input logic cs,
	input logic sck,
	input logic mosi,
	output logic miso);

`define ADDR_WHO_AM_I 8'h0f
`define ADDR_NPAGE 8'h01
`define ADDR_PAGESEL 8'h10
`define ADDR_OFFSET 8'h11
`define ADDR_DATA 8'h12
`define RESP_ERROR 8'hee
`define RESP_WHO_AM_I 8'h36

logic spi0_rx_dv;
logic [7:0] spi0_rx;
logic spi0_tx_dv;
logic [7:0] spi0_tx;

`define NPAGES 32
`define NADDR 8191

logic [7:0] page;
logic [7:0] offset;
logic [7:0] data[`NADDR:0];
/* verilator lint_off UNUSED */
logic [15:0] dataaddr;
/* verilator lint_on UNUSED */
assign dataaddr = {page, offset};

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
logic [7:0] effaddr;
logic wren;
logic [7:0] regresp;

/* This is used so we can revue the values written to flash via the trace
* later. */
/* verilator lint_off UNUSED */
logic data_wren;
logic [7:0] data_value;
/* verilator lint_on UNUSED */

assign wren = regaddr[7];
assign effaddr = {1'b0, regaddr[6:0]};

/* States */
enum logic [2:0] {
	STATE_IDLE,
	STATE_RX_ADDR,
	STATE_TX_DATA_SINGLE,
	STATE_WRITE_PAGSEL,
	STATE_WRITE_OFFSET,
	STATE_WRITE_DATA
} flash_state;

initial begin
	flash_state = STATE_IDLE;
	spi0_tx_dv = 1'b0;
	regaddr = 8'b0;
	regresp = 8'b0;
	page = 0;
	offset = 0;
end

always @(posedge clk) begin

	data_wren <= 0;

	if (rst) begin
		spi0_tx_dv <= 1'b0;
		regaddr <= 8'b0;
		regresp <= 8'b0;

	end else  if (flash_state == STATE_IDLE) begin

		/* default case, keep everything blanked out */
		spi0_tx_dv <= 1'b0;
		regaddr <= 8'b0;
		regresp <= 8'b0;

		/* until we get a data valid pulse from the SPI core */
		if (spi0_rx_dv) begin
			regaddr <= spi0_rx;
			flash_state <= STATE_RX_ADDR;
		end

	end else if (flash_state == STATE_RX_ADDR) begin

		/* WHO_AM_I */
		if (effaddr == `ADDR_WHO_AM_I) begin
			regresp <= `RESP_WHO_AM_I;
			flash_state <= STATE_TX_DATA_SINGLE;

		/* read NPAGES */
		end else if (effaddr == `ADDR_NPAGE) begin
			regresp <= `NPAGES;
			flash_state <= STATE_TX_DATA_SINGLE;

		/* write PAGESEL */
		end else if ((effaddr == `ADDR_PAGESEL) && (wren == 1)) begin
			flash_state <= STATE_WRITE_PAGSEL;

		/* read PAGESEL */
		end else if ((effaddr == `ADDR_PAGESEL) && (wren == 0)) begin
			flash_state <= STATE_TX_DATA_SINGLE;
			regresp <= page;

		/* write OFFSET */
		end else if ((effaddr == `ADDR_OFFSET) && (wren == 1)) begin
			flash_state <= STATE_WRITE_OFFSET;

		/* read OFFSET */
		end else if ((effaddr == `ADDR_OFFSET) && (wren == 0)) begin
			flash_state <= STATE_TX_DATA_SINGLE;
			regresp <= offset;

		/* write DATA */
		end else if ((effaddr == `ADDR_DATA) && (wren == 1)) begin
			flash_state <= STATE_WRITE_DATA;

		/* read DATA */
		end else if ((effaddr == `ADDR_DATA) && (wren == 0)) begin
			flash_state <= STATE_TX_DATA_SINGLE;
			regresp <= data[dataaddr[12:0]];

		/* error */
		end else begin
			regresp <= `RESP_ERROR;
			flash_state <= STATE_IDLE;
		end

	end else if (flash_state == STATE_TX_DATA_SINGLE) begin

		/* transmit response */
		spi0_tx <= regresp;
		spi0_tx_dv <= 1'b1;
		flash_state <= STATE_IDLE;

	end else if (flash_state == STATE_WRITE_PAGSEL) begin

		if (spi0_rx_dv) begin
			page <= spi0_rx;
			flash_state <= STATE_IDLE;
		end

	end else if (flash_state == STATE_WRITE_OFFSET) begin

		if (spi0_rx_dv) begin
			offset <= spi0_rx;
			flash_state <= STATE_IDLE;
		end

	end else if (flash_state == STATE_WRITE_DATA) begin

		if (spi0_rx_dv) begin
			data_wren <= 1;
			data_value <= spi0_rx;
			data[dataaddr[12:0]] <= spi0_rx;
			flash_state <= STATE_IDLE;
		end

	end else begin

		/* this should not happen */
		flash_state <= STATE_IDLE;

	end

end

endmodule

`undef ADDR_WHO_AM_I
`undef ADDR_NPAGE
`undef ADDR_PAGESEL
`undef ADDR_OFFSET
`undef ADDR_DATA
`undef RESP_ERROR
`undef RESP_WHO_AM_I

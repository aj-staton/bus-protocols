/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

module top(
	input logic clk,
	input logic rst,
	input logic cs1,
	input logic cs2,
	input logic sck,
	input logic mosi,
	output logic miso);

vd002 sensor0 (
	.clk(clk),
	.rst(rst),
	.cs(cs1),
	.sck(sck),
	.mosi(mosi),
	.miso(miso)
);

vd003 flash0(
	.clk(clk),
	.rst(rst),
	.cs(cs2),
	.sck(sck),
	.mosi(mosi),
	.miso(miso)
);

endmodule

/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

module top(
	input logic clk,
	input logic rst,
	input logic cs,
	input logic sck,
	input logic mosi,
	output logic miso);

sensor sensor0 (
	.clk(clk),
	.rst(rst),
	.cs(cs),
	.sck(sck),
	.mosi(mosi),
	.miso(miso)
);

endmodule

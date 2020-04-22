/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

`timescale 1ns/1ps

module top (
`ifndef TESTBENCH_MODE
	input logic clk,input logic rst,
	input logic sda_i,scl_i,
`endif
	output logic sda,scl);

	logic		sda_o2,scl_o2;
	logic 		sda_t2,scl_t2;

	logic		sda_t1,scl_t1;
	logic		sda_o1,scl_o1;

    logic       release_bus;

	/*
	 * The following are signals to read and write parallel data to
	   the I2C slave.
	*/
    logic [7:0]  data_in;
    logic        data_in_valid;
    logic        data_in_ready;
    logic        data_in_last;

    logic [7:0]  data_out;
    logic        data_out_valid;
    logic        data_out_ready;
    logic        data_out_last;

    /*
     * Status
     */
    logic        busy;
    logic [6:0]  bus_address;
    logic        bus_addressed;
    logic        bus_active;

    /*
     * Configuration
     */
    logic        enable;
    logic [6:0]  device_address;
    logic [6:0]  device_address_mask;
	assign device_address = 7'b0011000;
	assign enable = 1'b1;

	// 8 device addresses
	assign device_address_mask = 7'b1111000;
	assign release_bus = 1'b0;

	/*
	 * this is an internal testbench for the I2C Slave
	 */
`ifdef TESTBENCH_MODE
`include "i2c_slave_tb.sv"
`endif

	assign data_out_ready = 1'b1;

	assign data_in_last = 1'b1;

	assign scl = ~scl_t1 ? scl_o1 :
				 ~scl_t2 ? scl_o2 :
				 scl_i;
	assign sda = ~sda_t1 ? sda_o1 :
				 ~sda_t2 ? sda_o2 :
				 sda_i;

	logic initiate;
	
	// monitor for incoming reads
	always @(posedge clk) begin
		if (rst) initiate <= 1'b0;
		data_in_valid <= 1'b0;
		data_in <= 8'h0;
		if (data_in_ready) begin
			data_in_valid <= 1'b1;
			case (bus_address[2:0])
			// WHO_AM_I
			3'b100: // WHO_AM_I: address 0x1C (001 1100)
				data_in <= 8'h36;
			3'b101: // NPAGE: address 0x1D (001 1101)
				// when reading NPAGE, enable the i2c master
				// by setting initiate flag
				begin
					data_in <= 8'h3;
					initiate <= 1'b1;
				end

			3'b110: // PAGESEL: address 0x1E (001 1110)
				data_in <= 8'h00; // (don't read this)
			3'b111: // DATA: address 0x1F (001 1111)
				data_in <= 8'h00; // (don't read this)
			endcase
		end
	end

	// the following logic will translate writes into a format
	// that Charles's Python script can understand
	logic [7:0] page,offset;
	(* KEEP="TRUE" *) logic data_wren;
	(* KEEP="TRUE" *) logic [15:0] dataaddr;
	(* KEEP="TRUE" *) logic [7:0] data_value;
	assign data_value = data_out;
	assign dataaddr = {page,offset};
	assign data_wren = data_out_valid && bus_address==8'h1F;
	always @(posedge clk) begin
		if (data_out_valid && bus_address==8'h1b) begin
			offset <= 8'b0;
			page <= data_out;
		end else if (data_out_valid && bus_address==8'h1F) begin
			offset <= offset + 8'b1;
		end
	end

	i2c_slave #(.FILTER_LEN(1)) myslave(	.clk(clk),
						.rst(rst),
						.release_bus(release_bus),		// input

						.data_in(data_in),				// input
						.data_in_valid(data_in_valid),	// input
						.data_in_ready(data_in_ready),	// output
						.data_in_last(data_in_last),	// input

						.data_out(data_out),			// output
						.data_out_valid(data_out_valid),// output
						.data_out_ready(data_out_ready),// input
						.data_out_last(data_out_last),	// output

						.scl_i(scl_i),					// input
						.scl_o(scl_o2),					// output
						.scl_t(scl_t2),					// output
						.sda_i(sda_i),					// input
						.sda_o(sda_o2),					// output
						.sda_t(sda_t2),					// output

						.busy(busy),					// output
						.bus_address(bus_address),		// output (?)
						.bus_addressed(bus_addressed),	// output
						.bus_active(bus_active),		// output

						.enable(enable),				// input
						.device_address(device_address),// input
						.device_address_mask(device_address_mask) // input
	);

	// instantiate the master
	i2c_master mymaster (.clk(clk),
				.rst(rst),
				.initiate(initiate),
				.sda_i(sda_i),
				.scl_i(scl_i),
				.sda_o(sda_o1),
				.scl_o(scl_o1),
				.sda_t(sda_t1),
				.scl_t(scl_t1));

endmodule

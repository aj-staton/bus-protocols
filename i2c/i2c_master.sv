/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

module i2c_master (input logic clk,
				   input logic rst,
				   input logic initiate,
				   input logic sda_i,
				   input logic scl_i,
				   output logic sda_o,
				   output logic scl_o,
				   output logic sda_t,
				   output logic scl_t);

	// parameters

	// number of cycles between I2C master transactions
	parameter idle_time = 32'd200;

	// number of sensor payloads
	parameter PAYLOADS = 4;

	// slave I2C address
	parameter [6:0] slave_address_datacnt = 7'h7A;

	// payload sizes
	parameter [7:0] payload_sizes [0:PAYLOADS-1] = '{8'd4, 8'd5, 8'd7, 8'd9};

	// i2c data
	// NOTE: must allocate statically because Verilator does not support
	// SystemVerilog dynamic arrays
	logic [7:0] i2c_data [0:28]; // 5+6+8+10

	// the current value being transmitted
	logic [31:0] index;

	integer data_size = 0;

	// initialize sensor payloads
	initial begin
		// $srandom(42); // I don't understand why this causes a compile errror
		integer i,j,n;
		// calculate total size of I2C data
		for (i=0;i<PAYLOADS;i=i+1) begin
			data_size = data_size + payload_sizes[i]+8'b1;
		end
		// dynamic allocation
		// i2c_data = new[data_size]; // bad Verilator!!!

		n = 0;
		for (i=0;i<PAYLOADS;i=i+1) begin
			i2c_data[n] = payload_sizes[i];
			n=n+1;
			for (j=0;j<payload_sizes[i];j=j+1) begin
				//i2c_data[n] = $urandom_range(0,255);// damn Verilator
				i2c_data[n] = $random;
				n=n+1; 
			end
		end
	end

	// timer to implement idle time between sensor readings
	logic [31:0] global_timer;

	// timers to synchornize I2C master operation
	logic [31:0] timer;
	logic rst_timer;
	logic [2:0] bitcounter;
	logic rst_bitcounter;
	logic en_bitcounter;

	// counters to keep track of clock pulses and data serialization
	always @(posedge clk) begin
		// the global timer is useful for debugging synchronization
		// between the software and hardware
		if (rst)
			global_timer<=32'b0;
		else
			global_timer<=global_timer+32'b1;

		// the timer is used to make the I2C clock
		if (rst_timer)
			timer<=32'b0;
		else
			timer<=timer+32'b1;

		// the bitcounter is used for state changes
		if (rst_bitcounter)
			bitcounter<=32'b0;
		else
			if (en_bitcounter)
				bitcounter<=bitcounter+3'b1;
	end

	/*
     * states:
	 * TODO: need a way to reuse these states for sending both the datacnt
     * and the data itself.
	 */
	typedef enum {idle,
				  waiting,
				  start_datacnt,
				  send_datacnt_address,
				  send_datacnt_write,
				  get_datacnt_address_ack,
				  send_datacnt,
				  get_datacnt_ack,
				  stop_datacnt,
				  start_sensor,
				  send_sensoraddress,
				  send_sensorval,
				  stop_sensorval} state_type;

	state_type current_state,next_state;

	// clocked process
	always @(posedge clk, posedge rst) begin
		if (rst) begin
			current_state <= idle;
			index <= 32'b0;
		end else begin
			current_state <= next_state;
			if (current_state==stop_datacnt && next_state==idle) begin
				index <= index + 32'b1;
				//$display("index=%d, data=%02X\n",index+32'b1,i2c_data[index+32'b1]);
			end
		end
	end

	// next state logic
	always_comb begin
		next_state = current_state;
		case (current_state)
			idle: if (initiate) next_state = waiting;

			waiting:
				if (timer==idle_time)
					next_state = start_datacnt;

			start_datacnt:
				next_state = send_datacnt_address;

			send_datacnt_address:
				if (timer==32'd2 && bitcounter==3'd6)
					next_state = send_datacnt_write;

			send_datacnt_write:
				if (timer==32'd2)
					next_state = get_datacnt_address_ack;

			get_datacnt_address_ack:
				if (timer==32'd2)
					next_state = send_datacnt;

			send_datacnt:
				if (timer==32'd2 && bitcounter==3'd7)
					next_state = get_datacnt_ack;

			get_datacnt_ack:
				if (timer==32'd2)
					next_state = stop_datacnt;

			stop_datacnt:
				if (timer==32'd2)
					next_state = idle;
		endcase
	end

	// output logic
	always_comb begin
		scl_o = 1'b1;
		scl_t = 1'b1;
		sda_o = 1'b1;
		sda_t = 1'b1;

		rst_timer=1'b0;
		rst_bitcounter=1'b0;
		en_bitcounter=1'b0;
		case (current_state)
			idle: rst_timer=1'b1;

			start_datacnt: begin
				rst_timer=1'b1;
				rst_bitcounter=1'b1;
				sda_o = 1'b0;
				sda_t = 1'b0;
			end

			send_datacnt_address: begin
				scl_t = 1'b0;
				if (timer==32'd2) begin
					rst_timer=1'b1;
					en_bitcounter=1'b1;
				end
				if (timer==32'd1)
					scl_o = 1'b1;
				else
					scl_o = 1'b0;
				sda_o = slave_address_datacnt[3'd6-bitcounter];
				sda_t = 1'b0;
			end

			send_datacnt_write: begin
				scl_t = 1'b0;
				if (timer==32'd2) begin
					rst_timer=1'b1;
					en_bitcounter=1'b1;
				end
				sda_o = 1'b0;
				sda_t = 1'b0;
				if (timer==32'd1)
					scl_o = 1'b1;
				else
					scl_o = 1'b0;
			end
	
			get_datacnt_address_ack: begin
				scl_t = 1'b1;
				if (timer==32'd2) begin
					rst_timer=1'b1;
					en_bitcounter=1'b1;
				end
				rst_bitcounter=1'b1;
				sda_o = 1'b1;
				sda_t = 1'b1;
				if (timer==32'd1)
					scl_o = 1'b1;
				else
					scl_o = 1'b0;
			end

			send_datacnt: begin
				scl_t = 1'b0;
				if (timer==32'd2) begin
					rst_timer=1'b1;
					en_bitcounter=1'b1;
				end
				if (timer==32'd1)
					scl_o = 1'b1;
				else
					scl_o = 1'b0;
				sda_o = i2c_data[index][3'd7-bitcounter];
				sda_t = 1'b0;
			end

			get_datacnt_ack: begin
				scl_t = 1'b1;
				if (timer==32'd2) begin
					rst_timer=1'b1;
					en_bitcounter=1'b1;
				end
				sda_o = 1'b1;
				sda_t = 1'b1;
				if (timer==32'd1)
					scl_o = 1'b1;
				else
					scl_o = 1'b0;
			end

			stop_datacnt: begin
				scl_t = 1'b0;
				sda_t = 1'b0;
				case (timer)
				32'b0: begin
					scl_o = 1'b0;
					sda_o = 1'b0;
				end
				32'b1: begin
					scl_o = 1'b1;
					sda_o = 1'b0;
				end
				default: begin
					scl_o = 1'b1;
					sda_o = 1'b1;
				end
				endcase
			end

		endcase
	end

endmodule


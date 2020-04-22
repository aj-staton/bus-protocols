/* Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels */

	logic sda_i,scl_i;
	logic clk,rst;

	int i;

	logic [6:0] trans_addr;
	logic [7:0] trans_word;

	always begin
		clk=1'b0;
		#5;
		clk=1'b1;
		#5;
	end

	initial begin
		$wlfdumpvars(0,top);
		rst=1'b1;
		#10;
		rst=1'b0;
	end

	// master side!
	initial begin
		scl_i = 1'b1;
		sda_i = 1'b1;
		#10;

		// transaction 1:  write value E7
		trans_word = 8'h33;
		trans_addr = 7'hC;

		// start signal
		sda_i = 1'b0;
		#10;
		scl_i = 1'b0;
		#10;

		// write address
		for (i=6;i>=0;i=i-1) begin
			sda_i = trans_addr[i];
			#20;
			scl_i = 1'b1;
			#20;
			scl_i = 1'b0;
			#20;
		end

		sda_i = 1'b0; // R/W bit (0 to write)
		#20;
		scl_i = 1'b1; // clock pulse
		#20;
		scl_i = 1'b0;
		#20;
		
		sda_i = 1'b0; // blank bit (sda_o should acknowledge here)
		#20;
		scl_i = 1'b1; // clock pulse
		#20;
		scl_i = 1'b0;
		#20;

		// write data
		for (i=7;i>=0;i=i-1) begin
			sda_i = trans_word[i];
			#20;
			scl_i = 1'b1;
			#20;
			scl_i = 1'b0;
			#20;
		end

		sda_i = 1'b0; // blank bit (sda_o should acknowledge here)
		#20;
		scl_i = 1'b1; // clock pulse
		#20;
		scl_i = 1'b0;
		#20;

		scl_i = 1'b1; // end transmission
		#20;
		sda_i = 1'b1;
		#20;
		
		// transaction 2:  read
		// start signal
		sda_i = 1'b0;
		#10;
		scl_i = 1'b0;
		#10;

		// read address
		for (i=6;i>=0;i=i-1) begin
			sda_i = trans_addr[i];
			#20;
			scl_i = 1'b1;
			#20;
			scl_i = 1'b0;
			#20;
		end

		sda_i = 1'b1; // R/W bit (1 to read)
		#20;
		scl_i = 1'b1; // clock pulse
		#20;
		scl_i = 1'b0;
		#20;
		
		sda_i = 1'b0; // blank bit (sda_o should acknowledge here)
		#20;
		scl_i = 1'b1; // clock pulse
		#20;
		scl_i = 1'b0;
		#20;

		// read data
		for (i=7;i>=0;i=i-1) begin
			sda_i = 1'b1;
			#20;
			scl_i = 1'b1;
			#20;
			scl_i = 1'b0;
			#20;
		end

		sda_i = 1'b0; // blank bit (sda_o should acknowledge here)
		#20;
		scl_i = 1'b1; // clock pulse
		#20;
		scl_i = 1'b0;
		#20;

		scl_i = 1'b1; // end transmission
		#20;
		sda_i = 1'b1;
		#20;
	end


module i2c_master_tb;

	logic clk,rst,scl_i,scl_o,scl_t,sda_i,sda_o,sda_t;

	i2c_master dut (.clk(clk),
					.rst(rst),
					.scl_i(scl_i),
					.scl_o(scl_o),
					.scl_t(scl_t),
					.sda_i(sda_i),
					.sda_o(sda_o),
					.sda_t(sda_t));

	initial begin
		rst<=1'b1;
		#20;
		rst=1'b0;
	end

	always begin
		clk=1'b1;
		#5;
		clk=1'b0;
		#5;
	end

	

endmodule


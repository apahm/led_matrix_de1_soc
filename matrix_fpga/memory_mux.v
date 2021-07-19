`timescale 1 ps / 1 ps


module memory_mux (
	
	output wire [47:0] 	slave_0_dist_out,
   	input wire 	[9:0] 	slave_0_dist_address,
	input wire 	[47:0] 	slave_0_dist_data,
	input wire 			slave_0_write_enable,
	input wire 			slave_0_dist_clk, 

	output wire [47:0] 	slave_1_dist_out,
   	input wire 	[9:0] 	slave_1_dist_address,
	input wire 	[47:0] 	slave_1_dist_data,
	input wire 			slave_1_write_enable,
	input wire 			slave_1_dist_clk,  


	input wire  [47:0] 	master_dist_out,
   	output wire [9:0] 	master_dist_address,
	output wire [47:0] 	master_dist_data,
	output wire 		master_write_enable,
	output wire 		master_dist_clk,

	input wire mux

);

assign master_dist_address = mux ? (slave_1_dist_address) : (slave_0_dist_address);
assign master_dist_data = mux ? (slave_1_dist_data) : (slave_0_dist_data);
assign master_write_enable = mux ? (slave_1_write_enable) : (slave_0_write_enable);
assign master_dist_clk = mux ? (slave_1_dist_clk) : (slave_0_dist_clk);


assign slave_0_dist_out = mux ? (0) : (master_dist_out);
assign slave_1_dist_out = 0;

endmodule
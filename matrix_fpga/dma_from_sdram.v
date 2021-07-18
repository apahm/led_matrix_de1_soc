`timescale 1 ps / 1 ps


module dma_from_sdram
(
    input wire clk,
    input wire rst,
    
	input wire start,
	input wire [28:0] begin_address,
	input wire [31:0] size_buffer,

	output  wire [28:0] sdram0_data_address,          
	input wire        sdram0_data_waitrequest,        
	input wire [63:0] sdram0_data_readdata,           
	input wire        sdram0_data_readdatavalid,      
	output  wire        sdram0_data_read,
	output wire [7:0] sdram0_data_burstcount,


	output wire [9:0] dist_address,
	output wire [11:0] dist_data,
	output wire write_enable,
	output wire dist_clk  

);


   	parameter IDLE = 3'b00;
   	parameter READ_FROM_SDRAM = 3'b01;
   	parameter WAIT_RESPONSE_FROM_SDRAM = 3'b10;
   	parameter WRITE_TO_DIST_ONE = 3'b011;
   	parameter WRITE_TO_DIST_TWO = 3'b100;
   	parameter WRITE_TO_DIST_THREE = 3'b101;
   	parameter WRITE_TO_DIST_FOUR = 3'b110;

  	reg [2:0] state = IDLE;

	reg [63:0] read_data_from_sdram;
	reg [28:0] reg_address;
	

	reg [11:0] reg_dist_data;
   	reg [9:0]  reg_dist_address;
    
	reg [31:0] reg_count_size;

	assign sdram0_data_address = reg_address;
   	assign sdram0_data_read = (state == READ_FROM_SDRAM);
    assign sdram0_data_burstcount = 1'b1;
	 
   
    assign dist_address = reg_dist_address;
    assign dist_clk = clk;
	assign dist_data = reg_dist_data;	
	 	
	  	 
	assign write_enable = (state == WRITE_TO_DIST_ONE) || (state == WRITE_TO_DIST_TWO) || (state == WRITE_TO_DIST_THREE) || (state == WRITE_TO_DIST_FOUR);

   	always @(posedge clk)
      	if (rst == 1'b1) begin
        	state <= IDLE;
        	read_data_from_sdram <= 0;
        	reg_address <= 0;
        	reg_dist_address <= 0;
			reg_count_size <= 0;
      	end
      	else
         	case (state)
			 	IDLE : begin
            		if (start) begin
            			state <= READ_FROM_SDRAM;
						reg_address <= begin_address;
						reg_dist_address <= 0;
					end
            		else 
		            	state <= IDLE;
            	end
            	READ_FROM_SDRAM : begin
               		if (sdram0_data_waitrequest == 1'b0) begin 
            			state <= WAIT_RESPONSE_FROM_SDRAM;
					   end
               		else begin
                		state <= READ_FROM_SDRAM;
					   end
            		end
            	WAIT_RESPONSE_FROM_SDRAM : begin
            	    if (sdram0_data_readdatavalid == 1'b1) begin 
            			state <= WRITE_TO_DIST_ONE;
						reg_count_size <= reg_count_size + 1;
						reg_address <= reg_address + 1;
						read_data_from_sdram <= sdram0_data_readdata;
					   end
               		else begin
                		state <= WAIT_RESPONSE_FROM_SDRAM;
					   end
            		end
            	WRITE_TO_DIST_ONE : begin
					reg_dist_address <= reg_dist_address + 1;
					state <= WRITE_TO_DIST_TWO;
				end
				WRITE_TO_DIST_TWO : begin
					reg_dist_address <= reg_dist_address + 1;
					state <= WRITE_TO_DIST_THREE;
				end
				WRITE_TO_DIST_THREE : begin
					reg_dist_address <= reg_dist_address + 1;
					state <= WRITE_TO_DIST_FOUR;
				end
				WRITE_TO_DIST_FOUR : begin
					reg_dist_address <= reg_dist_address + 1;
					if(reg_count_size == size_buffer)
						state <= IDLE;
					else
						state <= READ_FROM_SDRAM;
				end
         	endcase
			
	always@(*)
	begin
	      case(state)
			3'b011 : reg_dist_data <= read_data_from_sdram[11:0];
			3'b100 : reg_dist_data <= read_data_from_sdram[27:16];
			3'b101 : reg_dist_data <= read_data_from_sdram[43:32];
			3'b110 : reg_dist_data <= read_data_from_sdram[59:48];
			default:
				reg_dist_data = 0;
			endcase
	end
endmodule
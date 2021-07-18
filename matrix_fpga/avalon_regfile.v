`timescale 1 ps / 1 ps


module avalon_csr
(
		input   wire		 clk,
		input   wire         rst, 
		output  wire         mm_waitrequest,      //           mm_bridge_0_m0.waitrequest
		output  wire [31:0]  mm_readdata,         //                         .readdata
		output  wire         mm_readdatavalid,    //                         .readdatavalid
		input wire [31:0] 	 mm_writedata,        //                         .writedata
		input wire [9:0]  	 mm_address,          //                         .address
		input wire        	 mm_write,            //                         .write
		input wire        	 mm_read,             

		output wire [31:0]   reg0,
		output wire [31:0]   reg1,
		output wire [31:0]   reg2,
		output wire [31:0]   reg3,
		output wire [31:0]   reg4,
		output wire [31:0]   reg5,
		output wire [31:0]   reg6,
		output wire [31:0]   reg7,
		input wire  [31:0]   reg8

);
	assign reg0 = slv_reg0;
	assign reg1 = slv_reg1;
	assign reg2 = slv_reg2;
	assign reg3 = slv_reg3;
	assign reg4 = slv_reg4;
	assign reg5 = slv_reg5;
	assign reg6 = slv_reg6;
	assign reg7 = slv_reg7;

	reg [31:0]	slv_reg0;
	reg [31:0]	slv_reg1;
	reg [31:0]	slv_reg2;
	reg [31:0]	slv_reg3;
	reg [31:0]	slv_reg4;
	reg [31:0]	slv_reg5;
	reg [31:0]	slv_reg6;
	reg [31:0]	slv_reg7;
    
    reg [31:0] reg_mm_readdata;
	reg [31:0] reg_data_out;
	reg reg_readdatavalid;
	
	wire	 slv_reg_rden;
	wire	 slv_reg_wren;

	assign mm_waitrequest = 1'b0;
	assign mm_readdatavalid = reg_readdatavalid;
    assign mm_readdata = reg_mm_readdata;
    
	assign slv_reg_rden = mm_read;
	assign slv_reg_wren = mm_write;

	// write
	always @(posedge clk)
	begin
		if(rst == 1'b1)
			begin
				slv_reg0 <= 0;
	      		slv_reg1 <= 0;
	      		slv_reg2 <= 0;
	      		slv_reg3 <= 0;
	      		slv_reg4 <= 0;
	      		slv_reg5 <= 0;
	      		slv_reg6 <= 0;
	      		slv_reg7 <= 0;
			end
		else
			begin
				if (slv_reg_wren)
	      		begin
	      	  		case ( mm_address )
	      	    		5'h0:
						  slv_reg0 <= mm_writedata;
	      	    		5'h4:
						  slv_reg1 <= mm_writedata;
	      	    		5'h8:
						  slv_reg2 <= mm_writedata;						  
	      	    		5'hC:
						  slv_reg3 <= mm_writedata;
	      	    		5'h10:
						  slv_reg4 <= mm_writedata;
	      	    		5'h14:
						  slv_reg5 <= mm_writedata;
	      	    		5'h18:
						  slv_reg6 <= mm_writedata;
	      	    		5'h1C:
						  slv_reg7 <= mm_writedata;
	      	    	default : begin
	      	    	            slv_reg0 <= slv_reg0;
	      	    	            slv_reg1 <= slv_reg1;
	      	    	            slv_reg2 <= slv_reg2;
	      	    	            slv_reg3 <= slv_reg3;
	      	    	            slv_reg4 <= slv_reg4;
	      	    	            slv_reg5 <= slv_reg5;
	      	    	            slv_reg6 <= slv_reg6;
	      	    	            slv_reg7 <= slv_reg7;
	      	    	          end
	      	  		endcase
				end
			end
	end	

	//read 


	always @(*)
	begin
	      // Address decoding for reading registers
	      case ( mm_address )
	        6'h0   : reg_data_out <= slv_reg0;
	        6'h4   : reg_data_out <= slv_reg1;
	        6'h8   : reg_data_out <= slv_reg2;
	        6'hC   : reg_data_out <= slv_reg3;
	        6'h10   : reg_data_out <= slv_reg4;
	        6'h14   : reg_data_out <= slv_reg5;
	        6'h18   : reg_data_out <= slv_reg6;
	        6'h1C   : reg_data_out <= slv_reg7;
			  6'h20	: reg_data_out <= reg8;
	        default : reg_data_out <= 0;
	      endcase
	end

	always @( posedge clk )
	begin
	  if ( rst == 1'b1 )
	    begin
	      reg_mm_readdata  <= 0;
		  reg_readdatavalid <= 0;
	    end 
	  else
	    begin    
	      if (slv_reg_rden)
	        begin
		      reg_readdatavalid <= 1;			
	          reg_mm_readdata <= reg_data_out;     // register read data
	        end
		  else
		  	reg_readdatavalid <= 0;	   
	    end
	 end
	endmodule
  
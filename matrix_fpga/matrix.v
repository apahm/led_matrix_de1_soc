module matrix
(
	input	wire			rst_n,
	input	wire			clk,


	output	reg				r0,
	output	reg				g0,
	output	reg				b0,
	output	reg				r1,
	output	reg				g1,
	output	reg				b1,
	
	output	reg				r2,
	output	reg				g2,
	output	reg				b2,
	output	reg				r3,
	output	reg				g3,
	output	reg				b3,
	
	output	reg		[2:0]	a,
	output	reg				blank,
	output	reg				sclk,
	output	reg				latch,

	output wire [9:0] mem_address,
	output wire mem_clk,
	output wire mem_write_enable,
	input wire [47:0] mem_output_data
);



//---------------------------------------------------------------------------------------------
// state machine states
//

localparam WAIT = 0,
		   BLANK = 1,
		   LATCH = 2,
		   UNBLANK = 3,
		   READ = 4,
		   SHIFT1 = 5,
		   SHIFT2 = 6,
		   WAIT_SHIFT = 7;


//---------------------------------------------------------------------------------------------
// registers and wires
//
reg [8:0] level;
reg [2:0] state;

reg [12:0] timer;
reg [12:0] blanktimer;
reg [3:0] delay;
reg rd_buffer;

reg [1:0] rd_bit;

reg [2:0] rd_row;
reg [6:0] rd_col;

wire [9:0] rd_addr;
reg [9:0] rd_app;

wire [47:0] rd_data;

wire [3:0] rd_r1, rd_g1, rd_b1, rd_r0, rd_g0, rd_b0;
wire rd_r1_bit, rd_g1_bit, rd_b1_bit, rd_r0_bit, rd_g0_bit, rd_b0_bit;

wire [3:0] rd_r3, rd_g3, rd_b3, rd_r2, rd_g2, rd_b2;
wire rd_r3_bit, rd_g3_bit, rd_b3_bit, rd_r2_bit, rd_g2_bit, rd_b2_bit;


assign mem_address = rd_addr;
assign mem_clk = clk;
assign mem_write_enable = 1'b0;
assign rd_data = mem_output_data;

assign rd_addr =  rd_col + rd_app;

assign rd_r3 = rd_data[47:44];
assign rd_g3 = rd_data[43:40];
assign rd_b3 = rd_data[39:36];
assign rd_r2 = rd_data[35: 32];
assign rd_g2 = rd_data[ 31: 28];
assign rd_b2 = rd_data[ 27: 24];

assign rd_r1 = rd_data[23:20];
assign rd_g1 = rd_data[19:16];
assign rd_b1 = rd_data[15:12];
assign rd_r0 = rd_data[11: 8];
assign rd_g0 = rd_data[ 7: 4];
assign rd_b0 = rd_data[ 3: 0];

assign rd_r3_bit = rd_r3[rd_bit];
assign rd_g3_bit = rd_g3[rd_bit];
assign rd_b3_bit = rd_b3[rd_bit];
assign rd_r2_bit = rd_r2[rd_bit];
assign rd_g2_bit = rd_g2[rd_bit];
assign rd_b2_bit = rd_b2[rd_bit];

assign rd_r1_bit = rd_r1[rd_bit];
assign rd_g1_bit = rd_g1[rd_bit];
assign rd_b1_bit = rd_b1[rd_bit];
assign rd_r0_bit = rd_r0[rd_bit];
assign rd_g0_bit = rd_g0[rd_bit];
assign rd_b0_bit = rd_b0[rd_bit];


//---------------------------------------------------------------------------------------------
// clocked logic
//

always @ (posedge clk)
begin
	if (rst_n)
	begin
		r0 <= 0;
		g0 <= 0;
		b0 <= 0;
		r1 <= 0;
		g1 <= 0;
		b1 <= 0;
		r2 <= 0;
		g2 <= 0;
		b2 <= 0;
		r3 <= 0;
		g3 <= 0;
		b3 <= 0;
		a <= 0;
		rd_app <= 0;
		blank <= 1;
		sclk <= 0;
		latch <= 0;
		level <= 0;
		state <= READ;

		timer <= 0;
		blanktimer <= 0;
		delay <= 0;

		rd_buffer <= 0;
		rd_row <= 0;
		rd_bit <= 0;
		rd_col <= 0;
	end
	else
	begin
		// implemnt timer for binary coded modulation
		// bit plane 0 is displayed for ~192 clock cycles
		// each succesfive bit plane is displayed for 2x the clocks of the previous bit plane
		if (timer == 0)
		begin
			// for 10MHz clock, use 192-1,  384-1,  768-1, 1536-1 below
			// for 25MHz clock, use 480-1,  960-1, 1920-1, 3840-1 below
			// for 50MHz clock, use 960-1, 1920-1, 3840-1, 7680-1 below
			case (rd_bit)
				0: timer <= 959;
				1: timer <= 1919;
				2: timer <= 3839;
				3: timer <= 7679;
			endcase
			case (rd_bit)
				0: blanktimer <= (959 * level) >> 8;
				1: blanktimer <= (1919 * level) >> 8;
				2: blanktimer <= (3839 * level) >> 8;
				3: blanktimer <= (7679 * level) >> 8;
			endcase
		end
		else
		begin
			timer <= timer - 1;
			blanktimer <= blanktimer - 1;
		end

		// move blanking control outside state machine to implement global dimming
		if ((blanktimer == 0) || (timer == 0))
		begin
			blank <= 1;
		end
		else if ((state == LATCH) && (delay == 0))
		begin
			blank <= 0;
		end
		
		// state machine
		case (state)

			// wait for timer to expire then blank the display
			WAIT: begin
				sclk <= 0;
				if (timer == 0)
				begin
					// blank <= 1;
					delay <= 8;
					state <= BLANK;
				end
			end

			// wait a while then latch in data previosly shifted into display
			BLANK: begin
				if (delay == 0)
				begin
					latch <= 1;
					delay <= 8;
					state <= LATCH;
					a <= rd_row;
				end
				else
				begin
					delay <= delay - 1;
				end
			end

			// wait a while then unblank the display to display the latched data
			LATCH: begin
				if (delay == 0)
				begin
					// blank <= 0;
					latch <= 0;
					state <= UNBLANK;
				end
				else
				begin
					delay <= delay - 1;
				end
			end

			// find the next bit, row, column, and buffer to display
			// this is converted to a read address using combinatorial logic above
			UNBLANK: begin
				if (rd_bit == 3)
				begin
					rd_bit <= 0;
					if (rd_row == 7)
					begin
						rd_row <= 0;
						rd_app <= 0;
					end
					else
					begin
						rd_row <= rd_row + 1;
						rd_app <= rd_app + 128;
					end
				end
				else
				begin
					rd_bit <= rd_bit + 1;
				end
				state <= READ;
			end
			
			// the read, shift1, and shift2 states could be reduced to two states
			// if I knew which edge of sclk latched the data into the shift registers
			// this is good enough for one panel but for more than about four panels
			// it'd be worth reducing to two clocks instead of three clocks.

			// wait for read data to be output from RAM
			READ: begin
				state <= SHIFT1;
				sclk <= 0;
			end

			// drive the column data out the outputs
			SHIFT1: begin
				r0 <= rd_r0_bit;
				g0 <= rd_g0_bit;
				b0 <= rd_b0_bit;
				r1 <= rd_r1_bit;
				g1 <= rd_g1_bit;
				b1 <= rd_b1_bit;
				
				r2 <= rd_r2_bit;
				g2 <= rd_g2_bit;
				b2 <= rd_b2_bit;
				r3 <= rd_r3_bit;
				g3 <= rd_g3_bit;
				b3 <= rd_b3_bit;
				state <= WAIT_SHIFT;
			end
			
			WAIT_SHIFT: begin
			    state <= SHIFT2;
			end
			
			SHIFT2: begin
				sclk <= 1;
				if (rd_col == 127)
				begin
					state <= WAIT;
					rd_col<= 0;
				end
				else
				begin
					state <= READ;
					rd_col <= rd_col + 1;
				end
			end

		endcase
	end
end

endmodule

module vga_controller

	#(parameter NUMBER_COLORS = 4)


	(
		input 																		CLOCK_50, 
		input																			resetn,
		input 			[9:0] 													VGA_R_in,
		input 			[9:0] 													VGA_G_in,
		input 			[9:0] 													VGA_B_in,
		output 	reg 	[((RESOLUTION == "320x240") ? (8) : (7)):0] 	x,
		output 	reg 	[((RESOLUTION == "320x240") ? (7) : (6)):0] 	y,
		output  			[9:0] 													VGA_R,
		output  			[9:0] 													VGA_G,
		output  			[9:0] 													VGA_B,
		output 	reg 																VGA_HS,
		output 	reg 																VGA_VS,
		output 	reg 																VGA_BLANK,
		output 																		VGA_SYNC,
		output 	reg 																VGA_CLK,
		output 																		TRIGGER
	);
	
	// System parameters
	
	parameter RESOLUTION = "320x240";
	parameter MONOCHROME = "FALSE";
	
	// Timing parameters
	
	parameter C_VERT_NUM_PIXELS  = 10'd480;
	parameter C_VERT_SYNC_START  = 10'd493;
	parameter C_VERT_SYNC_END    = 10'd494;
	parameter C_VERT_TOTAL_COUNT = 10'd525;

	parameter C_HORZ_NUM_PIXELS  = 10'd640;
	parameter C_HORZ_SYNC_START  = 10'd656; 
	parameter C_HORZ_SYNC_END    = 10'd754; 
	parameter C_HORZ_TOTAL_COUNT = 10'd800;
	
	// Local Signals
	
	reg VGA_HS1;
	reg VGA_VS1;
	reg VGA_BLANK1; 
	reg [9:0] xCounter, yCounter;
	wire xCounter_clear;
	wire yCounter_clear;
	wire vcc;
	
   initial VGA_CLK = 1'b0;
	
	// Controller implementation
	
	assign vcc =1'b1;
   
   /* Generate VGA_CLOCK at 25 MHz */
   always @(posedge CLOCK_50)
      VGA_CLK <= ~VGA_CLK;
	
	/* A counter to scan through a horizontal line. */
	always @(posedge VGA_CLK or negedge resetn)
	begin
		if (!resetn)
			xCounter <= 10'd0;
		else if (xCounter_clear)
			xCounter <= 10'd0;
		else
		begin
			xCounter <= xCounter + 1'b1;
		end
	end
	assign xCounter_clear = (xCounter == (C_HORZ_TOTAL_COUNT-1));

	/* A counter to scan vertically, indicating the row currently being drawn. */
	always @(posedge VGA_CLK or negedge resetn)
	begin
		if (!resetn)
			yCounter <= 10'd0;
		else if (xCounter_clear && yCounter_clear)
			yCounter <= 10'd0;
		else if (xCounter_clear)		
			yCounter <= yCounter + 1'b1;
	end
	assign yCounter_clear = (yCounter == (C_VERT_TOTAL_COUNT-1)); 

	always @(*)
	begin
		if (RESOLUTION == "320x240")
		begin
			x = xCounter[9:1];
			y = yCounter[8:1];
		end
		else
		begin
			x = xCounter[9:2];
			y = yCounter[8:2];
		end
	end

	/* Generate the vertical and horizontal synchronization pulses. */
	always @(posedge VGA_CLK)
	begin
		//- Sync Generator (ACTIVE LOW)
		VGA_HS1 <= ~((xCounter >= C_HORZ_SYNC_START) && (xCounter <= C_HORZ_SYNC_END));
		VGA_VS1 <= ~((yCounter >= C_VERT_SYNC_START) && (yCounter <= C_VERT_SYNC_END));
		
		//- Current X and Y is valid pixel range
		VGA_BLANK1 <= ((xCounter < C_HORZ_NUM_PIXELS) && (yCounter < C_VERT_NUM_PIXELS));	
	
		//- Add 1 cycle delay
		VGA_HS <= VGA_HS1;
		VGA_VS <= VGA_VS1;
		VGA_BLANK <= VGA_BLANK1;	
	end
	
	/* VGA sync should be 1 at all times. */
	assign VGA_SYNC = vcc;
	
	assign on_screen = (({1'b0, xCounter} >= 0) & ({1'b0, xCounter} < C_HORZ_NUM_PIXELS+2) & ({1'b0, yCounter} < C_VERT_NUM_PIXELS));
	
	assign VGA_R = on_screen ? VGA_R_in : 0;
	assign VGA_G = on_screen ? VGA_G_in : 0;
	assign VGA_B = on_screen ? VGA_B_in : 0;
	
	assign Trigger = VGA_VS;
	

endmodule
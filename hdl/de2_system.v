module de2_system

	#(parameter NUMBER_COLORS = 9)

	(
		input								CLOCK_50,
		output				 [2:0]		LEDR,
		input				 [17:0]		SW,
		input				 [0:0]		KEY,
		/////////// VGA /////////////
		output							VGA_CLK,   				//	VGA Clock
		output							VGA_HS,					//	VGA H_SYNC
		output							VGA_VS,					//	VGA V_SYNC
		output							VGA_BLANK,				//	VGA BLANK
		output							VGA_SYNC,				//	VGA SYNC
		output			[9:0]			VGA_R,   				//	VGA Red[9:0]
		output			[9:0]			VGA_G,	 				//	VGA Green[9:0]
		output			[9:0]			VGA_B	   				//	VGA Blue[9:0]
	);
	
   wire [8:0] 	xvga;
	wire [7:0] 	yvga;
   wire [$clog2(NUMBER_COLORS):0]  color_front, color_back, color_vga, din;
	wire [$clog2(320*240)-1:0] waddr;
	reg bb_we, fb_we;
	
	assign LEDR[0] = bb_we;
	assign LEDR[1] = fb_we;
	assign LEDR[2] = select;
	
	wire TRIGGER;
	
	reg select, swap, done;
	
	always @(negedge TRIGGER)
		if (KEY[0])
			if (done) begin
				select = 1'b1; fb_we = 1'b1; swap = 1'b1;
			end
			else begin
				select = 1'b0; fb_we = 1'b0; swap = 1'b0;
			end
		else
			swap = 1'b0;
 	
	
	
	
		
	
	assign color_vga = (SW[0] ? select : SW[1]) ? color_back : color_front;

	
	wire [9:0] VGA_R_palette, VGA_G_palette, VGA_B_palette;
	
	color_palette #(NUMBER_COLORS) color_palette (
		.id(color_vga),
		.VGA_R_out(VGA_R_palette),
		.VGA_G_out(VGA_G_palette),
		.VGA_B_out(VGA_B_palette)
	);

   
   vga_controller #(NUMBER_COLORS) vga_controller (
      .CLOCK_50      (CLOCK_50),
      .resetn        (1'b1),
      .x             (xvga),
      .y             (yvga),	
		.VGA_R_in(VGA_R_palette),
		.VGA_G_in(VGA_G_palette),
		.VGA_B_in(VGA_B_palette),
      .VGA_R         (VGA_R),
      .VGA_G         (VGA_G),
      .VGA_B         (VGA_B),
      .VGA_HS        (VGA_HS),
      .VGA_VS        (VGA_VS),
      .VGA_BLANK     (VGA_BLANK),
      .VGA_SYNC      (VGA_SYNC),
      .VGA_CLK       (VGA_CLK),
		.TRIGGER(TRIGGER)
   );
	
	background_ram #(.NUMBER_COLORS(NUMBER_COLORS), .FILENAME("nd.txt")) back_buffer (
		.clk(CLOCK_50),
		.x(xvga),
		.y(yvga),
		.din(din),
		.waddr(waddr),
		.we(bb_we),
		.dout(color_back)
	);
	
	background_ram #(NUMBER_COLORS) front_buffer (
		.clk(CLOCK_50),
		.x(xvga),
		.y(yvga),
		.din(color_back),
		.waddr(yvga + 240*xvga),
		.we(fb_we),
		.dout(color_front)
	);

	
	processor u0 (
		.clk_clk                          (CLOCK_50),                          //                       clk.clk
		.reset_reset_n                    (1'b1),                    //                     reset.reset_n
		.done_external_connection_export  (done),  //  done_external_connection.export
		.swap_external_connection_export  (swap),  //  swap_external_connection.export
		.bb_we_external_connection_export (bb_we), // bb_we_external_connection.export
		.waddr_external_connection_export (waddr), // waddr_external_connection.export
		.din_external_connection_export   (din)    //   din_external_connection.export
	);
	


	
	
endmodule
module de2_system

	#(parameter NUMBER_COLORS = 9)

	(
		input								CLOCK_50,
		input				[0:0]			KEY,
		/////////// VGA /////////////
		output							VGA_CLK,   	//	VGA Clock
		output							VGA_HS,		//	VGA H_SYNC
		output							VGA_VS,		//	VGA V_SYNC
		output							VGA_BLANK,	//	VGA BLANK
		output							VGA_SYNC,	//	VGA SYNC
		output			[9:0]			VGA_R,   	//	VGA Red[9:0]
		output			[9:0]			VGA_G,	 	//	VGA Green[9:0]
		output			[9:0]			VGA_B,	   //	VGA Blue[9:0]
	);

	// Connects vga controller and the buffers
  wire [8:0] 	xvga;
	wire [7:0] 	yvga;

	// output and input from and to the buffers
   wire [$clog2(NUMBER_COLORS):0]  color_front, color_back, color_vga, din;
	// address from the processor to the back buffer
	wire [$clog2(320*240)-1:0] waddr;
	// Trigger for the update of the buffers - end of screen render
	wire Trigger;

	// These states control the updating between the processor and the bufferrs
	wire select, swap, done, bb_we, fb_we;

	// Controls the updating of front and back buffers
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


	// Switch between the values in the front and back buffer
	assign color_vga = select ? color_back : color_front;

	// NIOS II Processor - Platform Designer Unit
	processor u0 (
		.clk_clk                          (CLOCK_50),
		.reset_reset_n                    (1'b1),
		.done_external_connection_export  (done),
		.swap_external_connection_export  (swap),
		.bb_we_external_connection_export (bb_we),
		.waddr_external_connection_export (waddr),
		.din_external_connection_export   (din)
	);

	// Back buffer, receives updates from the processor, updates the front buffer
	background_ram #(.NUMBER_COLORS(NUMBER_COLORS)) back_buffer (
		// System
		.clk(CLOCK_50),
		// Pixel coordinates
		.x(xvga),
		.y(yvga),
		// Data from the processor
		.din(din),
		.waddr(waddr),
		.we(bb_we),
		// Data to the front buffer and the vga controller
		.dout(color_back)
	);

	// Front buffer, receives updates from the back buffer
	background_ram #(NUMBER_COLORS) front_buffer (
		// System
		.clk(CLOCK_50),
		// Pixel coordinates
		.x(xvga),
		.y(yvga),
		// Data from the back buffer
		.din(color_back),
		// Writing adress comes from the vga controller
		.waddr(yvga + 240*xvga),
		.we(fb_we),
		// Data to the vga controller
		.dout(color_front)
	);

	// Wires between the palette module and the vga controller
	wire [9:0] VGA_R_palette, VGA_G_palette, VGA_B_palette;

	// Color palette, translates the id from memory to the vga codes
	color_palette #(NUMBER_COLORS) color_palette (
		// Color id
		.id(color_vga),
		// VGA values of the color
		.VGA_R_out(VGA_R_palette),
		.VGA_G_out(VGA_G_palette),
		.VGA_B_out(VGA_B_palette)
	);

	vga_controller #(NUMBER_COLORS) vga_controller (
		// System
      .CLOCK_50      (CLOCK_50),
      .resetn        (1'b1),
		// x and y coordinates
      .x             (xvga),
      .y             (yvga),
		// VGA values from the palette
		.VGA_R_in(VGA_R_palette),
		.VGA_G_in(VGA_G_palette),
		.VGA_B_in(VGA_B_palette),
		// VGA Control signals
      .VGA_HS        (VGA_HS),
      .VGA_VS        (VGA_VS),
      .VGA_BLANK     (VGA_BLANK),
      .VGA_SYNC      (VGA_SYNC),
      .VGA_CLK       (VGA_CLK),
		// VGA values to the DE2-115
      .VGA_R         (VGA_R),
      .VGA_G         (VGA_G),
      .VGA_B         (VGA_B),
		// Trigger for the NIOS Processor
		.Trigger(Trigger)
   );

endmodule

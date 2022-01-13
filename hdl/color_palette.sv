module color_palette 

	#(parameter NUMBER_COLORS = 4, parameter MONOCHROME="FALSE")
	
	(
		// address
		input [((MONOCHROME == "TRUE") ? (0) : $clog2(NUMBER_COLORS)):0] id,
		// output
		output [9:0] VGA_R_out,
		output [9:0] VGA_G_out,
		output [9:0] VGA_B_out
	);
	
	
	reg [9:0] rom [0:NUMBER_COLORS*3-1];
	
	initial $readmemh("colors.txt", rom);
	
	assign VGA_R_out = rom[id];
	assign VGA_G_out = rom[id + NUMBER_COLORS];
	assign VGA_B_out = rom[id + 2*NUMBER_COLORS];
	 
endmodule
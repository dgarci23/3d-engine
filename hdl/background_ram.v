module background_ram

	#(parameter NUMBER_COLORS = 10, parameter FILENAME = "background.txt")
	
	(
		input                clk,    			
		input          [8:0] x,
		input          [7:0] y,
		input				[$clog2(NUMBER_COLORS):0] din,
		input				[$clog2(320*240)-1:0]	  waddr,
		input												  we,
		output   reg   [$clog2(NUMBER_COLORS):0] dout
	);
	
	parameter IMAGE_FILE = FILENAME;
	
	wire [$clog2(320*240)-1:0] raddr  = y + 240*x;
	
	reg [$clog2(NUMBER_COLORS):0] mem [0:320*240-1];
	
	//initial $readmemh(IMAGE_FILE, mem);
	
	
	always @(posedge clk)
		
		if (we)
			mem[waddr] <= din;
		
	always @(posedge clk)
	
		dout <= mem[raddr];
		

endmodule
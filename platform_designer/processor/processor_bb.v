
module processor (
	clk_clk,
	reset_reset_n,
	done_external_connection_export,
	swap_external_connection_export,
	bb_we_external_connection_export,
	waddr_external_connection_export,
	din_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	done_external_connection_export;
	output	[7:0]	swap_external_connection_export;
	output	[7:0]	bb_we_external_connection_export;
	output	[7:0]	waddr_external_connection_export;
	output	[7:0]	din_external_connection_export;
endmodule

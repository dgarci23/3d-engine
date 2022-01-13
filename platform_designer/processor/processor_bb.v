
module processor (
	bb_we_external_connection_export,
	clk_clk,
	din_external_connection_export,
	done_external_connection_export,
	reset_reset_n,
	swap_external_connection_export,
	waddr_external_connection_export);	

	output		bb_we_external_connection_export;
	input		clk_clk;
	output	[31:0]	din_external_connection_export;
	output		done_external_connection_export;
	input		reset_reset_n;
	input		swap_external_connection_export;
	output	[31:0]	waddr_external_connection_export;
endmodule

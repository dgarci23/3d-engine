
module processor (
	bb_we_external_connection_export,
	din_external_connection_export,
	done_external_connection_export,
	reset_reset_n,
	swap_external_connection_export,
	waddr_external_connection_export,
	clk_clk,
	altpll_0_c0_clk,
	clock_bridge_0_in_clk_clk,
	altpll_0_areset_conduit_export,
	altpll_0_locked_conduit_export);	

	output		bb_we_external_connection_export;
	output	[31:0]	din_external_connection_export;
	output		done_external_connection_export;
	input		reset_reset_n;
	input		swap_external_connection_export;
	output	[31:0]	waddr_external_connection_export;
	input		clk_clk;
	output		altpll_0_c0_clk;
	input		clock_bridge_0_in_clk_clk;
	input		altpll_0_areset_conduit_export;
	output		altpll_0_locked_conduit_export;
endmodule

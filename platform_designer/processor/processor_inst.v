	processor u0 (
		.bb_we_external_connection_export (<connected-to-bb_we_external_connection_export>), // bb_we_external_connection.export
		.clk_clk                          (<connected-to-clk_clk>),                          //                       clk.clk
		.din_external_connection_export   (<connected-to-din_external_connection_export>),   //   din_external_connection.export
		.done_external_connection_export  (<connected-to-done_external_connection_export>),  //  done_external_connection.export
		.reset_reset_n                    (<connected-to-reset_reset_n>),                    //                     reset.reset_n
		.swap_external_connection_export  (<connected-to-swap_external_connection_export>),  //  swap_external_connection.export
		.waddr_external_connection_export (<connected-to-waddr_external_connection_export>)  // waddr_external_connection.export
	);


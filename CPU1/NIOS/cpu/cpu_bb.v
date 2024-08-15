
module cpu (
	clk_clk,
	led_tens_export,
	led_units_export,
	reset_reset_n);	

	input		clk_clk;
	output	[6:0]	led_tens_export;
	output	[6:0]	led_units_export;
	input		reset_reset_n;
endmodule

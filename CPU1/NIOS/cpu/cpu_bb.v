
module cpu (
	clk_clk,
	led_hour_tens_export,
	led_hour_units_export,
	led_minutes_tens_export,
	led_seconds_tens_export,
	led_seconds_units_export,
	led_minutes_units_export,
	reset_reset_n);	

	input		clk_clk;
	output	[6:0]	led_hour_tens_export;
	output	[6:0]	led_hour_units_export;
	output	[6:0]	led_minutes_tens_export;
	output	[6:0]	led_seconds_tens_export;
	output	[6:0]	led_seconds_units_export;
	output	[6:0]	led_minutes_units_export;
	input		reset_reset_n;
endmodule

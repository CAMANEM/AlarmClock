
module cpu (
	btn_edit_export,
	clk_clk,
	led_hour_tens_export,
	led_hour_units_export,
	led_minutes_tens_export,
	led_minutes_units_export,
	led_seconds_tens_export,
	led_seconds_units_export,
	reset_reset_n,
	sw_states_export,
	buzzer_export);	

	input	[1:0]	btn_edit_export;
	input		clk_clk;
	output	[6:0]	led_hour_tens_export;
	output	[6:0]	led_hour_units_export;
	output	[6:0]	led_minutes_tens_export;
	output	[6:0]	led_minutes_units_export;
	output	[6:0]	led_seconds_tens_export;
	output	[6:0]	led_seconds_units_export;
	input		reset_reset_n;
	input	[2:0]	sw_states_export;
	output		buzzer_export;
endmodule

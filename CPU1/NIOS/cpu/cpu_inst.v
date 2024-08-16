module cpu_inst(input clk, reset, output [6:0] led_seconds_units, output [6:0] led_seconds_tens, output [6:0] led_minutes_units, output [6:0] led_minutes_tens, output [6:0] led_hour_units, output [6:0] led_hour_tens);
	cpu u0 (
		.clk_clk                  (clk),                  //               clk.clk
		.led_hour_tens_export     (led_hour_tens),     //     led_hour_tens.export
		.led_hour_units_export    (led_hour_units),    //    led_hour_units.export
		.led_minutes_tens_export  (led_minutes_tens),  //  led_minutes_tens.export
		.led_seconds_tens_export  (led_seconds_tens),  //  led_seconds_tens.export
		.led_seconds_units_export (led_seconds_units), // led_seconds_units.export
		.led_minutes_units_export (led_minutes_units), // led_minutes_units.export
		.reset_reset_n            (reset)             //             reset.reset_n
	);
endmodule


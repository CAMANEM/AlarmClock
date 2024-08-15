module cpu_inst(input clk, reset, output [6:0] led_units, output [6:0] led_tens);
	cpu u0 (
		.clk_clk          (clk),          //       clk.clk
		.led_units_export (led_units), // led_units.export
		.reset_reset_n    (reset),    //     reset.reset_n
		.led_tens_export  (led_tens)   //  led_tens.export
	);
endmodule

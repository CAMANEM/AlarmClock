	component cpu is
		port (
			clk_clk          : in  std_logic                    := 'X'; -- clk
			led_tens_export  : out std_logic_vector(6 downto 0);        -- export
			led_units_export : out std_logic_vector(6 downto 0);        -- export
			reset_reset_n    : in  std_logic                    := 'X'  -- reset_n
		);
	end component cpu;

	u0 : component cpu
		port map (
			clk_clk          => CONNECTED_TO_clk_clk,          --       clk.clk
			led_tens_export  => CONNECTED_TO_led_tens_export,  --  led_tens.export
			led_units_export => CONNECTED_TO_led_units_export, -- led_units.export
			reset_reset_n    => CONNECTED_TO_reset_reset_n     --     reset.reset_n
		);


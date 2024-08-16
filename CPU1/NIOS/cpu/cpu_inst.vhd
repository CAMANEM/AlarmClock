	component cpu is
		port (
			clk_clk                  : in  std_logic                    := 'X'; -- clk
			led_hour_tens_export     : out std_logic_vector(6 downto 0);        -- export
			led_hour_units_export    : out std_logic_vector(6 downto 0);        -- export
			led_minutes_tens_export  : out std_logic_vector(6 downto 0);        -- export
			led_seconds_tens_export  : out std_logic_vector(6 downto 0);        -- export
			led_seconds_units_export : out std_logic_vector(6 downto 0);        -- export
			led_minutes_units_export : out std_logic_vector(6 downto 0);        -- export
			reset_reset_n            : in  std_logic                    := 'X'  -- reset_n
		);
	end component cpu;

	u0 : component cpu
		port map (
			clk_clk                  => CONNECTED_TO_clk_clk,                  --               clk.clk
			led_hour_tens_export     => CONNECTED_TO_led_hour_tens_export,     --     led_hour_tens.export
			led_hour_units_export    => CONNECTED_TO_led_hour_units_export,    --    led_hour_units.export
			led_minutes_tens_export  => CONNECTED_TO_led_minutes_tens_export,  --  led_minutes_tens.export
			led_seconds_tens_export  => CONNECTED_TO_led_seconds_tens_export,  --  led_seconds_tens.export
			led_seconds_units_export => CONNECTED_TO_led_seconds_units_export, -- led_seconds_units.export
			led_minutes_units_export => CONNECTED_TO_led_minutes_units_export, -- led_minutes_units.export
			reset_reset_n            => CONNECTED_TO_reset_reset_n             --             reset.reset_n
		);


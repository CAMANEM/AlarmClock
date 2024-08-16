#include "sys/alt_stdio.h"
#include "stdio.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_pio_regs.h"
#include "io.h" // Necesario para IORD y IOWR

void init_timer_interrupt();
static void timer_isr(void *context, alt_u32 id);
short switch1_true();
//short btn1_true();
void setAlarm();
void setTime();
void checkSelect();
short increaseTime();


short seconds = 0;
short minutes = 0;
short hour = 0;
short select = 0;
volatile unsigned short *led_seconds_units = (unsigned short *) 0x3090;
volatile unsigned short *led_seconds_tens = (unsigned short *) 0x3080;
volatile unsigned short *led_minutes_units = (unsigned short *) 0x3040;
volatile unsigned short *led_minutes_tens = (unsigned short *) 0x3070;
volatile unsigned short *led_hour_units = (unsigned short *) 0x3060;
volatile unsigned short *led_hour_tens = (unsigned short *) 0x3050;
volatile unsigned short *btn_state = (unsigned short *) 0x3030;
volatile unsigned short *sw_state = (unsigned short *) 0x3020;

// Funci�n para convertir segundos en el valor de LEDs
unsigned short get_led_value(short sec) {
    switch (sec) {
        case 0:  return 0b1000000;
        case 1:  return 0b1111001;
        case 2:  return 0b0100100;
        case 3:  return 0b0110000;
        case 4:  return 0b0011001;
        case 5:  return 0b0010010;
        case 6:  return 0b0000010;
        case 7:  return 0b1111000;
        case 8:  return 0b0000000;
        case 9:  return 0b0010000;
        default: return 0b1000000;
    }
}

int main()
{ 
    alt_putstr("Hello from Nios II!\n");
    init_timer_interrupt();
	while (1) {
		// Aqu� podr�a ir otro c�digo si fuera necesario
	}

    return 0;
}

void init_timer_interrupt()
{
    // Registra la ISR con HAL
    alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_IRQ, (void *)timer_isr, NULL, 0x0);

    // Inicia el temporizador
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
            | ALTERA_AVALON_TIMER_CONTROL_START_MSK
            | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
}

static void timer_isr(void *context, alt_u32 id)
{
	*led_seconds_units = get_led_value(seconds % 10); // Obtiene el valor correspondiente a los LEDs
	*led_seconds_tens = get_led_value(seconds / 10); // Obtiene el valor correspondiente a los LEDs
	*led_minutes_units = get_led_value(minutes % 10);
	*led_minutes_tens = get_led_value(minutes / 10);
	*led_hour_units = get_led_value(hour % 10);
	*led_hour_tens = get_led_value(hour / 10);

	if (switch1_true())
	{
		setTime();
	}
	else{
		if (seconds == 59)
		{
			if (minutes == 59)
			{
				hour = (hour + 1) % 24; // Resetea a 0 despu�s de 23  e Incrementa las horas
			}
			minutes = (minutes + 1) % 60; // Resetea a 0 despu�s de 59  e Incrementa los minutos
		}
		seconds = (seconds + 1) % 60; // Resetea a 0 despu�s de 59  e Incrementa los segundos
	}
	// Limpia la interrupci�n
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
}

// Switch1 esta activado y est� en modo cambio de hora
short switch1_true()
{
    unsigned short switch_value = IORD(sw_state, 0);

    return (switch_value & 0x1) ? 1 : 0;

}

/*
short btn1_true()
{
    unsigned short button_value = IORD(btn_state, 0);

    return (button_value & 0x1) ? 1 : 0;

}
*/

// ocurre cuando el boton derecho (KEY0) ha sido presionando. Valida que se pueda aumentar la hora si el boton esta presionado
short increaseTime()
{
    unsigned short button_value = IORD(btn_state, 0);

    return (button_value & 0x1) ? 0 : 1;

}

// valida la presion del boton de selecion de horas, minutos o segundos para poder seleccionar la siguiente opcion
void checkSelect()
{
    unsigned short button_value = IORD(btn_state, 0);

    unsigned short next = !((button_value >> 1) & 0x1);
    if (next)
    {
    	select = (select + 1) % 3;
    	alt_printf("El valor de los select es: %d\n", select);
    }
}

// modo de configuracion de hora, permite cambiar la hora
void setTime()
{
	if (increaseTime())
	{
		checkSelect();
		switch (select)
		{
		        case 0:
		        	seconds = (seconds + 1) % 60;
		        	break;
		        case 1:
		        	minutes = (minutes + 1) % 60;
		        	break;
		        case 2:
		        	hour = (hour + 1) % 24;
		        	break;
		}
	}
}

void setAlarm()
{

}



/*
void check_switches()
{
    unsigned short switch_value = IORD(sw_state, 0);

    unsigned short switch1 = switch_value & 0x1; // Primer switch (bit 0)
    unsigned short switch2 = (switch_value >> 1) & 0x1; // Segundo switch (bit 1)
    unsigned short switch3 = (switch_value >> 2) & 0x1; // Tercer switch (bit 2)


    if (switch1) {
        alt_putstr("SW I!\n");
    }

    if (switch2) {
    	alt_putstr("SW II!\n");
    }

    if (switch3) {
    	alt_putstr("SW III!\n");
    }
}
*/

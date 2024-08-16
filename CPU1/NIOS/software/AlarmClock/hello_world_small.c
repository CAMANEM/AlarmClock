#include "sys/alt_stdio.h"
#include "stdio.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"

void init_timer_interrupt();
static void timer_isr(void *context, alt_u32 id);

short seconds = 50;
short minutes = 59;
short hour = 24;
volatile unsigned short *led_seconds_units = (unsigned short *) 0x3070;
volatile unsigned short *led_seconds_tens = (unsigned short *) 0x3060;
volatile unsigned short *led_minutes_units = (unsigned short *) 0x3020;
volatile unsigned short *led_minutes_tens = (unsigned short *) 0x3050;
volatile unsigned short *led_hour_units = (unsigned short *) 0x3040;
volatile unsigned short *led_hour_tens = (unsigned short *) 0x3030;


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
        //case 10: return 0b11110011000000;
        //case 11: return 0b11110011111001;
        //case 12: return 0b11110010100100;
        //case 13: return 0b11110010110000;
        //case 14: return 0b11110010011001;
        // Agregar m�s casos seg�n sea necesario hasta 59
        default: return 0b1000000; // Valor por defecto
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
    // Limpia la interrupci�n
    *led_seconds_units = get_led_value(seconds % 10); // Obtiene el valor correspondiente a los LEDs
    *led_seconds_tens = get_led_value(seconds / 10); // Obtiene el valor correspondiente a los LEDs
	*led_minutes_units = get_led_value(minutes % 10);
	*led_minutes_tens = get_led_value(minutes / 10);
	*led_hour_units = get_led_value(hour % 10);
	*led_hour_tens = get_led_value(hour / 10);

    if (seconds == 59){

    	if (minutes == 59){
    	    	hour = (hour + 1) % 25; // Resetea a 0 despu�s de 24  e Incrementa las horas
    	    }

    	minutes = (minutes + 1) % 60; // Resetea a 0 despu�s de 59  e Incrementa los minutos
    }


    seconds = (seconds + 1) % 60; // Resetea a 0 despu�s de 59  e Incrementa los segundos

    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
}

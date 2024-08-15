#include "sys/alt_stdio.h"
#include "stdio.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"

void init_timer_interrupt();
static void timer_isr(void *context, alt_u32 id);

short seconds = 0;
volatile unsigned short *led_units = (unsigned short *) 0x3030;
volatile unsigned short *led_tens = (unsigned short *) 0x3020;

// Función para convertir segundos en el valor de LEDs
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
        // Agregar más casos según sea necesario hasta 59
        default: return 0b10000001000000; // Valor por defecto
    }
}

int main()
{ 
    alt_putstr("Hello from Nios II!\n");
    init_timer_interrupt();
    while (1) {
        // Aquí podría ir otro código si fuera necesario
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
    // Limpia la interrupción
    *led_units = get_led_value(seconds % 10); // Obtiene el valor correspondiente a los LEDs
    *led_tens = get_led_value(seconds / 10); // Obtiene el valor correspondiente a los LEDs

    alt_putstr("Second passed!\n");

    // Incrementa los segundos
    seconds = (seconds + 1) % 60; // Resetea a 0 después de 59
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
}

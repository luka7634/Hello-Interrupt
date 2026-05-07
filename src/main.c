#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "includes/pinDefines.h"

ISR(INT0_vect) /**< runs every time there is a change on the button */
{
    if ((BUTTON_PIN & (1 << BUTTON)))
        LED_PORT |= (1 << LED1);
    else
        LED_PORT &= ~(1 << LED1);
}

void initInterrupt0(void)
{
    EIMSK |= (1 << INT0);  /**< enable INT0 */
    EICRA |= (1 << ISC00); /**< trigger when button changes */
    sei();                 /**< set (global) interrupt enable bit */
}

void setup(void)
{
    LED_DDR = 0xff; /**< all leds active */
    DDRD = 0x00;    /**< pull-up */
    BUTTON_PORT |= (1 << BUTTON);
    initInterrupt0();
}

int main(void)
{
    setup();
    while (1)
    {
        _delay_ms(200);
        LED_PORT ^= (1 << LED0);
    }
    return 0;
}
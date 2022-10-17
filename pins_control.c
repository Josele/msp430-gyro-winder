/*
 * pins_control.c
 *
 *  Created on: 11 Oct 2022
 *      Author: Josele
 */
#include "pins_control.h"
#include <msp430.h>

uint8_t pin_setup(uint8_t pin, pin_direction_t dir )
{
   if(pin > 7)
   {
       return 1;
   }
   else if (OUTPUT == dir)
   {
       P1DIR |= (0x1U << pin);                            // Set P1.0, P1.1, P1.2 and P1.3  to output direction
   }
   else
   {
       P1DIR &= ~(0x1U << pin);
   }
   return 0;
}

uint8_t digital_write(uint8_t pin, pin_state_t state )
{
    if(pin > 7)
    {
        return 1;
    }
    if(state == HIGH)
    {
        P1OUT |= (0x1U << pin);                          // Toggle P1.0 using exclusive-OR
    }else
    {
        P1OUT &= ~(0x1U << pin);
    }
    return 0;
}






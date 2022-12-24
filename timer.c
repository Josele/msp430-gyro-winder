/*
 * timer.c
 *
 *  Created on: 12 Oct 2022
 *      Author: Josele
 */
#include "timer.h"
#include <msp430.h>

#define TIMER_MAX_MILLI_SEC 5400UL

// Delay function implemented with MCU's Timer.
// Max sleep time defined by the parameter size.
void delay_time_ms(volatile uint16_t ms) {
    //TBD: choosing different timer if it is currently being used.
    int cnt_sleep = 0;
    int rem_sleep = 0;

    cnt_sleep = ms/TIMER_MAX_MILLI_SEC;
    rem_sleep = ms%TIMER_MAX_MILLI_SEC;
    // The timer may be smaller than the ms,
    // so we have to wait several cycles.
    for(;cnt_sleep > 0;cnt_sleep--)
    {
        CCTL0 = CCIE;                             // TACCTL0 interrupt enabled
        CCR0 =  TIMER_MAX_MILLI_SEC*12;           // CCR0 count
        TACTL = TASSEL_1 + MC_1;                  // ACLK  +, upmode,  32 kHz
        __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
    }
    CCTL0 = CCIE;                                 // TACCTL0 interrupt enabled
    CCR0 =  rem_sleep*12;                         // CCR0 count
    TACTL = TASSEL_1 + MC_1;                  // ACLK  +, upmode,  32 kHz
    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    TACTL = TASSEL_1 + MC_0;                  // ACLK  +, upmode,  32 kHz
    __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}

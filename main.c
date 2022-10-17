
//******************************************************************************
//  MSP430F20xx - gyro_winder
//
//  Description;
//                MSP430F20xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//******************************************************************************

#include <msp430.h>
#include "pins_control.h"
#include "timer.h"

/* Constants */
#define PINA 1
#define PINB 2
#define PINC 3
#define PIND 4
#define NUMBER_OF_STEPS_PER_REV 510

#define bool uint8_t
#define true 1
#define false 0
#define HALT_STEP 8

// Configuring direction of the PINs
void pins_setup(void)
{
    pin_setup(PINA,OUTPUT);  // Set P1.0, P1.1, P1.2 and P1.3  to output direction
    pin_setup(PINB,OUTPUT);  // Set P1.0, P1.1, P1.2 and P1.3  to output direction
    pin_setup(PINC,OUTPUT);  // Set P1.0, P1.1, P1.2 and P1.3  to output direction
    pin_setup(PIND,OUTPUT);  // Set P1.0, P1.1, P1.2 and P1.3  to output direction
}

// Initial configuration of the MCU
void board_init(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
    BCSCTL3 |= LFXT1S_2;        // ACLK = VLO   32768 hy
    BCSCTL1 = CALBC1_1MHZ;      // 8MHz cal value
    DCOCTL = CALDCO_1MHZ;       // 8MHz cal value
}

// Write coil value configuration of a 28BZJ-48.
void stepper_write(uint8_t a,uint8_t b,uint8_t c,uint8_t d){
    digital_write(PINA,a);
    digital_write(PINB,b);
    digital_write(PINC,c);
    digital_write(PIND,d);
}

// Sets the 28BZJ-48 into a specific step.
void stepper_set_to_step(uint8_t stepNum)
{
    switch(stepNum)
    {
    case 0:
      stepper_write(1,0,0,0);
      break;
    case 1:
      stepper_write(1,1,0,0);
      break;
    case 2:
     stepper_write(0,1,0,0);
      break;
    case 3:
      stepper_write(0,1,1,0);
      break;
    case 4:
      stepper_write(0,0,1,0);
      break;
    case 5:
      stepper_write(0,0,1,1);
      break;
    case 6:
      stepper_write(0,0,0,1);
      break;
    case 7:
      stepper_write(1,0,0,1);
      break;
    default:
      stepper_write(0,0,0,0);
      break;
    }
}

// Performs a full turn of the stepper motor
void stepper_full_turn(uint16_t usDelay, bool clockWise)
{
    int i;
    if(clockWise == true){
        for(i=0;i<8;i++)
        {
            stepper_set_to_step(i);
            delay_time_ms(usDelay);
        }
    }
    else
    {
        for(i=8;i>=0;i--)
        {
            stepper_set_to_step(i);
            delay_time_ms(usDelay);
        }
    }

}

int main(void)
{
  //Initialization
  board_init();
  pins_setup();

  // Manual delay Freq BIT
  delay_time_ms(2000);
  pin_setup(0,OUTPUT);
  // 2 seconds delay with LED0 on.
  digital_write(0,HIGH);
  delay_time_ms(2000);
  digital_write(0,LOW);
  delay_time_ms(2000);


  for (;;)
  {
      int i = 0;
      int j = 0;
        for(j = 0;j<3;j++){
          while(i<NUMBER_OF_STEPS_PER_REV){
            stepper_full_turn(1,true);
            i++;
          }
          while(i>=0){
            stepper_full_turn(1,false);
            i--;
          }
        }
        stepper_set_to_step(HALT_STEP);
        delay_time_ms(0xFFFFUL);

  }
}




/*
 * pins_control.h
 *
 *  Created on: 11 Oct 2022
 *      Author: Josele
 */

#ifndef INCLUDES_PINS_CONTROL_H_
#define INCLUDES_PINS_CONTROL_H_
#include <stdint.h>

typedef enum {
  OUTPUT,
  INPUT,
} pin_direction_t ;

typedef enum {
  HIGH = 1,
  LOW = 0,
} pin_state_t ;

uint8_t pin_setup(uint8_t pin, pin_direction_t dir );
uint8_t digital_write(uint8_t pin, pin_state_t state );


#endif /* INCLUDES_PINS_CONTROL_H_ */

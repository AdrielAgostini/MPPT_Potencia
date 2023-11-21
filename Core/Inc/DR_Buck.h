/*
 * DR_Buck.h
 *
 *  Created on: Sep 27, 2023
 *      Author: adominguez
 */

#ifndef INC_DR_BUCK_H_
#define INC_DR_BUCK_H_

#include "stm32f1xx_hal.h"

#define BUCK_IN     1
#define BUCK_OUT    2
#define PERIOD      360 //Period of PWM for 200 KHz


void BUCK_init (void);
uint16_t getduty(int8_t );
void setduty (int8_t , int16_t );

#endif /* INC_DR_BUCK_H_ */

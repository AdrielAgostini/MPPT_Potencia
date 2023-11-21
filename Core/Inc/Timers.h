/*
 * Timers.h
 *
 *  Created on: Sep 27, 2023
 *      Author: adominguez
 */

#ifndef INC_TIMERS_H_
#define INC_TIMERS_H_

#include "stm32f1xx_hal.h"

void TimerStart(uint8_t ntimer,uint32_t time, void (*handler) (void));
void TimerEvent(void);

void HAL_IncTick(void);

#endif /* INC_TIMERS_H_ */

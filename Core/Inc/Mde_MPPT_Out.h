/*
 * Mde_MPPT_Out.h
 *
 *  Created on: Nov 7, 2023
 *      Author: adrie
 */

#ifndef INC_MDE_MPPT_OUT_H_
#define INC_MDE_MPPT_OUT_H_

#include "PR_Buck.h"
#include "DR_ADC.h"
#include "Timers.h"



#define SCAN 0
#define IDDLE 1

#define IDDLE_TIME_OUT 200 // in ms


void Mde_MPPT_Out(void);

void T_Hand_Out(void);

#endif /* INC_MDE_MPPT_OUT_H_ */

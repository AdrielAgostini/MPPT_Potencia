/*
 * Mde_MPPT_In.h
 *
 *  Created on: Nov 9, 2023
 *      Author: adrie
 */

#ifndef INC_MDE_MPPT_IN_H_
#define INC_MDE_MPPT_IN_H_

#include "PR_Buck.h"
#include "DR_ADC.h"
#include "Timers.h"

#define P_SLOPE 0
#define N_SLOPE 1
#define IDDLE 2




void Mde_MPPT_In(void);
void T_Hand_IN(void);


#endif /* INC_MDE_MPPT_IN_H_ */

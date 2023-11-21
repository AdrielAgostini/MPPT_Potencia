/*
 * PR_Buck.h
 *
 *  Created on: Nov 7, 2023
 *      Author: adrie
 */

#ifndef INC_PR_BUCK_H_
#define INC_PR_BUCK_H_

#include "DR_Buck.h"

#define VOUT_MAX 4190 // in mV
#define IOUT_MAX 500 //  in mA
#define IOUT_MIN 20
#define IOUT_K 20 //in percentage

#define BUCK_IN  1
#define BUCK_OUT 2


void duty_out_dec (int16_t , int16_t );
void duty_out_inc (int16_t , int16_t );
void duty_out_off();

void duty_in_dec (int16_t , int16_t );
void duty_in_inc (int16_t , int16_t );
void duty_in_off(void);


#endif /* INC_PR_BUCK_H_ */

/*
 * DR_ADC.h
 *
 *  Created on: Nov 7, 2023
 *      Author: adrie
 */

#ifndef INC_DR_ADC_H_
#define INC_DR_ADC_H_

#define VOUT    0
#define VIN     1
#define VINTRM  2
#define IOUT    3
#define IIN     4

/*Las mediciones estan expresadas en mV y mA*/

#define N_BITS  4095
#define V_REF   3300
#define I_OFFSET 62500   //Offset sensor de corriente en e-4 A
#define I_SENS  25     //Pendiente sensor de corriente en e-4 A/mV
#define I_SENS_OUT  257     //Pendiente sensor de corriente en e-5 A/mV
/*
    La ecuacion de del sensor de corriente es:
        Vout = I * m + b
        m = 400 mV/A
        b = 2500 mV
    Para transformar a corriente nuevamente 
        I = (Vout - b) / m => I = Vout * m2 - b2
        m2 = 0.0025 A/mV
        b2 = 6,25 A
    Para trabajar mas comodamente convierto a 1*e-4 A
        m2 = 25 *e-4 A/mV => Pendiente
        b2 = 62500 *e-4 mA   => Offset
*/

#define RDIV_N_1 39 //Numerador Divisor resistivo para VIN
#define RDIV_D_1 5  //Denominador Divisor resistivo para VIN
#define RDIV_N_2 2  //Numerador Divisor resistivo para VOUT e I_in
#define RDIV_D_2 1  //Numerador Divisor resistivo para VOUT e I_in
#define RDIV_N_3 155 //Numerador Divisor resistivo para I_out
#define RDIV_D_3 100 //Denominador Divisor resistivo para I_out
#define RDIV_N_4 83 //Numerador Divisor resistivo para  VMED
#define RDIV_D_4 43 //Denominador Divisor resistivo para VMED

#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;


void MX_ADC1_Init(void);

void ADC_Select_CH0 (void);

void ADC_Select_CH1 (void);

void ADC_Select_CH2 (void);

void ADC_Select_CH3 (void);

void ADC_Select_CH4 (void) ;

uint16_t getValue(uint8_t );

int16_t value_conversion(uint16_t , uint8_t );

#endif /* INC_DR_ADC_H_ */

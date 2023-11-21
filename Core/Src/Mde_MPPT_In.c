#include "Mde_MPPT_In.h"

#define P_SLOPE 0
#define N_SLOPE 1
#define IDDLE 2

#define IDDLE_TIME 50 // in ms

uint8_t tflag_in=0;
uint32_t vin_m=0, iin_m=0;
uint32_t pin_m=0;

void Mde_MPPT_In(void){
    static int8_t state = P_SLOPE;
    static int8_t slope = 1;
    static int32_t pin_prev = 0;
    switch (state){
        case P_SLOPE:
            vin_m = getValue (VIN);
            iin_m = getValue (IIN);
            pin_m = vin_m * iin_m / 100000;
            if (pin_m >= pin_prev){
                duty_in_inc(vin_m, iin_m);
                slope = 1;
            }else {
                duty_in_dec(vin_m, iin_m);
                slope=-1;
            }
            pin_prev = pin_m;
            state=IDDLE;
            TimerStart (0,IDDLE_TIME,&T_Hand_IN);

            break;
        case N_SLOPE:
            vin_m = getValue (VIN);
            iin_m = getValue (IIN);
            pin_m = vin_m * iin_m /100000;
            if (pin_m >= pin_prev){
                duty_in_dec(vin_m, iin_m);
                slope = -1;
            }else {
                duty_in_inc(vin_m, iin_m);
                slope = 1;
            }
            pin_prev = pin_m;
            state=IDDLE;            
            TimerStart (0,IDDLE_TIME,&T_Hand_IN);
            break;

        case IDDLE:
            if (tflag_in==1){
                tflag_in=0;
                if (slope == 1)
                    state = P_SLOPE;
                else state = N_SLOPE;
            }break;
        default: 
            TimerStart (0,IDDLE_TIME,&T_Hand_IN);
            state=IDDLE;
    }
}

void T_Hand_IN(void){
    tflag_in=1;
}

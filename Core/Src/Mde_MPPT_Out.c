
#include "Mde_MPPT_Out.h"


#define SCAN 0
#define IDDLE 1

#define IDDLE_TIME 100 // in ms


uint8_t tflag_out=0;

void Mde_MPPT_Out(void){
    static int8_t state = SCAN;
    int16_t vout_m=0, iout_m=0;
    switch (state){
        case SCAN:
            vout_m = getValue (VOUT);
            iout_m = getValue (IOUT);

            if (vout_m > VOUT_MAX || iout_m > IOUT_MAX){
                duty_out_dec(vout_m, iout_m);
                if (iout_m < IOUT_MIN)
                    duty_out_off();
            }else duty_out_inc(vout_m, iout_m);
            if (vout_m < 2500)
				duty_out_off();
            TimerStart (0,IDDLE_TIME_OUT,&T_Hand_Out);
            serial_send_4();
            state=IDDLE;
            break;
        case IDDLE:
            if (tflag_out==1){
                tflag_out=0;
                state=SCAN;
            }break;
        default: 
            TimerStart (0,IDDLE_TIME_OUT,&T_Hand_Out);
            state=IDDLE;
    }
}

void T_Hand_Out(void){
    tflag_out=1;
}

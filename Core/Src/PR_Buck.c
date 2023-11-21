#include "PR_Buck.h"

#define DUTY_DELTA_IN 2
#define DUTY_DELTA_OUT 2


void duty_out_dec (int16_t vout_m, int16_t iout_m){

    uint16_t act_duty, nxt_duty;
    uint16_t delta_duty = 0;
    act_duty = getduty(BUCK_OUT);

    if (iout_m > 600)
        	delta_duty = 7;
        	else delta_duty =2;
        if (iout_m > 700)
            delta_duty = 14;
        if (iout_m > 800)
            delta_duty = 22;
        if (iout_m > 900)
            delta_duty = 29;
     nxt_duty = act_duty - delta_duty;
    if (nxt_duty > 360)
        nxt_duty = 0;
    setduty(BUCK_OUT,nxt_duty);
    
    /*
    uint16_t vout_rel, iout_rel, act_duty, nxt_duty;

    vout_rel = vout_m*100 / VOUT_MAX;
    iout_rel = iout_m*100 / IOUT_MAX;
    act_duty = getduty(BUCK_OUT);
    if (vout_rel > iout_rel){
        nxt_duty = (100*act_duty) / vout_rel;
        
    }else nxt_duty = (IOUT_K*act_duty) / vout_rel;
    setduty(BUCK_OUT,nxt_duty);
    */
}

void duty_out_inc (int16_t vout_m, int16_t iout_m){ 
    uint16_t act_duty, nxt_duty;
    uint16_t delta_duty = 0;
    if (iout_m < 400)
    	delta_duty = 7;
    	else delta_duty =2;
    if (iout_m < 300)
        delta_duty = 14;
    if (iout_m < 200)
        delta_duty = 22;
    if (iout_m < 100)
        delta_duty = 29;
    act_duty = getduty(BUCK_OUT);
    nxt_duty = act_duty + delta_duty;
    if (nxt_duty > 360)
        nxt_duty = 360;
    setduty(BUCK_OUT,nxt_duty);
    /*
    uint16_t vout_rel, iout_rel, act_duty, nxt_duty;

    if (vout_m < 42)
        vout_m = 42;
    if (iout_m < 5)
        iout_m = 5;

    vout_rel = vout_m*100 / VOUT_MAX;
    iout_rel = iout_m*100 / IOUT_MAX;

    act_duty = getduty(BUCK_OUT);

    if (vout_rel < iout_rel){
        nxt_duty = (100*act_duty) / vout_rel;
        
    }else nxt_duty = (IOUT_K*act_duty) / iout_rel;
    if (nxt_duty > 100)
        nxt_duty = 100;
    setduty(BUCK_OUT,nxt_duty);
    */
}

void duty_out_off(){
    uint16_t nxt_duty=0;
    setduty(BUCK_OUT,nxt_duty);
}


void duty_in_dec (int16_t vout_m, int16_t iout_m){
    // uint16_t vout_rel, iout_rel, act_duty, nxt_duty;
    uint16_t act_duty, nxt_duty;
    act_duty = getduty(BUCK_IN);
    nxt_duty = act_duty - DUTY_DELTA_IN;
    if (nxt_duty > 100)
        nxt_duty = 0;
    setduty(BUCK_IN,nxt_duty);
    /*
    vout_rel = vout_m*100 / VOUT_MAX;
    iout_rel = iout_m*100 / IOUT_MAX;
    act_duty = getduty(BUCK_OUT);
    if (vout_rel > iout_rel){
        nxt_duty = (100*act_duty) / vout_rel;
        
    }else nxt_duty = (IOUT_K*act_duty) / vout_rel;
    setduty(BUCK_OUT,nxt_duty);
    */
}

void duty_in_inc (int16_t vout_m, int16_t iout_m){
        uint16_t act_duty, nxt_duty;
    act_duty = getduty(BUCK_IN);
    nxt_duty = act_duty + DUTY_DELTA_IN;
    if (nxt_duty > 100)
        nxt_duty = 100;
    setduty(BUCK_IN,nxt_duty);    
    /*
    uint16_t vout_rel, iout_rel, act_duty, nxt_duty;

    vout_rel = vout_m*100 / VOUT_MAX;
    iout_rel = iout_m*100 / IOUT_MAX;
    act_duty = getduty(BUCK_OUT);
    if (vout_rel < iout_rel){
        nxt_duty = (100*act_duty) / vout_rel;
        
    }else nxt_duty = (IOUT_K*act_duty) / vout_rel;
    setduty(BUCK_OUT,nxt_duty);
    */
}

void duty_in_off(){
    uint16_t nxt_duty=0;
    setduty(BUCK_IN,nxt_duty);
}

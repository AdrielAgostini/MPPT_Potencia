#include "DR_Buck.h"           


void BUCK_init (void){
    setduty (BUCK_IN , 0);
    setduty (BUCK_OUT , 0);
}

uint16_t getduty(int8_t buck){
    uint16_t aux;
    uint16_t duty;
    switch (buck){
        case BUCK_OUT:
            aux = TIM3->CCR2;
            break;
        case BUCK_IN:
            aux = TIM3->CCR1;
            break;
    }duty = aux;
    return duty;
}

void setduty (int8_t selection , int16_t duty){
    uint16_t aux;

    switch (selection){
        case BUCK_OUT:
            TIM3->CCR2 = duty;
            break;
        case BUCK_IN:
            TIM3->CCR1 = duty;
            break;
    }
}

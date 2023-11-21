/*
 * Timers.c
 *
 *  Created on: Sep 27, 2023
 *      Author: adominguez
 */
#include "Timers.h"
#define MAX_T 3

uint32_t timer[MAX_T];
uint8_t flag_timer[MAX_T];
void ( * handler_timer[MAX_T])(void);

void TimerStart(uint8_t ntimer,uint32_t time, void (*handler) (void)){
	timer[ntimer]=time;
	handler_timer[ntimer]=handler;
	flag_timer[ntimer]=0;
}

void TimerEvent(void){
	for (uint8_t i=0;i<MAX_T;i++){
		if (flag_timer[i]==1){
			flag_timer[i]=0;
			handler_timer[i]();
		}
	}
}


/*El SysTick esta configurado en 1 mS por default en HAL_Init()*/
void HAL_IncTick(void){
	uwTick += uwTickFreq;
	for (uint8_t i=0; i<MAX_T; i++){
		if(timer[i]!=0){
			timer[i]--;
			if (timer[i]==0)
				flag_timer[i]=1;
		}
	}
}

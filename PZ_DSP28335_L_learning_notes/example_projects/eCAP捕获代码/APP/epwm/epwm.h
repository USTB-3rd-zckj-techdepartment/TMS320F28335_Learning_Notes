/*
 * epwm.h
 *
 *  Created on: 2018-1-26
 *      Author: Administrator
 */

#ifndef EPWM_H_
#define EPWM_H_


#include "DSP2833x_Device.h"     // DSP2833x 头文件
#include "DSP2833x_Examples.h"   // DSP2833x 例子相关头文件


void EPWM1_Init(Uint16 tbprd);
void EPwm1A_SetCompare(Uint16 val);
void EPwm1B_SetCompare(Uint16 val);

void EPWM6_Init(Uint16 tbprd);
void EPwm6A_SetCompare(Uint16 val);
void EPwm6B_SetCompare(Uint16 val);


// Configure the start/end period for the timer
#define PWM3_TIMER_MIN     10
#define PWM3_TIMER_MAX     8000

// To keep track of which way the timer value is moving
#define EPWM_TIMER_UP   1
#define EPWM_TIMER_DOWN 0

void EPWM3_Init(Uint16 tbprd);


// Configure the start/end period for the timer
#define PWM5_TIMER_MIN     10
#define PWM5_TIMER_MAX     8000

void EPWM5_Init(Uint16 tbprd);
void EPwm5A_SetCompare(Uint16 val);
void EPwm5B_SetCompare(Uint16 val);
#endif /* EPWM_H_ */

#ifndef _WAVE_H
#define _WAVE_H

#include "sys.h"
#define Trig_center GPIO_Pin_1//引脚改
#define Echo_center GPIO_Pin_0//引脚改
#define Trig_left GPIO_Pin_6
#define Echo_left GPIO_Pin_7
#define Trig_right GPIO_Pin_8
#define Echo_right GPIO_Pin_9

void Wave_SRD_Init(void);        //超声波模块的初始化

void Wave_SRD_Strat(GPIO_TypeDef* GPIOx,u16 Trig);         //超声波模块本省的触发条件，大于10us的触发

#endif


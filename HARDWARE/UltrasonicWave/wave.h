#ifndef _WAVE_H
#define _WAVE_H

#include "sys.h"
#define Trig_center GPIO_Pin_1//���Ÿ�
#define Echo_center GPIO_Pin_0//���Ÿ�
#define Trig_left GPIO_Pin_6
#define Echo_left GPIO_Pin_7
#define Trig_right GPIO_Pin_8
#define Echo_right GPIO_Pin_9

void Wave_SRD_Init(void);        //������ģ��ĳ�ʼ��

void Wave_SRD_Strat(GPIO_TypeDef* GPIOx,u16 Trig);         //������ģ�鱾ʡ�Ĵ�������������10us�Ĵ���

#endif


#ifndef __MOTOR_H
#define __MOTOR_H 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define RIO PAout(2)//右轮PA2控制
#define LIO PAout(3) //左轮PA3控制

void motor_Init(void);//初始�
void forward(void);
void right(void);
void left(void);
void back(void);
void brake(void);


		 				    
#endif

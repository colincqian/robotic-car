#ifndef __MOTOR_H
#define __MOTOR_H 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define RIO PAout(2)//����PA2����
#define LIO PAout(3) //����PA3����

void motor_Init(void);//��ʼ�
void forward(void);
void right(void);
void left(void);
void back(void);
void brake(void);


		 				    
#endif

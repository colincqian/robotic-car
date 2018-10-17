#ifndef __MOTOR_H
#define __MOTOR_H 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//LEDÇı¶¯´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2012/9/2
//°æ±¾£ºV1.0
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define RIO PAout(2)//ÓÒÂÖPA2¿ØÖÆ
#define LIO PAout(3) //×óÂÖPA3¿ØÖÆ

void motor_Init(void);//³õÊ¼»
void forward(void);
void right(void);
void left(void);
void back(void);
void brake(void);


		 				    
#endif

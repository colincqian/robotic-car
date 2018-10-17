#include "led.h"
#include "motor.h"
#include "timer.h"
#include "delay.h"

//RIO LIO¸ßµçÆ½ µç»úË³Ê±Õë×ª¶¯ ÓÒÂÖºóÍË ×óÂÖÇ°½ø          ÕûÌå×ó×ª
//RIO¸ßµçÆ½ LIOµÍµçÆ½ ¯ÓÓÒÂÖË³Ê±Õë  ×óÂÖÄæÊ±Õë ÓÒÇ° ×óÇ°  ÕûÌåÇ°½ø
//RIOµÍµçÆ½ LIO¸ßµçÆ½½ ¯ÓÓÒÂÖÄæÊ±Õë  ×óÂÖË³Ê±Õë ÓÒºó×óºó   ÕûÌåÏòºó
//RIO LIO µÍµçÆ½   µç»úÄæÊ±Õë×ª¶¯                         ÕûÌåÓÒ×ª

void motor_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //Ê¹ÄÜPA¶Ë¿ÚÊ±ÖÓ
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
 GPIO_ResetBits(GPIOA,GPIO_Pin_2);						

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 
 GPIO_SetBits(GPIOA,GPIO_Pin_3); 		
TIM_SetCompare1(TIM3,899);	
TIM_SetCompare2(TIM3,899);
	
}

void forward()
{
	//GPIO_SetBits(GPIOA,GPIO_Pin_2);
	TIM_SetCompare1(TIM3,400);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	TIM_SetCompare2(TIM3,800);
	RIO=1; //ÓÒÂÖÇ°½ø
	LIO=0; //×óÂÖÇ°½ø
}

void left()
{
	TIM_SetCompare2(TIM3,800);
	TIM_SetCompare1(TIM3,899);
	RIO=0;
	LIO=0;
}

void right()
{
	TIM_SetCompare2(TIM3,899);
	TIM_SetCompare1(TIM3,400);
	RIO=1;	
	LIO=1;	
}

void back()
{
	TIM_SetCompare1(TIM3,700);
  TIM_SetCompare2(TIM3,700);
	RIO=0;
	LIO=0;
}

void brake()//ĞèÒªUĞÍBACK
{
                            //Ê¹ÄÜ¸ßµçÆ½ÓĞĞ§
	TIM_SetCompare1(TIM3,899);//ÊıÖµºÍÕ¼¿Õ±È³É·´±È;
	TIM_SetCompare2(TIM3,899);
	RIO=1;
	LIO=0;
	delay_ms(500);
}


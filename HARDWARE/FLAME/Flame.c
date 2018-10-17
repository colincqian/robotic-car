#include "led.h"
#include "flame.h"

 
void flame_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitSture;
		//配置IO端口
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_0;                //将PE0
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);	
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_1;                //将PE1
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);	

	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_2;                //将PE2
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
  GPIO_ResetBits(GPIOE,GPIO_Pin_2);	
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_3;                //将PE3
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);	
	
  GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_4;                //将PE4
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
}
	
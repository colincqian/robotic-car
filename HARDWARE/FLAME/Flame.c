#include "led.h"
#include "flame.h"

 
void flame_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitSture;
		//����IO�˿�
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_0;                //��PE0
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);	
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_1;                //��PE1
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);	

	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_2;                //��PE2
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
  GPIO_ResetBits(GPIOE,GPIO_Pin_2);	
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_3;                //��PE3
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);	
	
  GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_4;                //��PE4
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture); 
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
}
	
//所有标注引脚改的地方为可变动引脚
#include "wave.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "wave.h"
#include "stm32f10x_exti.h"
float Distancef;
float Distancer;
float Distancel;
static float f0,r0,l0;
void Wave_SRD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitSture;
	EXTI_InitTypeDef  EXTI_InitSture;
	NVIC_InitTypeDef  NVIC_InitSture;
	//如果外部中断的话则一定使能AFIO复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//引脚改
	
	
	//配置IO端口
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   //推挽输出模式
	GPIO_InitSture.GPIO_Pin=Trig_center;                //将PA0与TRIG相连
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture); //引脚改
	GPIO_InitSture.GPIO_Pin=Trig_left;
	GPIO_Init(GPIOB,&GPIO_InitSture);
	GPIO_InitSture.GPIO_Pin=Trig_right;
	GPIO_Init(GPIOB,&GPIO_InitSture);
	
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //拉输入模式
	GPIO_InitSture.GPIO_Pin=Echo_center;                //将PA1与ECHO相连
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture); //引脚窯
	GPIO_InitSture.GPIO_Pin=Echo_left; 
	GPIO_Init(GPIOB,&GPIO_InitSture);
	GPIO_InitSture.GPIO_Pin=Echo_right; 
	GPIO_Init(GPIOB,&GPIO_InitSture);
	
	
	//中断和6端口映射一起
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//引脚改
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
	
	
	//外部中断配置
	EXTI_InitSture.EXTI_Line=EXTI_Line0;//引脚改
	EXTI_InitSture.EXTI_LineCmd=ENABLE;
	EXTI_InitSture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger=EXTI_Trigger_Rising;//高电平触发
	EXTI_Init(&EXTI_InitSture);
	EXTI_InitSture.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitSture);
	EXTI_InitSture.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitSture);
	
	
	//中断优先级管理
	NVIC_InitSture.NVIC_IRQChannel=EXTI0_IRQn;//中央超声测距
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitSture);
	
	NVIC_InitSture.NVIC_IRQChannel=EXTI9_5_IRQn;//左侧超声测距
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitSture);
	
	NVIC_InitSture.NVIC_IRQChannel=EXTI9_5_IRQn;//右侧超声测距
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitSture);
}

void EXTI0_IRQHandler(void)//中央测距中断函数
{
	delay_us(10);
	
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//发生中断//引脚改
	{
		TIM_SetCounter(TIM5,0);//计时器清零
		TIM_Cmd(TIM5,ENABLE);  //开始计时
		
		while(GPIO_ReadInputDataBit(GPIOA,Echo_center));  //等待低电平//引脚改
		TIM_Cmd(TIM5,DISABLE);//关闭定时器
		
		Distancef=TIM_GetCounter(TIM5)*340/200.0;//计算距离
		if(Distancef>200||Distancef==0) Distancef=f0;
		else f0=Distancef;
		
		EXTI_ClearITPendingBit(EXTI_Line0);//引脚改
	}
}

void  EXTI9_5_IRQHandler(void)//左侧测距中断函数
{
	delay_us(10);
	
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//发生中断//引脚改
	{
		TIM_SetCounter(TIM4,0);//计时器清零
		TIM_Cmd(TIM4,ENABLE);  //开始计时
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7));  //等待低电平//引脚改
		TIM_Cmd(TIM4,DISABLE);//关闭定时器
		
		Distancel=TIM_GetCounter(TIM4)*340/200.0;//计算距离
		if(Distancel>200||Distancel==0) Distancel=l0;
		else l0=Distancel;	
		EXTI_ClearITPendingBit(EXTI_Line7);//引脚改
	}
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//发生中断//引脚改
	{
		TIM_SetCounter(TIM6,0);//计时器清零
		TIM_Cmd(TIM6,ENABLE);  //开始计时
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));  //等待低电平//引脚改
		TIM_Cmd(TIM6,DISABLE);//关闭定时器
		
		Distancer=TIM_GetCounter(TIM6)*340/200.0;//计算距离
		if(Distancer>200||Distancer==0) Distancer=r0;
		else r0=Distancer;		
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}


void Wave_SRD_Strat(GPIO_TypeDef* GPIOx,u16 Trig)
{
	GPIO_SetBits(GPIOx,Trig);   //将Trig设置为高电平 中央发射
	delay_us(20);               //持续大于10us触发，触发超声波模块工作
	GPIO_ResetBits(GPIOx,Trig);	//引脚改
	
}












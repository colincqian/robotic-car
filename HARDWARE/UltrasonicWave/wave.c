//���б�ע���Ÿĵĵط�Ϊ�ɱ䶯����
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
	//����ⲿ�жϵĻ���һ��ʹ��AFIO���ù���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//���Ÿ�
	
	
	//����IO�˿�
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   //�������ģʽ
	GPIO_InitSture.GPIO_Pin=Trig_center;                //��PA0��TRIG����
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture); //���Ÿ�
	GPIO_InitSture.GPIO_Pin=Trig_left;
	GPIO_Init(GPIOB,&GPIO_InitSture);
	GPIO_InitSture.GPIO_Pin=Trig_right;
	GPIO_Init(GPIOB,&GPIO_InitSture);
	
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=Echo_center;                //��PA1��ECHO����
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture); //���ŸG
	GPIO_InitSture.GPIO_Pin=Echo_left; 
	GPIO_Init(GPIOB,&GPIO_InitSture);
	GPIO_InitSture.GPIO_Pin=Echo_right; 
	GPIO_Init(GPIOB,&GPIO_InitSture);
	
	
	//�жϺ�6�˿�ӳ��һ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//���Ÿ�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
	
	
	//�ⲿ�ж�����
	EXTI_InitSture.EXTI_Line=EXTI_Line0;//���Ÿ�
	EXTI_InitSture.EXTI_LineCmd=ENABLE;
	EXTI_InitSture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger=EXTI_Trigger_Rising;//�ߵ�ƽ����
	EXTI_Init(&EXTI_InitSture);
	EXTI_InitSture.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitSture);
	EXTI_InitSture.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitSture);
	
	
	//�ж����ȼ�����
	NVIC_InitSture.NVIC_IRQChannel=EXTI0_IRQn;//���볬�����
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitSture);
	
	NVIC_InitSture.NVIC_IRQChannel=EXTI9_5_IRQn;//��೬�����
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitSture);
	
	NVIC_InitSture.NVIC_IRQChannel=EXTI9_5_IRQn;//�Ҳ೬�����
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitSture);
}

void EXTI0_IRQHandler(void)//�������жϺ���
{
	delay_us(10);
	
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//�����ж�//���Ÿ�
	{
		TIM_SetCounter(TIM5,0);//��ʱ������
		TIM_Cmd(TIM5,ENABLE);  //��ʼ��ʱ
		
		while(GPIO_ReadInputDataBit(GPIOA,Echo_center));  //�ȴ��͵�ƽ//���Ÿ�
		TIM_Cmd(TIM5,DISABLE);//�رն�ʱ��
		
		Distancef=TIM_GetCounter(TIM5)*340/200.0;//�������
		if(Distancef>200||Distancef==0) Distancef=f0;
		else f0=Distancef;
		
		EXTI_ClearITPendingBit(EXTI_Line0);//���Ÿ�
	}
}

void  EXTI9_5_IRQHandler(void)//������жϺ���
{
	delay_us(10);
	
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)//�����ж�//���Ÿ�
	{
		TIM_SetCounter(TIM4,0);//��ʱ������
		TIM_Cmd(TIM4,ENABLE);  //��ʼ��ʱ
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7));  //�ȴ��͵�ƽ//���Ÿ�
		TIM_Cmd(TIM4,DISABLE);//�رն�ʱ��
		
		Distancel=TIM_GetCounter(TIM4)*340/200.0;//�������
		if(Distancel>200||Distancel==0) Distancel=l0;
		else l0=Distancel;	
		EXTI_ClearITPendingBit(EXTI_Line7);//���Ÿ�
	}
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET)//�����ж�//���Ÿ�
	{
		TIM_SetCounter(TIM6,0);//��ʱ������
		TIM_Cmd(TIM6,ENABLE);  //��ʼ��ʱ
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));  //�ȴ��͵�ƽ//���Ÿ�
		TIM_Cmd(TIM6,DISABLE);//�رն�ʱ��
		
		Distancer=TIM_GetCounter(TIM6)*340/200.0;//�������
		if(Distancer>200||Distancer==0) Distancer=r0;
		else r0=Distancer;		
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}


void Wave_SRD_Strat(GPIO_TypeDef* GPIOx,u16 Trig)
{
	GPIO_SetBits(GPIOx,Trig);   //��Trig����Ϊ�ߵ�ƽ ���뷢��
	delay_us(20);               //��������10us����������������ģ�鹤��
	GPIO_ResetBits(GPIOx,Trig);	//���Ÿ�
	
}












#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "hc05.h"
#include "usart3.h"			 	 
#include "string.h"	   
#include "usmart.h"	
#include "oled.h"
#include "motor.h"
#include "timer.h"
#include "dht11.h"
#include "exti.h"
#include "wave.h"
#include "flame.h"

extern float Distancef;
extern float Distancer;
extern float Distancel;
extern u8 temperature;
extern u8 humidity;

 int main(void)
 {	 
	  u8 t,temp=5;
   	u8 sendcnt=0;
  	u8 sendbuf[20];	
  float dright;
	float dfront;
	float dleft;
	 
	delay_init();
  flame_Init();
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	Timer_SRD_Init(5000,7199);
	Wave_SRD_Init();	
	usmart_dev.init(72);
	LED_Init();
	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
			
   	//��ʼ��USMART		
 	OLED_Init();
	OLED_ShowString(0,0,"front:",16);  
	OLED_ShowString(0,16,"left:",16);	 
	OLED_ShowString(0,32,"right:",16); 
	 

	 
  TIM3_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
  motor_Init();    
	delay_ms(1000);	//�ȴ�����ģ���ϵ��ȶ�
	
 	while(HC05_Init());//��ʼ��ATK-HC05ģ��	
	USART3_RX_STA=0;
 	while(1) 
	{		

	 if(clk12==1) {u3_printf("FRONT!FIRE DETECTED!�\n");	 /*USART3_RX_BUF[1]='5';*/USART3_RX_STA|=1<<15;}//��⵽��������ͣ��
	 if(clk1==1)  {u3_printf("RIGHT FRONT!FIRE DETECTED!\n");	 /*USART3_RX_BUF[1]='5';*/USART3_RX_STA|=1<<15;}
	 if(clk2==1)  {u3_printf("RIGHT! FIRE DETECTED!\n");	   /*USART3_RX_BUF[1]='5';*/USART3_RX_STA|=1<<15;}
	 if(clk11==1) {u3_printf("LEFT FRONT! FIRE DETECTED!\n");	/*USART3_RX_BUF[1]='5';*/USART3_RX_STA|=1<<15;}
	 if(clk10==1) {u3_printf("LEFT! FIRE DETECTED!\n");	 /*USART3_RX_BUF[1]='5';*/USART3_RX_STA|=1<<15;}		
   if(USART3_RX_STA&0X8000)			//���յ�һ��������
		{  		 
			
			switch (USART3_RX_BUF[1]) {
				case '1':Show_DHT11();//��ʾ��ʪ��
								 u3_printf("temperature %d\r\n",temperature);	 
			  case '2':forward();
				case '3':Show_DHT11();//��ʾ��ʪ��
							   u3_printf("humidity %d\r\n",humidity);
				case '4':left();
				case '5':brake();
				case '6':right();
				case '8':back();
				case '9':///�Զ���ʻ����
					{
					u3_printf("entering auto mode \n");
					USART3_RX_STA=0;//ȷ���Ѿ����ܵ��л��ź�
					while(USART3_RX_BUF[1]=='9')
					{  
						if(USART3_RX_STA&0X8000)	
							{
							if(USART3_RX_BUF[1]=='9') {brake();u3_printf("ending auto mode\n");break;}
							}
						forward();//�Զ���ʻ����
				 
						Wave_SRD_Strat(GPIOA,Trig_center);//����������
						dfront=Distancef;	OLED_ShowNum(50,0,dfront,3,16);
						Wave_SRD_Strat(GPIOB,Trig_left);//����������
						dleft=Distancel;OLED_ShowNum(50,16,dleft,3,16);
						Wave_SRD_Strat(GPIOB,Trig_right);//����������
						dright=Distancer;OLED_ShowNum(50,32,dright,3,16);
						OLED_Refresh_Gram();  
						///dfront ǰ������	
						///dright �Ҳ����
						///dleft  ������
						///dback  �󷽾���
						if(dfront<35)
							{ 
								 if(dright<35&&dleft>35) 
									 {
										 left();
										 delay_ms(400);
									 }
								 else if(dright<35&&dleft<35) 
									 {
										 back();
										 delay_ms(400);
									 }
									else if(dright>35) 
									 {
										 right();
										 delay_ms(400);
									 }
						   }
					  else
							 {
								if(dright<35&&dleft>35)
									{
									 left();
									 delay_ms(400);
									}
								else if(dright<35&&dleft<35)
									{
									 forward();
									 delay_ms(200);
									}
								else if(dright>35&&dleft<35)
									{
									 right();
									 delay_ms(400);
									}
					 }
		 }
   
	}

			temp=USART3_RX_BUF[1];//������һ�εĶ���
 			USART3_RX_STA=0;	///��ձ�־λ	
}	 		

		delay_ms(5);
	}
}

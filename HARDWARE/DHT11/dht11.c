#include "dht11.h"
#include "delay.h"
#include "led.h"
#include "oled.h"
//复位DHT11
	  u8 temperature;  	    
	  u8 humidity; 
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//拉低DQ
    delay_ms(20);    	//拉低至少18ms
    DHT11_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在

u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)
	{
	  return 1;
	}
	else retry=0;
	
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
		
	};
	if(retry>=100)
	{
		return 1;	
	}		
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	while(DHT11_Init());
//	DHT11_Rst();
//	if(DHT11_Check()==0)
//	{
//		  LED1=!LED1;	
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		
		}
		if(((buf[0]+buf[1]+buf[2]+buf[3])&0xff)==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
			
		}
	//}else return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PB0端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOB,GPIO_Pin_0);						 //PB0输出高 总线空闲
			    
	DHT11_Rst();  //复位DHT11
	return DHT11_Check();//等待DHT11的回应
} 

void Show_DHT11()
{	    
			 
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值	
//      OLED_ShowString(0,0,"NUAA",24);  
//	    OLED_ShowString(0,24,"TEMP:",16);  
//	    OLED_ShowString(0,40,"HUMID:",16); 	
//   	  OLED_ShowNum(80,24,temperature,3,16);  
//			OLED_ShowNum(80,40,humidity,3,16);  
//	    OLED_Refresh_Gram();				   
//	 	  delay_ms(5);

}








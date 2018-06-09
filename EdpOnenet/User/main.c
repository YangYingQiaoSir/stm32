
#include "main.h"

int main(void)
{	
		delay_init();//注意时间的初始化
		SystemInit();
		LED_Init();    //LED指示灯初始化函数
		USART1_Init(); //USART1串口初始化函数
		USART2_Init(); //USART2串口初始化函数
	  DHT11_Init();
		while(1)
		{	
			  LED_Switch(LED_ON,LED_R|LED_G);	   //点亮开发板四个指示灯，表示程序进入主流程		
				ESP8266_Init();    //ESP8266初始化
				ESP8266_DevLink(DEVICEID,APIKEY,20);    //和平台建立设备连接
				LED_Switch(LED_OFF,LED_R|LED_G); //熄灭开发板四个指示灯，表示程序完成设备连接，进入数据发送循环
			
				while(1)
				{								
						if(!(ESP8266_CheckStatus(100)))    //检测ESP8266模块连接状态
						{
								ESP8266_SendDat();     //向平台发送数据
						}
						else
						{
								break;
						}
				}
		}	
}



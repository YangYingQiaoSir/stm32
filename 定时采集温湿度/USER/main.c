#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "dht11.h"

/************************************************
 ALIENTEKս��STM32������ʵ��8
 ��ʱ���ж�ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {		
	 u8 wd;
	 u8 sd;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TIM3_Int_Init(49990,7199);//10Khz�ļ���Ƶ�ʣ�������50000Ϊ5000ms  
   	while(1)
	{
		//if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1)
		//{
		
			if(flag == 1)
				{
	DHT11_Read_Data(&wd,&sd);  
  printf("wendu: %d ",wd);    
  printf("sidu: %d \r\n",sd); 
	flag=0;
				}
		//}
		LED0=!LED0;
		delay_ms(100);		   
	}	 

 
}	 
 

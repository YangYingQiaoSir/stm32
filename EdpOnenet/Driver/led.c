#include "main.h"


volatile unsigned char  red_value=0;
volatile unsigned char  green_value=0;


/**
  * @brief  LED指示灯初始化函数
**/
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //PE5--对应开发板绿指示灯;DS1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	
		//PB5---对应开发板红色指示灯；DS0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}


/**
  * @brief  分析平台下发的LED控制命令
**/
void LED_CmdCtl(void)
{
		if((NULL != strstr((const char *)usart2_cmd_buf, "LED red on")))  //约定平台控制命令"LED11"为打开红色LED灯
		{
				LED_RED_ON;	
				printf("receive message LED red on ");
				red_value=1;
		}
		if((NULL != strstr((const char *)usart2_cmd_buf, "LED green on")))  //约定平台控制命令"LED21"为打开绿色LED灯
		{
				LED_GREEN_ON;	
			  printf("receive message LED green on ");
				green_value=1;
		}
	
		
		if((NULL != strstr((const char *)usart2_cmd_buf, "LED red off")))  //约定平台控制命令"LED10"为关闭红色LED灯
		{
				LED_RED_OFF;
			  printf("receive message LED red off ");
				red_value=0;
		}
		if((NULL != strstr((const char *)usart2_cmd_buf, "LED green off")))  //约定平台控制命令"LED20"为关闭绿色LED灯
		{
				LED_GREEN_OFF;
			  printf("receive message LED green off ");
				green_value=0;	
		}

}

/**
  * @brief  LED指示灯操作函数，点亮和熄灭指示灯
**/
void LED_Switch(const u8 statu,const u8 mode)
{
		if(statu)
		{
				LED_RED_OFF;
				LED_GREEN_OFF;

			
				if(mode&0x01)
				{
						LED_RED_ON;
				}
				if(mode&0x02)
				{
						LED_GREEN_ON;
				}

		}
		else
		{
				if(mode&0x01)
				{
						LED_RED_OFF;
				}
				if(mode&0x02)
				{
						LED_GREEN_OFF;
				}

		}
}


/**
  * @brief  获取LED的当前状态值
**/
void LED_GetValue(void)
{
		if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5))
		{
				red_value=0;
		}
		else
		{
				red_value=1;
		}

		if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5))
		{
				green_value=0;
		}
		else
		{
				green_value=1;
		}

}








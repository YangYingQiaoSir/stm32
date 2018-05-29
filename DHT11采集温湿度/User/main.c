#include "stm32f10x.h"
#include "timer.h"
#include "usart.h"
#include "dht11.h"

#define Led_On   GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define Led_Off GPIO_ResetBits(GPIOB, GPIO_Pin_12)

void LED_Init()
{
    GPIO_InitTypeDef s;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    s.GPIO_Pin = GPIO_Pin_12;
    s.GPIO_Mode = GPIO_Mode_Out_PP;
    s.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &s);
}

int main()
{
	u8 buffer[5];
  double hum;
  double temp;
  SystemInit();
  systick_init();
	usart_config();    
	LED_Init();
	Led_On;
	while (1)
	{
			Led_On;
			if (dht11_read_data(buffer) == 0)
			{
					hum = buffer[0] + buffer[1] / 10.0;
					temp = buffer[2] + buffer[3] / 10.0;
			}
			usart_printf("{\"temperature\": %.2f, \"humidness\": %.2f}\n", temp, hum);
			delay_us(2000000);
			Led_Off;
			delay_us(2000000);
	}
}

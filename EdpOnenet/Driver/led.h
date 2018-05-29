#ifndef LED_H_H
#define LED_H_H

#define  LED_RED_OFF       GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define  LED_GREEN_OFF     GPIO_SetBits(GPIOE,GPIO_Pin_5)


#define  LED_RED_ON        GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define  LED_GREEN_ON      GPIO_ResetBits(GPIOE,GPIO_Pin_5)



#define  LED_R    0X01
#define  LED_G    0X02


#define  LED_OFF  0
#define  LED_ON   (!LED_OFF)

extern volatile unsigned char  red_value;
extern volatile unsigned char  green_value;

extern void LED_Init(void);
extern void LED_CmdCtl(void);
extern void LED_Switch(u8 statu,u8 mode);
extern void LED_GetValue(void);


#endif

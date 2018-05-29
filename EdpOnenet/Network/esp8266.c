#include "main.h"



EdpPacket* send_pkg;
char send_buf[MAX_SEND_BUF_LEN];


/**
  * @brief  ESP8266初始化
**/
void ESP8266_Init(void)
{
		printf("%s\r\n","[ESP8266_Init]ENTER AT.");
		//SendCmd(AT,"OK",1000); 	
		usart2_write(USART2,AT,strlen(AT));
		mDelay(1000);
		printf("%s\r\n","[ESP8266_Init]EXIT AT.");
		//LCD_ShowString(30,40,210,24,24,"AT");
		//delay_ms(200);
		
		printf("%s\r\n","[ESP8266_Init]ENTER CWMODE.");
		//SendCmd(CWMODE,"OK",1000);
		usart2_write(USART2,CWMODE,strlen(CWMODE));
		mDelay(1000);	
		printf("%s\r\n","[ESP8266_Init]EXIT CWMODE.");
		//LCD_ShowString(30,40,210,24,24,"CWMODE");
		//delay_ms(200);
	
		printf("%s\r\n","[ESP8266_Init]ENTER RST.");
		//SendCmd(RST,"OK",2000);	
		printf("%s\r\n","[ESP8266_Init]EXIT RST.");
		//LCD_ShowString(30,40,210,24,24,"RST");
		//delay_ms(200);
	
		printf("%s\r\n","[ESP8266_Init]ENTER CIFSR.");
		//SendCmd(CIFSR,"OK",1000);	
		usart2_write(USART2,CIFSR,strlen(CIFSR));
		mDelay(1000);
		printf("%s\r\n","[ESP8266_Init]EXIT CIFSR.");
		//LCD_ShowString(30,40,210,24,24,"CIFSR");
		//delay_ms(200);
	
		printf("%s\r\n","[ESP8266_Init]ENTER CWJAP.");
		//SendCmd(CWJAP,"OK",2200);
		usart2_write(USART2,CWJAP,strlen(CWJAP));
		mDelay(2000);		
		printf("%s\r\n","[ESP8266_Init]EXIT CWJAP.");
		//LCD_ShowString(30,40,210,24,24,"CWJAP");
		//delay_ms(200);
		

		printf("%s\r\n","[ESP8266_Init]ENTER CIPSTART.");
		//SendCmd(CIPSTART,"OK",2200);
		usart2_write(USART2,CIPSTART,strlen(CIPSTART));
		mDelay(2000);
		printf("%s\r\n","[ESP8266_Init]EXIT CIPSART.");
		//LCD_ShowString(30,40,210,24,24,"CIPSTART");
		//delay_ms(200);
		
		printf("%s\r\n","[ESP8266_Init]ENTER CIPMODE.");
		usart2_write(USART2,CIPMODE,strlen(CIPMODE));
		mDelay(1000);
		//SendCmd(CIPMODE,"OK",1000);
		printf("%s\r\n","[ESP8266_Init]EXIT CIPMODE.");
		//LCD_ShowString(30,40,210,24,24,"CIPMODE");
		//delay_ms(200);
}

/**
  * @brief  生成LED当前状态的上传数据，分割字符串格式
**/
void GetSendBuf(void)
{
		char text[25] = {0};
	  u8 hum;
    u8 temp;

		LED_GetValue();
		DHT11_Read_Data(&temp,&hum);
    printf("wendu: %d ",temp);    
    printf("sidu: %d \r\n",hum); 
		delay_us(2000000);
	  delay_us(2000000);
		memset(send_buf,0,MAX_SEND_BUF_LEN);
		
		strcat(send_buf, ",;");	
		strcat(send_buf, "red_statu,");
		sprintf(text,"%d",red_value);
		strcat(send_buf, text);
		strcat(send_buf, ";");
		
		strcat(send_buf, "green_statu,");
		sprintf(text,"%d",green_value);
		strcat(send_buf, text);
		strcat(send_buf, ";");
		
		strcat(send_buf, "temp_statu,");
		sprintf(text,"%d",temp);
		strcat(send_buf, text);
		strcat(send_buf, ";");

		strcat(send_buf, "hum_statu,");
		sprintf(text,"%d",hum);
		strcat(send_buf, text);
		strcat(send_buf, ";");
}


/**
  * @brief  发送一条AT指令
**/
void SendCmd(char* cmd, char* result, int timeOut)
{
    while(1)
    {
        memset(usart2_rcv_buf,0,sizeof(usart2_rcv_buf));
				usart2_rcv_len=0;
        usart2_write(USART2, (unsigned char *)cmd, strlen((const char *)cmd));
        mDelay(timeOut);
       
        if((NULL != strstr((const char *)usart2_rcv_buf, result)))	//判断是否有预期的结果
        {
            break;
        }
        else
        {
            mDelay(100);
        }
    }
}



/**
  * @brief  和平台建立设备连接
**/
void ESP8266_DevLink(const char* devid, const char* auth_key, int timeOut)
{
		int32 count=0;
	
		memset(usart2_rcv_buf,0,strlen((const char *)usart2_rcv_buf));
		usart2_rcv_len=0;			
		
		printf("%s\r\n","[ESP8266_DevLink]ENTER device link...");
		usart2_write(USART2,CIPSEND,strlen(CIPSEND));  //向ESP8266发送数据透传指令
		for(count=0;count<timeOut;count++)
		{
				mDelay(100);
				if((NULL != strstr((const char *)usart2_rcv_buf,">")))
				{
						break;
				}
		}	

		send_pkg = PacketConnect1(devid,auth_key);
		mDelay(200);
		usart2_write(USART2,send_pkg->_data,send_pkg->_write_pos);  //发送设备连接请求数据
		mDelay(500);
		DeleteBuffer(&send_pkg);
		mDelay(200);
		usart2_write(USART2,"+++",3);  //向ESP8266发送+++结束透传，使ESP8266返回指令模式
		mDelay(50);
		printf("%s\r\n","[ESP8266_DevLink]EXIT device link...");
}

/**
  * @brief  检测ESP8266连接状态
**/
int ESP8266_CheckStatus(int timeOut)
{
		int32 res=0;
		int32 count=0;
	
		memset(usart2_rcv_buf,0,sizeof(usart2_rcv_buf));
		usart2_rcv_len=0;
		
		printf("%s\r\n","[ESP8266_CheckStatus]ENTER check status...");
		usart2_write(USART2,CIPSTATUS,strlen(CIPSTATUS));
		for(count=0;count<timeOut;count++)
		{
				mDelay(100);
				if((NULL != strstr((const char *)usart2_rcv_buf,"STATUS:4")))  //失去连接
				{
						res=-4;
						break;
				}
				else if((NULL != strstr((const char *)usart2_rcv_buf,"STATUS:3")))  //建立连接
				{
						res=0;	
						break;
				}
				else if((NULL != strstr((const char *)usart2_rcv_buf,"STATUS:2")))  //获得IP
				{
						res=-2;
						break;				
				}
				else if((NULL != strstr((const char *)usart2_rcv_buf,"STATUS:5")))  //物理掉线
				{
						res=-5;
						break;
				}
				else if((NULL != strstr((const char *)usart2_rcv_buf,"ERROR")))   
				{
						res=-1;
						break;
				}
				else
				{
						;
				}
		}	
		printf("%s\r\n","[ESP8266_CheckStatus]EXIT check status...");
		return res;	
}

/**
  * @brief  向平台上传LED当前状态数据
**/
void ESP8266_SendDat(void)
{		
		int32 count=0;

		memset(usart2_rcv_buf,0,sizeof(usart2_rcv_buf));
		usart2_rcv_len=0;			
		printf("%s\r\n","[ESP8266_SendDat]ENTER Senddata...");
		usart2_write(USART2,CIPSEND,strlen(CIPSEND));  //向ESP8266发送数据透传指令
		for(count=0;count<40;count++)
		{
				mDelay(100);
				if((NULL != strstr((const char *)usart2_rcv_buf,">")))
				{
						break;
				}
		}	
	
		GetSendBuf();		
		send_pkg = PacketSavedataSimpleString(DEVICEID,send_buf);   
		usart2_write(USART2,send_pkg->_data,send_pkg->_write_pos);	//向平台上传数据点
		DeleteBuffer(&send_pkg);
		mDelay(500);

		usart2_write(USART2,"+++",3);  //向ESP8266发送+++结束透传，使ESP8266返回指令模式
		mDelay(200);
		printf("%s\r\n","[ESP8266_SendDat]EXIT Senddata...");
}










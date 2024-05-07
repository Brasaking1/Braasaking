#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Seriol.h"
#include <string.h>

 uint8_t RxData;

int main(void)
{
	OLED_Init();
	 LED_Init();
	
	SERIAL_Init();
	OLED_ShowString(1,1,"UESTC");
	OLED_ShowString(3,1,"maziqi");

	

	while(1)
	{
	if(Serial_GetRxFlag()==1)
	{
//		OLED_ShowString(4,1,"    			");
		OLED_ShowString(4,1,Serial_RXPacket);
		if(strcmp(Serial_RXPacket,"LED_ON")==0)
		{
			LED_1_ON();
			Serial_SendString("LED_ON_OK\r\n");
			OLED_ShowString(2,1,"LED_ON_OK");
		}
		else if(strcmp(Serial_RXPacket,"LED_OFF")==0)
		{
			LED_1_OFF();
			Serial_SendString("LED_OFF_OK\r\n");
			OLED_ShowString(2,1,"LED_OFF_OK");
		}
		else
		{
			Serial_SendString("ERROR_COMMAND\r\n");
			OLED_ShowString(2,1,"ERROR_COMMAND");
		}
	}
	}
}
 
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "LED.h"
#include "HCSR04.h"
float a;

 
int main(void)
{
	LED_Init();
	OLED_Init();
	Sr04_Init();
	OLED_ShowString(1,1,"length:");
	a=Sr04GetLength();//距离变量a
	while(1)
	{
		a=Sr04GetLength();
		OLED_ShowNum(2,1,a,4);
		if(a<10)
		{
			LED_1_ON();
		}
		else
		{
			LED_1_OFF();
		}
	}
}
 

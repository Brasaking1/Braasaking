#include "stm32f10x.h"                  // Device header
void LED_Init(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2 ;
		GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
        GPIO_Init( GPIOA,&GPIO_InitStructure);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);

	}
void LED_1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

void LED_1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED_2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED_2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
void LED1turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
	
	
}
void LED2turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	
	
}



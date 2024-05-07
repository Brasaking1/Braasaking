#include "stm32f10x.h"                  // Device header
#include <stdio.h>

#include <stdarg.h>

uint8_t Serial_RxFlag;
uint8_t Serial_TXPacket[4];
char Serial_RXPacket[100];
void SERIAL_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init( GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init( GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStruture;
	USART_InitStruture.USART_BaudRate=9600;//波特率
	USART_InitStruture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruture.USART_Parity=USART_Parity_No;
	USART_InitStruture.USART_StopBits=USART_StopBits_1;
	USART_InitStruture.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruture);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使用中断接收
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}
void SERIAL_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
}


void Serial_sendArray(uint8_t *Array,uint16_t Length)//发送数组
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		SERIAL_SendByte(Array[i]);
	}
}


void Serial_SendString(char*String)//发送字符串
{
	uint8_t i;
	for(i=0;String[i]!=0;i++)
	{
		SERIAL_SendByte(String[i]);
	}
}


uint32_t Serial_POW(uint32_t X,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result *=X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)//直接发送数字,在文本模式下使用！
{
		uint8_t i;
	for(i=0;i<Length;i++)
	{
		SERIAL_SendByte(Number/Serial_POW(10,Length-1-i)%10+0x30);
	}
}
	
int fputc(int ch,FILE*f)
{
	SERIAL_SendByte(ch);
	return ch;
}

void Serial_Printf(char*format,...)
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
    va_end(arg);
	Serial_SendString(String);
}

void Serial_SnedPacket(void)
{
	SERIAL_SendByte(0xFF);
	Serial_sendArray(Serial_TXPacket,4);
	SERIAL_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)
{
	if(Serial_RxFlag==1)
	{
		Serial_RxFlag=0;
		return 1;
	}
}




void USART1_IRQHandler(void)
{
	static uint8_t Rxstate=0;
	static uint8_t PRXpacket=0;

	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET	)
	{
		uint8_t Rxdate=USART_ReceiveData(USART1);
		if(Rxstate==0)
		{
			if(Rxdate=='@')
			{
				Rxstate=1;
				PRXpacket=0;
			}
		}
		else if(Rxstate==1)
		{
			if(Rxdate=='\r')
			{
				Rxstate=2;
			}
			else
			{
				Serial_RXPacket[PRXpacket]=Rxdate;
			PRXpacket++;
			}
		}

		else if(Rxstate==2)
		{
			if(Rxdate=='\n')
			{
				Rxstate=0;
				Serial_RXPacket[PRXpacket]='\0';
			Serial_RxFlag=1;
				
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}



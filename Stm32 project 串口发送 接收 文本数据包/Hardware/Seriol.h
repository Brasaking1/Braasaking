#ifndef _SERIAL_H
#define _SERIAL_H
#include <stdio.h>
extern char Serial_RXPacket[];
void SERIAL_SendByte(uint8_t Byte);
void SERIAL_Init(void);
void Serial_sendArray(uint8_t *Array,uint16_t Length);
void Serial_SendString(char*String);
uint32_t Serial_POW(uint32_t X,uint32_t Y);
void Serial_SendNumber(uint32_t Number,uint8_t Length);
void Serial_Printf(char*format,...);

uint8_t Serial_GetRxFlag(void);



#endif
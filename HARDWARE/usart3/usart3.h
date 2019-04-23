#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x_usart.h"
#include "stm32f10x.h"

#define USART3_TIMEOUT_Setting 800  //(ms)
extern u8 USART3_RX_BUF[250]; 
extern u16 USART3_RX_CNT;
extern u16 USART3_RX_TIMEOUT;
void USART3_Init(u32 baud);
void USART3_Sned_Char(u8 temp);
void USART3_Sned_Char_Buff(u8 buf[],u32 len);
void Timer1CountInitial(void);
void usart3_niming_report(u8*data);
#endif

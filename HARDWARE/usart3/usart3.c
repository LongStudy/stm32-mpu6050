
#include "usart3.h"	


u8 USART3_RX_BUF[250]; 
u16 USART3_RX_CNT=0;
u16 USART3_RX_TIMEOUT=0;


void USART3_Init(u32 baud)   
{  
    USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    USART_InitStructure.USART_BaudRate = baud;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  


    // Configure USART3   
    USART_Init(USART3, &USART_InitStructure);
    // Enable USART3 Receive interrupts
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  
    // Enable the USART3   
    USART_Cmd(USART3, ENABLE);

    //Configure the NVIC Preemption Priority Bits     
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  

    // Enable the USART3 Interrupt   
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;    
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);       
      
} 

void USART3_Sned_Char(u8 temp)        
{  
    USART_SendData(USART3,(u8)temp);      
    while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);  
      
}

void USART3_Sned_Char_Buff(u8 buf[],u32 len)  
{  
    u16 i;  
    for(i=0;i<len;i++)  
    USART3_Sned_Char(buf[i]);  
}

void usart3_niming_report(u8*data)
{
	u8 send_buf[8];
	u8 i;
	send_buf[0]=0XAA;	//帧头
	send_buf[1]=data[0];			//复制数据
	send_buf[2]=data[1];
	send_buf[3]=data[2];
	send_buf[4]=data[3];
	send_buf[5]=data[4];
	send_buf[6]=data[5];
	send_buf[7]=0XFF;	//帧尾
	for(i=0;i<8;i++)
	USART3_Sned_Char(send_buf[i]);
}


void USART3_IRQHandler(void)                 
{
    u8 Res;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  
    {    
        USART3_RX_TIMEOUT=0;
        USART3_RX_BUF[USART3_RX_CNT++] = USART_ReceiveData(USART3);      
    }
    if(USART_GetFlagStatus(USART3,USART_FLAG_ORE) == SET)
    {
        USART_ReceiveData(USART3);
        USART_ClearFlag(USART3,USART_FLAG_ORE);
    }
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);

}


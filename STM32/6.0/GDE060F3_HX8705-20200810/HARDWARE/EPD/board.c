#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "board.h"
#include "data.h"

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

void Delay1ms(unsigned long ms)
{	
	for(;ms;ms--)
	{
		Delay(5900);	//1ms
	}
}

void Delay100ms(unsigned long cnt)
{
  for(; cnt != 0; cnt--)
  	Delay(0x92400);
}


void IO_Init(void)
{
	SYS_WAKEUP_L;
	LED_01_OFF;
	LED_02_OFF;

	FLASH_CS_H;

	AVT_RST_L;
	AVT_HDC_L;
	AVT_HWE_H;
	AVT_HRD_H;
	AVT_HCS_H;
	AVT_DAT_SETIN;

	TPS_WAKEUP_L;
	TPS_PWRCOM_L;
	TPS_PWRUP_L;
	TPS_SCL_H;
	TPS_SDA_H;

}

void SYS_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    SystemInit();
		
	RCC_APB2PeriphClockCmd(RCC_GPIO_USE, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = PORT_A_OUT_PP; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_EPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = PORT_B_OUT_PP; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_EPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PORT_B_OUT_OD; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_EPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = PORT_C_OUT_PP; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_EPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PORT_D_OUT_PP; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_EPD;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PORT_D_IN_NOPULL; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_EPD;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	IO_Init();

	
}


#ifdef DEBUG_USART
void GPIO_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;


	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK, ENABLE);		
	RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE); 			

	GPIO_InitStructure.GPIO_Pin = USART1_RxPin;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = USART1_TxPin;				
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;               						
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;					
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     						
	USART_InitStructure.USART_Parity = USART_Parity_No;        					
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	//USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  			
	USART_InitStructure.USART_Mode =  USART_Mode_Tx;  								


	USART_Init(USART1, &USART_InitStructure);				

#if 0
	NVIC_InitTypeDef NVIC_InitStructure;


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);			
	  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			
#endif  
  	
  	
  	USART_Cmd(USART1, ENABLE);								
}

void usart_sendbyte(unsigned char s)
{
  	USART_SendData(USART1, s);
  	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void Debug_str(char *s)
{
	while (*s)					
	{
		usart_sendbyte(*s++);	
	}
}

void Debug_hex(unsigned int dat)
{
	char buf[8];
	unsigned char i;
	
	buf[0]='0';
	buf[1]='x';
	i=(dat>>12)&0x0f;
	if (i>9)
		buf[2]='A'-10+i;
	else
		buf[2]='0'+i;

	i=(dat>>8)&0x0f;
	if (i>9)
		buf[3]='A'-10+i;
	else
		buf[3]='0'+i;

	i=(dat>>4)&0x0f;
	if (i>9)
		buf[4]='A'-10+i;
	else
		buf[4]='0'+i;

	i=dat&0x0f;
	if (i>9)
		buf[5]='A'-10+i;
	else
		buf[5]='0'+i;

	buf[6]=' ';
	buf[7]=0;

	Debug_str(buf);
}

void Debug_dec(unsigned int dat)
{
	char buf[7];
	
	buf[0]='0'+dat/10000;
	buf[1]='0'+(dat% 10000) / 1000;
	buf[2]='0'+(dat% 1000) / 100;
	buf[3]='0'+(dat% 100) / 10;
	buf[4]='0'+(dat% 10) ;
	buf[5]=' ';
	buf[6]=0;
	Debug_str(buf);
}
#endif

void SPIx_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable SPI1 and GPIOA clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* Configure SPI1 pins: SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* SPI1 configuration */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	                 
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	 		             
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;		               
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			             
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				  
	SPI_InitStructure.SPI_CRCPolynomial = 7;						  
	SPI_Init(SPI1, &SPI_InitStructure);
	
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE); 											 

	
}






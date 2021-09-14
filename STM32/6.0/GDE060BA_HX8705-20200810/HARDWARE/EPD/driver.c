#include "stm32f10x.h"
#include "board.h"
#include "data.h"
#include "driver.h"
#include "epd.h"

u8 SpiFlash_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while((SPI1->SR&1<<1)==0)//Wait for the send area to be empty
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI1->DR=TxData;	 	  //Send a byte
	retry=0;
	while((SPI1->SR&1<<0)==0) //Waiting to receive a byte
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI1->DR;          //Return received data	    
}

//Read chip ID W25X16  ID:0XEF14
u16 SpiFlash_ReadID(void)
{
	u16 Temp = 0;	
	
	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x90);//Send Read ID command  
	SpiFlash_ReadWriteByte(0x00); 	    
	SpiFlash_ReadWriteByte(0x00); 	    
	SpiFlash_ReadWriteByte(0x00); 	 			   
	Temp |= SpiFlash_ReadWriteByte(0xFF)<<8;  
	Temp |= SpiFlash_ReadWriteByte(0xFF);	 
	FLASH_CS_H;	
	
	return Temp;
} 

void SpiFlash_StatusWait(void)
{
	u8 ret = 0;	

	while(1)
	{
		FLASH_CS_L;				    
		SpiFlash_ReadWriteByte(0x05);//Send Read ID command
		ret = SpiFlash_ReadWriteByte(0xFF);
		FLASH_CS_H;	
		if((ret & 0x1)==0)
			break;


		Debug_str("w");
	}
} 

void SpiFlash_EraseBlock32K(u32 addr)
{
	u8 addr3,addr2,addr1;

	
	addr1 = addr;
	addr2 = (addr>>8);
	addr3 = (addr>>16);
	
	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x06);//write enable
	FLASH_CS_H;	
	
	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x52);    
	SpiFlash_ReadWriteByte(addr3); 	    
	SpiFlash_ReadWriteByte(addr2); 	    
	SpiFlash_ReadWriteByte(addr1); 	 
	FLASH_CS_H;	

	SpiFlash_StatusWait();

	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x04);//write disable
	FLASH_CS_H;	
}

void SpiFlash_PageProgram(u32 addr, u8 *data)
{
	u8 addr3,addr2,addr1;
	u16 i;

	
	addr1 = addr;
	addr2 = (addr>>8);
	addr3 = (addr>>16);

	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x06);//write enable
	FLASH_CS_H;	
	
	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x02);	    
	SpiFlash_ReadWriteByte(addr3); 	    
	SpiFlash_ReadWriteByte(addr2); 	    
	SpiFlash_ReadWriteByte(addr1); 	

	for(i=0; i<256; i++)
	{
		SpiFlash_ReadWriteByte(data[i]);
	}
	FLASH_CS_H;	

	SpiFlash_StatusWait();

	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x04);//write disable
	FLASH_CS_H;	
}


void SpiFlash_ReadData(u32 addr, u8 *data)
{
	u8 addr3,addr2,addr1;
	
	
	addr1 = addr;
	addr2 = (addr>>8);
	addr3 = (addr>>16);

	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x03);	    
	SpiFlash_ReadWriteByte(addr3); 	    
	SpiFlash_ReadWriteByte(addr2); 	    
	SpiFlash_ReadWriteByte(addr1); 	

	FLASH_CS_H;	
}


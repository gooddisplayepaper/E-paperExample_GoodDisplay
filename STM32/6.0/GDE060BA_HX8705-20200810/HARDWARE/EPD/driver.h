#ifndef __DRIVER_H
#define __DRIVER_H

#include "stm32f10x.h"


//512k bytes of a picture
#define PICA_FLASH_ADDR		0
#define PICB_FLASH_ADDR		240000

#define SPIFLASH_PAGESIZE	512


u8 SpiFlash_ReadWriteByte(u8 TxData);
void SpiFlash_EraseBlock32K(u32 addr);
void SpiFlash_PageProgram(u32 addr, u8 *data);

u16 SpiFlash_ReadID(void);
#endif /* __DRIVER_H */

#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   800
#define EPD_HEIGHT  480

//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void PIC_display (const unsigned char* picData);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clear(void);
//Display canvas function
void EPD_Display(unsigned char *Image); 

#endif
/***********************************************************
						end file
***********************************************************/



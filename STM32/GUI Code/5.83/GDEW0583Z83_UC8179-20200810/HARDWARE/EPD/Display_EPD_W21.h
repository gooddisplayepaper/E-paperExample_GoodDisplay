#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   648
#define EPD_HEIGHT  480

//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void PIC_display(const unsigned char* picData_old,const unsigned char* picData_new);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clear(void);
//Display canvas function
void EPD_Display_BW(unsigned char *BW_Image);
void EPD_Display_R(unsigned char *R_Image);

#endif
/***********************************************************
						end file
***********************************************************/



#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   128
#define EPD_HEIGHT  296

//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void PIC_display(const unsigned char* picData_old,const unsigned char* picData_new);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clear(void);
//Display canvas function
void EPD_Display(unsigned char *BW_Image,unsigned char *R_Image);

#endif
/***********************************************************
						end file
***********************************************************/



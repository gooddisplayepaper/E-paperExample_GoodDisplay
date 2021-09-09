#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   104
#define EPD_HEIGHT  212

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
//LUT
void EPD_init_LUT(void);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode); //mode 0: first  1: other...
void EPD_init_4GRAY(void);
void PIC_display_4GRAY(const unsigned char *DATA_4GRAY);
#endif
/***********************************************************
						end file
***********************************************************/



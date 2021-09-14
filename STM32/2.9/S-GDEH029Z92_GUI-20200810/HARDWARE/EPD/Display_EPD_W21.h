#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   128
#define EPD_HEIGHT  296

#define ALLSCREEN_GRAGHBYTES  4736
//EPD
void EPD_W21_Init(void);
void EPD_init_GUI(void);
void EPD_init(void);
void PIC_display(const unsigned char *BW_datas,const unsigned char *R_datas);
void EPD_sleep(void);
void Epaper_READBUSY(void);
void PIC_display_Clear(void);
//Display canvas function
void EPD_Display(unsigned char *BW_Image,unsigned char *R_Image);

#endif
/***********************************************************
						end file
***********************************************************/



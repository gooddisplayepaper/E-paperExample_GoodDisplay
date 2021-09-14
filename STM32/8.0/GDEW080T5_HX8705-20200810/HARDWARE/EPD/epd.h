#ifndef __EPD_H
#define __EPD_H

#include "stm32f10x.h"

//#define GDE043A2         //4.3 inch needs to enable this macro definition, otherwise the display image mirror is inverted
//#define GDE060F3   //6.0 INCH 1024*758     

#define EPD_WF_ADDR				(0x3000)		//The e-paper module drives the waveform file at the beginning of the FLASH
#define EPD_IMG_ADDR			(0x200000)		//Transfer picture data to RAM start address

#define EPD_MODE_INIT			0
#define EPD_MODE_DU				1
#define EPD_MODE_GC16			2

// Load Image Data Formats (ld_img, dfmt)
#define EPD_DATA_2BPP         	(0<<4)       	// 1 pixel occupies 2 bits, one byte represents 4 pixels
#define EPD_DATA_4BPP           (2<<4)       	// 1 pixel occupies 4 bits, one byte represents 2 pixels
#define EPD_DATA_8BPP           (3<<4)       	//1 pixel occupies 8 bits, one byte represents 1 pixels

#if 0	//800x600 85Hz
#define  tcon_init_hsize        800                 
#define  tcon_init_vsize        600             
#define  tcon_init_fslen        4                          
#define  tcon_init_fblen        4                          
#define  tcon_init_felen        10                         
#define  tcon_init_lslen        10                         
#define  tcon_init_lblen        4                          
#define  tcon_init_lelen        13                 
#define  tcon_init_pixclkdiv    3
#define  tcon_init_sdrv_cfg     (100 | (1 << 8) | (1 << 9))
#ifdef  GDE043A2   // GDE060BA/GDE043A2
	#define  tcon_init_gdrv_cfg     0x00
#else	            //GDE060BA
	#define  tcon_init_gdrv_cfg     0x02	
#endif
#define  tcon_init_lutidxfmt    (4 | (1 << 7))
#endif

#if 0	//800x600 50Hz
#define  tcon_init_hsize        800                        
#define  tcon_init_vsize        600                        
#define  tcon_init_fslen        4                          
#define  tcon_init_fblen        4                          
#define  tcon_init_felen        10                         
#define  tcon_init_lslen        10                         
#define  tcon_init_lblen        4                          
#define  tcon_init_lelen        44                 
#define  tcon_init_pixclkdiv    5                          
#define  tcon_init_sdrv_cfg     (100 | (1 << 8) | (1 << 9))
#define  tcon_init_gdrv_cfg     0x02                  
#define  tcon_init_lutidxfmt    (4 | (1 << 7))
#endif
#if 1	//1024x758 85Hz
#define  tcon_init_hsize        1024
#ifdef GDE060F3  //6´ç1024*758
#define  tcon_init_vsize        758 
#else           //8´ç1024*768
#define  tcon_init_vsize        768 
#endif
#define  tcon_init_fslen        13                          
#define  tcon_init_fblen        4                         
#define  tcon_init_felen        10                         
#define  tcon_init_lslen        10                         
#define  tcon_init_lblen        4                          
#define  tcon_init_lelen        42                 
#define  tcon_init_pixclkdiv    2                         
#define  tcon_init_sdrv_cfg     (128 | (1 << 8) | (1 << 9))
#define  tcon_init_gdrv_cfg     0x00                  
#define  tcon_init_lutidxfmt    (4 | (1 << 7))

#endif

void avt_spi_flash_init(void);
void AVT_CONFIG_check(void);
void avt_waveform_update(void);
void avt_init(void);
//u16 avt_rd_reg(u16 regaddr);
//u16 avt_wr_reg(u16 regaddr, u16 regdata);

void avt_run_sys(void);
void avt_stby(void);
void avt_slp(void);

void avt_spi_flash_write_waveform_start(void);
void avt_spi_flash_write_waveform_end(void);
void avt_spi_flash_sector_earase(u32 addr);
void avt_spi_flash_write_page(u32 addr, u8 *data);

void epd_draw_pic_start(void);
void epd_draw_pic_buff(u8* buff, u16 len);
void epd_draw_pic_end(void);
void epd_draw_pic_from_spiflash(u32 addr);

void epd_draw_gray(u8 gray);
void epd_draw_gray_level_horizontal(u8 div);
void epd_draw_gray_level_vertical(u8 div);
void epd_draw_gray_part(u8 gray, u16 x, u16 y, u16 w, u16 h);
void epd_draw_gray_part_lut(u8 gray, u16 x, u16 y, u16 w, u16 h);
void epd_draw_pic_part_from_rom(u8* ptr, u8 bpp, u16 x, u16 y, u16 w, u16 h);

void avt_lut_demo(u8 gray);

#endif /* __EPD_H */

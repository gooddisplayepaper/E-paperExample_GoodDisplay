#include "stm32f10x.h"
#include "delay.h"
//EPD
#include "board.h"
#include "driver.h"
#include "data.h"
#include "epd.h"
#include "power.h"
#include "picture.h"

u8 wf_mode = EPD_MODE_INIT;				//EPD refresh mode
int main(void)
{	
			u32 i;
			
			for(i=0;i<10000;i++);
			SYS_Init();			//system initialization
			IO_Init();			//IO port initialization
			delay_init();   //delay init
			GPIO_USART_Init();	 //Serial port initialization
			SPIx_Init();				//SPI initialization
			SYS_WAKEUP_H;
			delay_ms(20);
			
			tps_init(); //TPS65185 initialization
			tps_sleep_to_standby(); //VCOM voltage setting
			AVT_CONFIG_check();			//Check whether the configuration command of the AVT is normal.
	
	  	delay_ms(20);
	    avt_waveform_update();//Load waveform file
	
			avt_init();//Double flash
			epd_draw_gray(0xff);//Full gray
			delay_ms(20);



		#if 1    //16-level grayscale demo
			delay_ms(20);

			wf_mode = EPD_MODE_GC16;
			epd_draw_gray_level_horizontal(16);
			delay_ms(20);

			epd_draw_gray_level_vertical(16);
			delay_ms(20);

			epd_draw_gray_level_horizontal(8);
			delay_ms(20);

			epd_draw_gray_level_vertical(8);
			delay_ms(20);

			epd_draw_gray(0xff);
		#endif	
			

		while(1)
			{	
						////////////////Bureau brush refresh display/////////////////
			//4 gray
			wf_mode = EPD_MODE_GC16;
			epd_draw_pic_part_from_rom((u8*)gImage_01, EPD_DATA_2BPP, 0, 0, 800, 133); //Picture 1.1, resolution 800*133		
  		epd_draw_pic_part_from_rom((u8*)gImage_02, EPD_DATA_2BPP, 0, 133, 800, 105);//Picture 1.2, resolution 800*105
			epd_draw_pic_part_from_rom((u8*)gImage_03, EPD_DATA_2BPP, 0, 238, 800, 175);//Picture 1.3, resolution 800*175
			epd_draw_pic_part_from_rom((u8*)gImage_04, EPD_DATA_2BPP, 0, 413, 800, 187);//Picture 1.4, resolution 800*187

			//Refresh screen             
			wf_mode = EPD_MODE_GC16;
			epd_draw_gray(0xff);  //Full gray
			epd_draw_gray(0xff); //Full gray
	          ////////////////Display pictures in full screen/////////////////
			//4 gray
			epd_draw_pic_part_from_rom((u8*)gImage_1, EPD_DATA_2BPP, 0, 0, 800, 600);//Picture 1£¬resolution 800*600
			delay_s(3);//ÑÓÊ±3s
			//Refresh screen     
      wf_mode = EPD_MODE_GC16;				
			epd_draw_gray(0xff); //Full gray
			epd_draw_gray(0xff); //Full gray
			
			//16 gray
			epd_draw_pic_part_from_rom((u8*)gImage_11, EPD_DATA_4BPP, 0, 0, 800, 600);//Picture 2£¬resolution 800*600
			delay_s(3);
			//Refresh screen     
      wf_mode = EPD_MODE_GC16;			
			epd_draw_gray(0xff);  //Full gray
			epd_draw_gray(0xff);  //Full gray

			while(1);
	   }




}






























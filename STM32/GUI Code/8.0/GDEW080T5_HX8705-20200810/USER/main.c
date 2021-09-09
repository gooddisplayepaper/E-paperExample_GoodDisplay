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
			epd_draw_gray(0xff);//Clean screen
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
			wf_mode = EPD_MODE_DU;	
      //4 gray				
			//5~1 Bureau brush display
			epd_draw_pic_part_from_rom((u8*)gImage_num5, EPD_DATA_2BPP, 500 , 300, 48, 104); //Picture1,resolution 48*104
			epd_draw_pic_part_from_rom((u8*)gImage_num4, EPD_DATA_2BPP, 500 , 300, 48, 104); //Picture2,resolution 48*104
			epd_draw_pic_part_from_rom((u8*)gImage_num3, EPD_DATA_2BPP, 500 , 300, 48, 104); //Picture3,resolution 48*104
			epd_draw_pic_part_from_rom((u8*)gImage_num2, EPD_DATA_2BPP, 500 , 300, 48, 104); //Picture4,resolution 48*104
			epd_draw_pic_part_from_rom((u8*)gImage_num1, EPD_DATA_2BPP, 500 , 300, 48, 104); //Picture5,resolution 48*104

			//Clear                
			wf_mode = EPD_MODE_GC16;
			epd_draw_gray(0xff);  //Clean screen
			delay_s(1);	//1s	
	    //4 gray   
      epd_draw_pic_part_from_rom((u8*)gImage_1, EPD_DATA_2BPP, 0 , 0, 1024, 768); //Full screen display, resolution 1024*758
      delay_s(3);	//3s
			//Clear                
			wf_mode = EPD_MODE_GC16;
			epd_draw_gray(0xff);  //Clean screen
			delay_s(2);	//2s		
				
			//If select "EPD_DATA_4BPP",mode is 16 gray.	
			while(1);		
				
	   }




}






























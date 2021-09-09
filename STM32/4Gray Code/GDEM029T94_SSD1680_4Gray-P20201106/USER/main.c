#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	

//Tips//
/*
1. When refreshing the electronic paper in full screen, the picture flickers is a normal phenomenon, the main function is to clear the residual image displayed in the previous picture.
2. When performing partial refresh, the screen will not flicker. It is recommended to use full-screen refresh to clear the screen after 5 partial refreshes to reduce screen image retention.
3. After the e-paper is refreshed, it needs to enter the sleep mode, please do not delete the sleep command.
4. Do not remove the e-paper when turning on.
5. Wake up from sleep, need to re-initialize the electronic paper.
6. When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is in input mode, and the other pins are in output mode.
*/
int	main(void)
{
	unsigned char fen_L,fen_H,miao_L,miao_H;
		delay_init();	    	     //Delay function initialization
		NVIC_Configuration(); 	//Set NVIC interrupt grouping 2
    EPD_GPIO_Init();       //EPD GPIO  initialization
	while(1)
	{
				
  ///////////////////////////Normal picture display/////////////////////////////////////////////////////////////////
		/************Normal picture display*******************/
    EPD_HW_Init(); //EPD init
	  EPD_WhiteScreen_ALL(gImage_1);//EPD_picture1
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(2); //2s	
	
		EPD_HW_Init_4GRAY(); //EPD init 4gray
	 	EPD_WhiteScreen_ALL_4GRAY(gImage_11); 
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay_s(2); //2s	

		
		//Clear
		EPD_HW_Init(); //EPD init
	  EPD_WhiteScreen_White();//EPD Clear
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(2); //2s	
		
/*It is recommended to use full-screen refresh to clear the screen after 5 partial refreshes to reduce screen image retention.		*/
//////////////////////Partial refresh time demo/////////////////////////////////////
    EPD_HW_Init(); //Electronic paper initialization	
	  EPD_SetRAMValue_BaseMap(gImage_basemap); //Partial refresh background color  		
		for(fen_H=0;fen_H<6;fen_H++)
		{
		for(fen_L=0;fen_L<10;fen_L++)
		{
		for(miao_H=0;miao_H<6;miao_H++) 	
		{
		for(miao_L=0;miao_L<10;miao_L++)
		{
				EPD_Dis_Part_myself(32,92,(unsigned char *)&Num[miao_L],         //x-A,y-A,DATA-A
														32,124,(unsigned char *)&Num[miao_H],         //x-B,y-B,DATA-B
														32,164,(unsigned char *)gImage_numdot,       //x-C,y-C,DATA-C
														32,206,(unsigned char *)&Num[fen_L],         //x-D,y-D,DATA-D
														32,238,(unsigned char *)&Num[fen_H],32,64);	 //x-E,y-E,DATA-E,Resolution 32*64
														
														if((fen_L==0)&&(miao_H==0)&&(miao_L==5))
														goto Clear;
			}
		}
		}
		
		}
		
////////////////////////////////////////////////////////////////////////	
			//Clear screen
		Clear:
		EPD_HW_Init(); //Electronic paper initialization
		EPD_WhiteScreen_White(); //Show all white
		EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
	  delay_s(2); //2s		
	while(1);	
	}	

}	



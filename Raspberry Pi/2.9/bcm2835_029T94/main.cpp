#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "epd1in54.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED      0
#define UNCOLORED    1

int main(void)
{
    Epd epd;

	  //Full screen refresh
		epd.EPD_HW_Init(); //Electronic paper initialization
	 	epd.EPD_WhiteScreen_ALL(gImage_1); //Refresh the picture in full screen
               //epd.DelayMs(500);
//////////////////////Partial refresh digital presentation//////////////////////////////////////
      epd.EPD_HW_Init(); //Electronic paper initialization	
	  epd.EPD_SetRAMValue_BaseMap(gImage_basemap);  //Partial refresh background color 
	  epd.EPD_Dis_Part(0,32,gImage_num1,32,32); //x,y,DATA,Resolution 32*32
	  epd.EPD_Dis_Part(0,32,gImage_num2,32,32); //x,y,DATA,Resolution 32*32
	  epd.EPD_Dis_Part(0,32,gImage_num3,32,32); //x,y,DATA,Resolution 32*32
           //epd.DelayMs(500);     
                 //all white
		epd.EPD_HW_Init(); //Electronic paper initialization
	 	epd.EPD_WhiteScreen_ALL(gImage_white); //Refresh the picture in full screen

while(1);
}


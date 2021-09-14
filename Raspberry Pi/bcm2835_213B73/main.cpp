#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "epd1in54.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED      0
#define UNCOLORED    1

//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */

int main(void)
{
    time_t now;
    struct tm* timenow;
    Epd epd;
    if (epd.Init(lut_full_update) != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }
	  //Full screen refresh
		epd.EPD_HW_Init(); //Electronic paper initialization
	 	epd.EPD_WhiteScreen_ALL(gImage_1); //Refresh the picture in full screen
               //epd.DelayMs(500);
//////////////////////Partial refresh digital presentation//////////////////////////////////////
          epd.EPD_HW_Init(); //Electronic paper initialization	
	  epd.EPD_SetRAMValue_BaseMap(gImage_logo);  //Partial refresh background color 
	  epd.EPD_Dis_Part(0,32,gImage_num1,32,32); //x,y,DATA,Resolution 32*32
	  epd.EPD_Dis_Part(0,32,gImage_num2,32,32); //x,y,DATA,Resolution 32*32
	  epd.EPD_Dis_Part(0,32,gImage_num3,32,32); //x,y,DATA,Resolution 32*32
           //epd.DelayMs(500);     
                 //all white
		epd.EPD_HW_Init(); //Electronic paper initialization
	 	epd.EPD_WhiteScreen_ALL(gImage_white); //Refresh the picture in full screen
          epd.Sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!

while(1);
}


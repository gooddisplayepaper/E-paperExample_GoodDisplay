#include <stdlib.h>
#include <stdio.h>
#include "epd7in5.h"
#include "epdpaint.h"
#include "imagedata.h" 

#define COLORED      1
#define UNCOLORED    0


//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */

int main(void)
{
    Epd epd;
    if (epd.Init() != 0) //EPD init
      {
        printf("e-Paper init failed\n");
        return -1;
      }

    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);//set wide and height
    paint.Clear(UNCOLORED); //clear screen



   epd.DisplayFrame(gImage_3); //image3 
   epd.Sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
   while(1);
    
}


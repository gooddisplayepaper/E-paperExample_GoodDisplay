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


    
    //GUI demo////////////
    unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
    unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);

    Paint paint_black(frame_black, epd.width, epd.height);
    Paint paint_red(frame_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.DrawRectangle(20, 80, 180, 280, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_black.DrawLine(20, 80, 180, 280, COLORED);//x1,y1,x2,y2
    paint_black.DrawLine(180, 80, 20, 280, COLORED);//x1,y1,x2,y2
    paint_red.DrawFilledRectangle(200, 80, 360, 280, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawCircle(300, 160, 60, UNCOLORED);//x,y,r
    paint_red.DrawFilledCircle(90, 500, 30, COLORED);//x,y,r

    /* Write strings to the buffer */
    paint_red.DrawFilledRectangle(0, 0, 400, 30, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawStringAt(70, 4, "--Good display--", &Font24, UNCOLORED);//x,y
    paint_black.DrawStringAt(100, 40, "e-Paper Demo", &Font24, COLORED);//x,y
   
    /* Display the frame_buffer */
    epd.DisplayFrame(frame_black, frame_red);
    bcm2835_delay(8000); 




//Picture demo////////////
epd.pic_display_white();//white;
epd.pic_display1();//image1;
epd.EPD_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!

	  while(1);
    
}


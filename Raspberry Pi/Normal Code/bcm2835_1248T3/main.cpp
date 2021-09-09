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
    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED);
    paint.SetRotate(ROTATE_0);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint.DrawRectangle(16, 40, 56, 90, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawLine(16, 40, 56, 90, COLORED);//x1,y1,x2,y2
    paint.DrawLine(56, 40, 16, 90, COLORED);//x1,y1,x2,y2
    paint.DrawCircle(400,400, 150, COLORED);//x,y,r
    paint.DrawFilledRectangle(16, 100, 56, 150, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawFilledCircle(600, 600, 150, COLORED);//x,y,r

    /*Write strings to the buffer */
    paint.DrawFilledRectangle(0, 0, 152, 15, COLORED);//x1,y1,x2,y2 Diagonal point
    paint.DrawStringAt(20, 04, "--Good display--", &Font12, UNCOLORED);//x,y
    paint.DrawStringAt(35, 18, "e-Paper Demo", &Font12, COLORED);//x,y

    /* Display the frame_buffer */
    epd.DisplayFrame(frame_buffer);
    bcm2835_delay(2000);  





//Picture demo////////////
epd.pic_display_white();//white;
epd.pic_display1();//image1;
epd.EPD_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
	  while(1);
    
}


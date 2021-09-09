

#include <stdlib.h>
#include <stdio.h>
#include "epd4in2b.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <bcm2835.h>

#define COLORED      1
#define UNCOLORED    0

//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */


int main(void)
{
    Epd epd;
    if (epd.Init() != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }

    unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
    unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);

    Paint paint_black(frame_black, epd.width, epd.height);
    Paint paint_red(frame_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);
    paint_black.SetRotate(ROTATE_270);
    paint_red.SetRotate(ROTATE_270);

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.DrawRectangle(16, 40, 56, 90, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_black.DrawLine(16, 40, 56, 90, COLORED);//x1,y1,x2,y2
    paint_black.DrawLine(56, 40, 16, 90, COLORED);//x1,y1,x2,y2
    paint_red.DrawFilledRectangle(16, 100, 56, 150, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawCircle(120, 60, 25, COLORED);//x,y,r
    paint_red.DrawFilledCircle(120, 125, 25, COLORED);//x,y,r

    /* Write strings to the buffer */
    paint_red.DrawFilledRectangle(0, 0, 152, 15, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawStringAt(20, 04, "--Good display--", &Font12, UNCOLORED);//x,y
    paint_black.DrawStringAt(35, 18, "e-Paper Demo", &Font12, COLORED);//x,y
   
    /* Display the frame_buffer */
    epd.DisplayFrame(frame_black, frame_red);
    bcm2835_delay(8000); 

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

    epd.Sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);
    return 0;
}


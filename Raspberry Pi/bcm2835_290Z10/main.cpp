

#include <stdlib.h>
#include <stdio.h>
#include "epd2in9b.h"
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

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.SetRotate(ROTATE_270);
    paint_red.SetRotate(ROTATE_270);
    paint_black.DrawRectangle(10, 60, 50, 110, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_black.DrawLine(10, 60, 50, 110, COLORED);//x1,y1,x2,y2
    paint_black.DrawLine(50, 60, 10, 110, COLORED);//x1,y1,x2,y2
    paint_black.DrawCircle(90, 85, 25, COLORED);//x,y,r
    paint_red.DrawFilledRectangle(220, 60, 260, 110, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawFilledRectangle(90, 0, 220, 18, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawFilledCircle(180, 85, 25, COLORED);//x,y,r

    /*Write strings to the buffer */
    paint_black.DrawStringAt(115, 24, "e-Paper Demo", &Font12, COLORED);//x,y
    paint_red.DrawStringAt(100, 4, "--Good display--", &Font12, UNCOLORED);//x,y
   
    /* Display the frame_buffer */
    epd.DisplayFrame(frame_black, frame_red);
    bcm2835_delay(8000);

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

    epd.Sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);
    return 0;
}


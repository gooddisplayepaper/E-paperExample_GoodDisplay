

#include <stdio.h>
#include <stdlib.h>
#include "epd2in7b.h"
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
    unsigned char* frame_buffer_black = (unsigned char*)malloc(epd.width / 8 * epd.height);
    unsigned char* frame_buffer_red = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint_black(frame_buffer_black, epd.width, epd.height);
    Paint paint_red(frame_buffer_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.SetRotate(ROTATE_270);
    paint_red.SetRotate(ROTATE_270);
    paint_black.DrawRectangle(10, 80, 50, 130, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_black.DrawLine(10, 80, 50, 130, COLORED);//x1,y1,x2,y2
    paint_black.DrawLine(50, 80, 10, 130, COLORED);//x1,y1,x2,y2
    paint_black.DrawCircle(90, 105, 25, COLORED);//x,y,r
    paint_red.DrawFilledRectangle(150, 80, 190, 130, COLORED);//x1,y1,x2,y2,Diagonal point
    paint_red.DrawFilledCircle(230, 105, 25, COLORED);//x,y,r
    paint_red.DrawFilledRectangle(40, 0, 230, 30, COLORED); //x1,y1,x2,y2,Diagonal point
    paint_red.DrawStringAt(50, 8, "--Good display--", &Font16, UNCOLORED);//x,y
    paint_black.DrawStringAt(55, 30, "e-Paper Demo", &Font20, COLORED);//x,y

    /* Display the frame_buffer */
    epd.DisplayFrame(frame_buffer_black, frame_buffer_red);
    bcm2835_delay(8000); 

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
    epd.Sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);
    return 0;
}




#include <stdlib.h>
#include <stdio.h>
#include "epd7in5b.h"
#include "epd7in5bpaint.h"
#include "imagedata.h"
#include <bcm2835.h>


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


    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 2 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(EPDPAINT_WHITE);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint.SetRotate(ROTATE_0);
    paint.DrawRectangle(20, 80, 180, 280, EPDPAINT_RED);//x1,y1,x2,y2,Diagonal point
    paint.DrawLine(20, 80, 180, 280, EPDPAINT_RED);//x1,y1,x2,y2
    paint.DrawLine(180, 80, 20, 280, EPDPAINT_RED);//x1,y1,x2,y2
    paint.DrawFilledRectangle(200, 80, 360, 280, EPDPAINT_BLACK);//x1,y1,x2,y2,Diagonal point
    paint.DrawCircle(520, 320, 30, EPDPAINT_RED);//x,y,r
    paint.DrawCircle(550, 320, 30, EPDPAINT_RED);//x,y,r
    paint.DrawFilledCircle(500, 180, 60, EPDPAINT_WHITE);//x,y,r
    paint.DrawFilledCircle(500, 160, 60, EPDPAINT_RED);//x,y,r
    paint.DrawFilledCircle(500, 200, 60, EPDPAINT_BLACK);//x,y,r

    /* Write strings to the buffer */
    paint.DrawFilledRectangle(0, 6, 600, 30, EPDPAINT_RED);//x1,y1,x2,y2,Diagonal point
    paint.DrawStringAt(100, 10, "--Good display--", &Font24, EPDPAINT_WHITE);//x,y
    paint.DrawStringAt(130, 40, "e-Paper Demo", &Font24, EPDPAINT_BLACK);//x,y

    /* Display the frame buffer */
    epd.DisplayFrame1(frame_buffer);
    bcm2835_delay(8000); 

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_DATA);
    epd.Sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
   
    while(1);
    return 0;
}


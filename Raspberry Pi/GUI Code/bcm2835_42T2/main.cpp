

#include <stdio.h>
#include <stdlib.h>
#include "epd4in2.h"
#include "epdpaint.h"
#include "imagedata.h"
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

    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint.DrawRectangle(20, 80, 180, 280, COLORED);//x1,y1,x2,y2 Diagonal point
    paint.DrawLine(20, 80, 180, 280, COLORED);//x1,y1,x2,y2 
    paint.DrawLine(180, 80, 20, 280, COLORED);//x1,y1,x2,y2 
    paint.DrawFilledRectangle(200, 80, 360, 280, COLORED);//x1,y1,x2,y2 Diagonal point
    paint.DrawCircle(300, 160, 60, UNCOLORED);//x,y,r
    paint.DrawFilledCircle(90, 210, 30, COLORED);//x,y,r

    /*Write strings to the buffer */
    paint.DrawFilledRectangle(0, 6, 400, 30, COLORED);//x1,y1,x2,y2 Diagonal point
    paint.DrawStringAt(60, 10, "--Good display--", &Font24, UNCOLORED);//x,y
    paint.DrawStringAt(100, 40, "e-Paper Demo", &Font24, COLORED);//x,y

    /* Display the frame_buffer */
    epd.DisplayFrame(frame_buffer);
    bcm2835_delay(2000);  

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BUTTERFLY);
    epd.Sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);
    return 0;
}


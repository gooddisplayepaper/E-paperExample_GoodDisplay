

#include <stdio.h>
#include <stdlib.h>
#include "epd2in7.h"
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

    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED); 
    paint.SetRotate(ROTATE_270);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint.DrawFilledRectangle(30, 0, 210, 30, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawStringAt(35, 10, "--Good display--", &Font16, UNCOLORED);//x,y
    paint.DrawStringAt(40, 35, "e-Paper Demo", &Font20, COLORED);//x,y

    paint.DrawRectangle(10, 100, 50, 150, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawLine(10, 100, 50, 150, COLORED);//x1,y1,x2,y2
    paint.DrawLine(50, 100, 10, 150, COLORED);//x1,y1,x2,y2
    paint.DrawCircle(160, 125, 25, COLORED);//x,y,r
    paint.DrawFilledRectangle(70, 100, 110, 150, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawFilledCircle(230, 125, 25, COLORED);//x,y,r
  
    
    /* Display the frame_buffer */
    epd.DisplayFrame(paint.GetImage());
    bcm2835_delay(2000);   

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_DATA);
    epd.Sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);
    return 0;
}


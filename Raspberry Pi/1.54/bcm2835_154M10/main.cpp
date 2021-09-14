

#include <stdio.h>
#include <stdlib.h>
#include "epd4in2.h"
#include "epdpaint.h"
#include "imagedata.h"
#include <bcm2835.h>

#define COLORED      1
#define UNCOLORED    0

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
    paint.DrawRectangle(16, 40, 56, 90, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawLine(16, 40, 56, 90, COLORED);//x1,y1,x2,y2
    paint.DrawLine(56, 40, 16, 90, COLORED);//x1,y1,x2,y2
    paint.DrawCircle(120, 60, 25, COLORED);//x,y,r
    paint.DrawFilledRectangle(16, 100, 56, 150, COLORED);//x1,y1,x2,y2,Diagonal point
    paint.DrawFilledCircle(120, 125, 25, COLORED);//x,y,r

    /*Write strings to the buffer */
    paint.DrawFilledRectangle(0, 0, 152, 15, COLORED);//x1,y1,x2,y2 Diagonal point
    paint.DrawStringAt(20, 04, "--Good display--", &Font12, UNCOLORED);//x,y
    paint.DrawStringAt(35, 18, "e-Paper Demo", &Font12, COLORED);//x,y

    /* Display the frame_buffer */
    epd.DisplayFrame(frame_buffer);
    bcm2835_delay(2000);  

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BUTTERFLY);
    while(1);
    return 0;
}


#include <SPI.h>
#include "epd.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[1280];
Paint paint(image, 80, 128);

#define COLORED     0
#define UNCOLORED   1

void setup()
{

}

void loop()
{
  //GUI
  epd.Init();
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "goodisplay", &Font12, COLORED);
   //Line
   paint.DrawLine(0, 25, 25, 50,  COLORED);
   paint.DrawLine(25, 25, 0, 50,   COLORED);
//Rectangle
   paint.DrawRectangle(0, 25, 25, 50,   COLORED);
   paint.DrawRectangle(50, 25, 75, 50,  COLORED);
//Circle
   paint.DrawCircle(20, 80, 15,  COLORED);
   paint.DrawCircle(50, 80, 15,  COLORED);
   epd.Display(image); 
   epd.Sleep();//Enter to sleep
   delay(2000);     
//display picture
  epd.Init();
  epd.Display(gImage_1);  
  epd.Sleep();//Enter to sleep
  delay(2000);  
  //Clear
  epd.Init();
  epd.Clear();
  epd.Sleep();//Enter to sleep
  while(1);
}

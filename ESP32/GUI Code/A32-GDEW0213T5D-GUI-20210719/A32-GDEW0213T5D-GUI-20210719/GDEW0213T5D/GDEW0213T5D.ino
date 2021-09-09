#include <SPI.h>
#include "epd.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[2756];
Paint paint(image, 104, 212);

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
  paint.DrawStringAt(16, 0, "good-display", &Font12, COLORED);
   //Line
   paint.DrawLine(0, 20, 50, 60,  COLORED);
   paint.DrawLine(50, 20, 0, 60,   COLORED);
//Rectangle
   paint.DrawRectangle(0, 20, 50, 60,   COLORED);
   paint.DrawRectangle(60, 20, 102, 60,  COLORED);
//Circle
   paint.DrawCircle(30, 120, 25,  COLORED);
   paint.DrawCircle(70, 120, 25,  COLORED);
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

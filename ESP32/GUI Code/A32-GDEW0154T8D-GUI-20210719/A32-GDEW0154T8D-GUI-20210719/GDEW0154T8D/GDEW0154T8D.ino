#include <SPI.h>
#include "epd.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[2888];
Paint paint(image, 152, 152);

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
  paint.DrawStringAt(20, 0, "good-display", &Font12, COLORED);
   //Line
   paint.DrawLine(20-10, 20, 70-10, 60,  COLORED);
   paint.DrawLine(70-10, 20, 20-10, 60,   COLORED);
//Rectangle
   paint.DrawRectangle(20-10, 20, 70-10, 60,   COLORED);
   paint.DrawRectangle(85-10, 20, 130-10, 60,  COLORED);
//Circle
   paint.DrawCircle(50-10, 120, 30,  COLORED);
   paint.DrawCircle(100-10, 120, 30,  COLORED);
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

#include "epd.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char BlackImage[1024];//Define canvas space  
Paint paint(BlackImage, 104, 24); //

#define COLORED     0
#define UNCOLORED   1

void setup()
{

}

void loop()
{
  ////GUI//////////////////
  epd.Init();
  paint.SetWidth(104);
  paint.SetHeight(24);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Good-display!", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 10,  paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(10, 5, "E-paper!", &Font12, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 30,  paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(64);
  paint.SetHeight(64); 
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 10, 25, COLORED);
  paint.DrawLine(0, 0, 10, 25, COLORED);
  paint.DrawLine(10, 0, 0, 25, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 20, 70, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawCircle(16, 16, 15, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(0, 0, 10, 20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 20, 110, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(16, 16, 15, COLORED);
  epd.SetFrameMemory(paint.GetImage(),40, 110, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  epd.Sleep(); 
  delay(2000);

 ////GUI//////////////////
  epd.Init();
  paint.SetWidth(104);
  paint.SetHeight(24);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Good-display!", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 10,  paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(10, 5, "Thank you!", &Font12, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 30,  paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  epd.Sleep(); 
  delay(2000);
  ///////////Clear////////////////////
  epd.Init();
  epd.Clear();
  epd.Sleep(); 
 while(1);
}
             

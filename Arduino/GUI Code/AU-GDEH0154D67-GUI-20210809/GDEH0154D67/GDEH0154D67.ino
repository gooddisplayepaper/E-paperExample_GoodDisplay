#include "epd.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[1024];
Paint paint(image, 200, 24);

#define COLORED     0
#define UNCOLORED   1

void setup()
{

}

void loop()
{
  //GUI  display...
  epd.HDirInit();
  epd.Clear(); //Screen clearing is required for the first refresh. MiniGUI is a necessary operation
  epd.LDirInit();  
  paint.SetWidth(200);
  paint.SetHeight(24);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(30, 4, "Good-display!", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(10, 4, "Welcome to China!", &Font16, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(64);
  paint.SetHeight(64); 
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 40, 50, COLORED);
  paint.DrawLine(0, 0, 40, 50, COLORED);
  paint.DrawLine(40, 0, 0, 50, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 16, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawCircle(32, 32, 30, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 120, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 16, 130, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(32, 32, 30, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 120, 130, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  epd.Sleep(); 
  delay(2000);

  //GUI  display...
  epd.HDirInit();
  epd.Clear(); //Screen clearing is required for the first refresh. MiniGUI is a necessary operation
  epd.LDirInit();  
  paint.SetWidth(200);
  paint.SetHeight(24);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(30, 4, "Good-display!", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(10, 4, "Thank you!", &Font16, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  epd.Sleep(); 
  
 //Clear epd
  epd.HDirInit();
  epd.Clear();
  epd.DisplayFrame();
  epd.Sleep();
  while(1);
}

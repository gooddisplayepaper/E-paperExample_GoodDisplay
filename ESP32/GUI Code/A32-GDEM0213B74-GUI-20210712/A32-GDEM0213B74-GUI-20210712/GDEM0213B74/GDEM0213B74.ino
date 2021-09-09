#include <SPI.h>
#include "epd.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[4000];
Paint paint(image, 128, 250);

unsigned long time_start_ms;
unsigned long time_now_s;
#define COLORED     0
#define UNCOLORED   1

void setup()
{

}

void loop()
{
  //GUI
  epd.LDirInit();
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
   epd.SetFrameMemory(paint.GetImage(),0, 0, paint.GetWidth(), paint.GetHeight());
   epd.DisplayFrame();
   epd.Sleep();//Enter to sleep
   delay(2000);  

   
  //Part display
  epd.Init();   
  epd.DisplayPartBaseImage(gImage_basemap);
  epd.EPD_Dis_Part(32,160, Num[0],32,64);//display num0
  epd.EPD_Dis_Part(32,160, Num[1],32,64);//display num1
  epd.EPD_Dis_Part(32,160, Num[2],32,64);//display num2
  epd.EPD_Dis_Part(32,160, Num[3],32,64);//display num3
  epd.EPD_Dis_Part(32,160, Num[4],32,64);//display num4  
  epd.Sleep();//Enter to sleep
  delay(2000); 
  //Clear
  epd.Init();
  epd.Clear();
  while(1);
}

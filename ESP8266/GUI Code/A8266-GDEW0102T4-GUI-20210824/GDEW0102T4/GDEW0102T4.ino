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


void Sys_run(void)
{
   ESP.wdtFeed(); //Feed dog to prevent system reset
  }

void LED_run(void)
{
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  delay(500);
  }

void setup()
{
   pinMode(LED_BUILTIN, OUTPUT); //ESP8266 Status light 
   ESP.wdtDisable();//Turn off the software watchdog
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
  
  while(1) 
  {
   Sys_run();//System run
   LED_run();//Breathing lamp
  }
}

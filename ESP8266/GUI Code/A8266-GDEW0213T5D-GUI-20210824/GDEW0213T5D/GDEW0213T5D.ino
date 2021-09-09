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
  while(1) 
  {
   Sys_run();//System run
   LED_run();//Breathing lamp
  }
}

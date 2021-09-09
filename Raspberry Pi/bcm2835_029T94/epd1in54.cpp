
#include <stdlib.h>
#include "epd1in54.h"

Epd::~Epd() {
};

Epd::Epd() {
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
};


/**
 *  @brief: basic function for sending commands
 */
void Epd::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes LOW
 */
void Epd::WaitUntilIdle(void) {
    while(DigitalRead(busy_pin) == HIGH) {      //LOW: idle, HIGH: busy
        DelayMs(100);
    }      
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(200);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);    
}



/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void Epd::EPD_HW_Init(void)
{
	Reset();
	  
	WaitUntilIdle();   
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();  
		
	SendCommand(0x01); //Driver output control      
	SendData(0x27);  //0x0127-->(295+1)=296
	SendData(0x01);
	SendData(0x00);

	SendCommand(0x11); //data entry mode       
	SendData(0x01);

	SendCommand(0x44); //set Ram-X address start/end position   
	SendData(0x00);
	SendData(0x0F);    //0x0F-->(15+1)*8=128

	SendCommand(0x45); //set Ram-Y address start/end position          
	SendData(0x27);  //0x0127-->(295+1)=296
	SendData(0x01);
	SendData(0x00);
	SendData(0x00); 

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x05);	
	
    SendCommand(0x21); //  Display update control
	SendData(0x00);	
	SendData(0x80);

    SendCommand(0x18);  //Read built-in temperature sensor
	SendData(0x80);	

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;    
	SendData(0x27);  //0x0127-->(295+1)=296
	SendData(0x01);
  WaitUntilIdle();
	
}
/////////////////////////////////////////////////////////////////////////////////////////
void Epd::EPD_Update(void)
{   
  SendCommand(0x22); 
  SendData(0xF7);   
  SendCommand(0x20); 
  WaitUntilIdle();

}
void Epd::EPD_Part_Update(void)
{
	SendCommand(0x22); 
	SendData(0xFF);   
	SendCommand(0x20); 
	WaitUntilIdle();		
}
//////////////////////////////All screen update////////////////////////////////////////////
void Epd::EPD_WhiteScreen_ALL(const unsigned char *datas)
{
   unsigned int i;	
  SendCommand(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_BYTES;i++)
   {               
     SendData(*datas);
			datas++;
   }
   EPD_Update();	 
}
///////////////////////////Part update//////////////////////////////////////////////
//The x axis is reduced by one byte, and the y axis is reduced by one pixel.
void Epd::EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
	unsigned int i;   
	const unsigned char  *datas_flag;   
	datas_flag=datas;

	
  SendCommand(0x24);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_BYTES;i++)
   {               
     SendData(*datas);
			datas++;
   }
	 datas=datas_flag;
  SendCommand(0x26);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_BYTES;i++)
   {               
     SendData(*datas);
			datas++;
   }
   EPD_Update();		 
	 
}
void Epd::EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	x_start=x_start/8;//×a???a×??ú
	x_end=x_start+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_start;
	if(y_start>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_start+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	SendCommand(0x44);       // set RAM x address start/end, in page 35
	SendData(x_start);    // RAM x address start at 00h;
	SendData(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	SendCommand(0x45);       // set RAM y address start/end, in page 35
	SendData(y_start2);    // RAM y address start at 0127h;
	SendData(y_start1);    // RAM y address start at 0127h;
	SendData(y_end2);    // RAM y address end at 00h;
	SendData(y_end1);    // ????=0	


	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(x_start); 
	SendCommand(0x4F);   // set RAM y address count to 0X127;    
	SendData(y_start2);
	SendData(y_start1);
	
	
	 SendCommand(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     SendData(*datas);
			datas++;
   } 
	 EPD_Part_Update();

}

void Epd::EPD_DeepSleep(void)
{  	
  SendCommand(0x10); //enter deep sleep
  SendData(0x01); 
  //driver_delay_xms(100);
}

/* END OF FILE */



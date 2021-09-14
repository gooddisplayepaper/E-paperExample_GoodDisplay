
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

int Epd::Init(const unsigned char* lut) {
    /* this calls the peripheral hardware interface, see epdif */
    if (IfInit() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    this->lut = lut;
    Reset();
    SendCommand(DRIVER_OUTPUT_CONTROL);
    SendData((EPD_HEIGHT - 1) & 0xFF);
    SendData(((EPD_HEIGHT - 1) >> 8) & 0xFF);
    SendData(0x00);                     // GD = 0; SM = 0; TB = 0;
    SendCommand(BOOSTER_SOFT_START_CONTROL);
    SendData(0xD7);
    SendData(0xD6);
    SendData(0x9D);
    SendCommand(WRITE_VCOM_REGISTER);
    SendData(0xA8);                     // VCOM 7C
    SendCommand(SET_DUMMY_LINE_PERIOD);
    SendData(0x1A);                     // 4 dummy lines per gate
    SendCommand(SET_GATE_TIME);
    SendData(0x08);                     // 2us per line
    SendCommand(DATA_ENTRY_MODE_SETTING);
    SendData(0x03);                     // X increment; Y increment
    SetLut(this->lut);
    /* EPD hardware init end */
    return 0;
}

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

/**
 *  @brief: set the look-up table register
 */
void Epd::SetLut(const unsigned char* lut) {
    this->lut = lut;
    SendCommand(WRITE_LUT_REGISTER);
    /* the length of look-up table is 30 bytes */
    for (int i = 0; i < 30; i++) {
        SendData(this->lut[i]);
    }
}

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void Epd::SetFrameMemory(
    const unsigned char* image_buffer,
    int x,
    int y,
    int image_width,
    int image_height
) {
    int x_end;
    int y_end;

    if (
        image_buffer == NULL ||
        x < 0 || image_width < 0 ||
        y < 0 || image_height < 0
    ) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= this->width) {
        x_end = this->width - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= this->height) {
        y_end = this->height - 1;
    } else {
        y_end = y + image_height - 1;
    }
    SetMemoryArea(x, y, x_end, y_end);
    SetMemoryPointer(x, y);
    SendCommand(WRITE_RAM);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
        for (int i = 0; i < (x_end - x + 1) / 8; i++) {
            SendData(image_buffer[i + j * (image_width / 8)]);
        }
    }
}

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void Epd::SetFrameMemory1(
    const unsigned char* image_buffer,
    int x,
    int y,
    int image_width,
    int image_height
) {
    int x_end;
    int y_end;
    int x_dot;
    int y_dot;
    unsigned char tempOriginal;

    unsigned int tempcol=1;

    unsigned int templine=0;

    if (
        image_buffer == NULL ||
        x < 0 || image_width < 0 ||
        y < 0 || image_height < 0
    ) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= this->width) {
        x_end = this->width - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= this->height) {
        y_end = this->height - 1;
    } else {
        y_end = y + image_height - 1;
    }
    
    SetMemoryArea(x, y, x_end, y_end);
    SetMemoryPointer(x, y);
    SendCommand(WRITE_RAM);
    /* send the image data */
    x_dot=((x_end - x + 1) / 8);
    y_dot=(y_end - y + 1);
    for (int i = 0; i< y_dot*x_dot; i++) { 
           tempOriginal=*(image_buffer+ALLSCREEN_BYTES-(x_dot*tempcol-i%x_dot)); //(5000-(25*y-i%25))

             templine++;

             if(templine>=x_dot)

             {

               tempcol++;

               templine=0;

             }
           SendData(tempOriginal);     
    }
}

/**
 *  @brief: clear the frame memory with the specified color.
 *          this won't update the display.
 */
void Epd::ClearFrameMemory(unsigned char color) {
    SetMemoryArea(0, 0, this->width - 1, this->height - 1);
    SetMemoryPointer(0, 0);
    SendCommand(WRITE_RAM);
    /* send the color data */
    for (int i = 0; i < this->width / 8 * this->height; i++) {
        SendData(color);
    }
}

/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will 
 *          set the other memory area.
 */
void Epd::DisplayFrame(void) {
    SendCommand(DISPLAY_UPDATE_CONTROL_2);
    SendData(0xC4);
    SendCommand(MASTER_ACTIVATION);
    SendCommand(TERMINATE_FRAME_READ_WRITE);
    WaitUntilIdle();
}

/**
 *  @brief: private function to specify the memory area for data R/W
 */
void Epd::SetMemoryArea(int x_start, int y_start, int x_end, int y_end) {
    SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x_start >> 3) & 0xFF);
    SendData((x_end >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
    SendData(y_start & 0xFF);
    SendData((y_start >> 8) & 0xFF);
    SendData(y_end & 0xFF);
    SendData((y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void Epd::SetMemoryPointer(int x, int y) {
    SendCommand(SET_RAM_X_ADDRESS_COUNTER);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
    SendData(y & 0xFF);
    SendData((y >> 8) & 0xFF);
    WaitUntilIdle();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the 
 *          deep-sleep mode to save power. 
 *          The deep sleep mode would return to standby by hardware reset. 
 *          You can use Epd::Init() to awaken
 */
void Epd::Sleep() {
    SendCommand(DEEP_SLEEP_MODE);
    WaitUntilIdle();
}

const unsigned char lut_full_update[] =
{
    0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 
    0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88, 
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51, 
    0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

const unsigned char lut_partial_update[] =
{
    0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};










/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void Epd::EPD_HW_Init(void)
{
	Reset();
	
	WaitUntilIdle();   
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();  
		
	SendCommand(0x01); //Driver output control      
	SendData(0xC7);
	SendData(0x00);
	SendData(0x00);

	SendCommand(0x11); //data entry mode       
	SendData(0x01);

	SendCommand(0x44); //set Ram-X address start/end position   
	SendData(0x00);
	SendData(0x18);    //0x0C-->(18+1)*8=200

	SendCommand(0x45); //set Ram-Y address start/end position          
	SendData(0xC7);   //0xC7-->(199+1)=200
	SendData(0x00);
	SendData(0x00);
	SendData(0x00); 

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x05);	
	  	
  SendCommand(0x18); 
	SendData(0x80);	

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;    
	SendData(0xC7);
	SendData(0x00);
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



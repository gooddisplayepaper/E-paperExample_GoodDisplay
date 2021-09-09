#include <stdlib.h>
#include "epd.h"

Epd::~Epd()
{
};

Epd::Epd()
{
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
void Epd::SendCommand(unsigned char command)
{
	DigitalWrite(dc_pin, LOW);
	SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data)
{
	DigitalWrite(dc_pin, HIGH);
	SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void Epd::WaitUntilIdle(void)
{
   while(!DigitalRead(busy_pin))//0 is busy
  {
    ESP.wdtFeed(); //Feed dog to prevent system reset
    }  
}


int Epd::Init(void)
{
  /* this calls the peripheral hardware interface, see epdif */
  if (IfInit() != 0) {
    return -1;
  }
  /* EPD hardware init start */
  Reset();

  SendCommand(0x04);  
  WaitUntilIdle(); //waiting for the electronic paper IC to release the idle signal

  SendCommand(0x00);     //panel setting
  SendData(0x1f);    //LUT from OTP
    
  SendCommand(0x61);     //resolution setting
  SendData (0x68);  //104       
  SendData (0x00);  //212    
  SendData (0xd4); 

  SendCommand(0X50);     //VCOM AND DATA INTERVAL SETTING      
  SendData(0x97);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

  /* EPD hardware init end */
  return 0;
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void)
{
	DigitalWrite(reset_pin, LOW);                //module reset
	DelayMs(20);
	DigitalWrite(reset_pin, HIGH);
	DelayMs(20);

  DigitalWrite(reset_pin, LOW);                //module reset
  DelayMs(20);
  DigitalWrite(reset_pin, HIGH);
  DelayMs(20);

  DigitalWrite(reset_pin, LOW);                //module reset
  DelayMs(20);
  DigitalWrite(reset_pin, HIGH);
  DelayMs(20);
}

void Epd::Clear(void)
{
	int w, h;
	w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	h = EPD_HEIGHT;
	SendCommand(0x10);
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}
  SendCommand(0x13);
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      SendData(0xff);
    }
  }
   //Refresh
    SendCommand(0x12);   //DISPLAY REFRESH   
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    WaitUntilIdle();          //waiting for the electronic paper IC to release the idle signal

}

void Epd::Display(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

		SendCommand(0x10);
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(0xff);
			}
		}
    SendCommand(0x13);
    for (int j = 0; j < h; j++) {
      for (int i = 0; i < w; i++) {
        SendData(frame_buffer[i + j * w]);
      }
    }	

   //Refresh
    SendCommand(0x12);   //DISPLAY REFRESH   
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    WaitUntilIdle();          //waiting for the electronic paper IC to release the idle signal

}




/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void Epd::DisplayFrame(void)
{
	//DISPLAY REFRESH
   //Refresh
    SendCommand(0x12);   //DISPLAY REFRESH   
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    WaitUntilIdle();          //waiting for the electronic paper IC to release the idle signal

}


/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Init() to awaken
 */
void Epd::Sleep()
{
    SendCommand(0X50);  //VCOM AND DATA INTERVAL SETTING     
    SendData(0xf7); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57    WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7  

    SendCommand(0X02);   //power off
    WaitUntilIdle();          //waiting for the electronic paper IC to release the idle signal
    SendCommand(0X07);   //deep sleep
    SendData(0xA5);
}




/* END OF FILE */

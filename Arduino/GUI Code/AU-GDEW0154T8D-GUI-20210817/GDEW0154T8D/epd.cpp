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
	while(DigitalRead(busy_pin) == 0) {      //LOW: busy, HIGH: idle
		delay(100);
	}
	delay(200);
}


int Epd::Init(void)
{
  int w, h;
  w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
  h = EPD_HEIGHT;
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
  SendData (0x98);  //152      
  SendData (0x00);  //152 
  SendData (0x98); 

  SendCommand(0X50);     //VCOM AND DATA INTERVAL SETTING      
  SendData(0x97);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
 //Reset register parameters//////////
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
	delay(10);
	DigitalWrite(reset_pin, HIGH);
	delay(10);

  DigitalWrite(reset_pin, LOW);                //module reset
  delay(10);
  DigitalWrite(reset_pin, HIGH);
  delay(10);

  DigitalWrite(reset_pin, LOW);                //module reset
  delay(10);
  DigitalWrite(reset_pin, HIGH);
  delay(10);
}
void Epd::PaintAllClear(void)
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


void Epd::SetFrameMemory(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
)
{
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
  if (x + image_width >=EPD_WIDTH) {
    x_end = EPD_WIDTH - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= EPD_HEIGHT) {
    y_end = EPD_HEIGHT - 1;
  } else {
    y_end = y + image_height - 1;
  }
   //Write RAM  datas
    SendCommand(0x91);   //This command makes the display enter partial mode
    SendCommand(0x90);   //resolution setting
    SendData (x);   //x-start     
    SendData (x_end-1);   //x-end  
    SendData (y/256);
    SendData (y%256);   //y-start      
    SendData (y_end/256);    
    SendData (y_end%256-1);  //y-end
    SendData (0x28); 

    SendCommand(0x13);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++) {
      for (int i = 0; i < (x_end - x + 1) / 8; i++) {
        SendData(image_buffer[i + j * (image_width / 8)]);
      }
    }
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
    SendCommand(0x92);    //Enter normal mode
    SendCommand(0x12);   //DISPLAY REFRESH   
    delay(10);   //!!!The delay here is necessary, 200uS at least!!!     
    WaitUntilIdle();           //waiting for the electronic paper IC to release the idle signal

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

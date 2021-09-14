

#include <stdlib.h>
#include "epd2in13b.h"
#include "epdif.h"

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

int Epd::Init(void) {
    if (IfInit() != 0) {
        return -1;
    }
    Reset();

    SendCommand(0x04);  //POWER ON
    WaitUntilIdle();

    SendCommand(0x00); //panel setting
    SendData(0x1f);   //LUT from OTP£¬KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f

    SendCommand(0x61); //Resolution setting
    SendData(0x80); //128
    SendData(0x01); //296
    SendData(0x28);

	SendCommand(0x50); //VCOM AND DATA INTERVAL SETTING		
    SendData(0x97);   //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

    return 0;
}

void Epd::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

void Epd::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

void Epd::WaitUntilIdle(void) {
    SendCommand(GET_STATUS);
    while(DigitalRead(busy_pin) == 0) {      //0: busy, 1: idle
        DelayMs(100);
    }      
}

void Epd::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(100);                               //At least 10ms delay 
    DigitalWrite(reset_pin, HIGH);
    DelayMs(100);                               //At least 10ms delay  

    DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(100);                               //At least 10ms delay 
    DigitalWrite(reset_pin, HIGH);
    DelayMs(100);                               //At least 10ms delay  

	DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(100);                               //At least 10ms delay 
    DigitalWrite(reset_pin, HIGH);
    DelayMs(100);                               //At least 10ms delay  
}



void Epd::DisplayFrame(const unsigned char* frame_buffer) {

    if (frame_buffer != NULL) {
        SendCommand(DATA_START_TRANSMISSION_1);
        for(int i = 0; i < width * height / 8; i++) {
            SendData(0xFF);      // bit set: white, bit reset: black
        }
        DelayMs(2);
        SendCommand(DATA_START_TRANSMISSION_2); 
        for(int i = 0; i < width * height / 8; i++) {
            SendData(frame_buffer[i]);
        }  
        DelayMs(2);                  
    }

    SendCommand(DISPLAY_REFRESH); 
    DelayMs(100);
    WaitUntilIdle();

}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Reset() to awaken or Epd::Init() to initialize
 */
void Epd::Sleep() {
	SendCommand(0x50); //VCOM AND DATA INTERVAL SETTING		
    SendData(0xf7);   //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7        
               
    SendCommand(0x02);          //power off
    WaitUntilIdle();
    SendCommand(0x07);         //deep sleep
    SendData(0xA5);
}



/* END OF FILE */


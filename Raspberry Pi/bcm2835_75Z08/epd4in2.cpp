

#include <stdlib.h>
#include "epd4in2.h"


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
    SendCommand(0x01);
    SendData(0x07);                  // VDS_EN, VDG_EN
    SendData(0x07);                  // VCOM_HV, VGHL_LV[1], VGHL_LV[0]
    SendData(0x3f);                  // VDH
    SendData(0x3f);                  // VDL
    //SendData(0xff);                  // VDHR

    SendCommand(0x04);
    WaitUntilIdle();
    SendCommand(0x00);
    SendData(0x0f);     //KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f

    SendCommand(0X15);		
    SendData(0x00);		

    SendCommand(0X50);			//VCOM AND DATA INTERVAL SETTING
    SendData(0x11);
    SendData(0x07);

    SendCommand(0X60);			//TCON SETTING
    SendData(0x22);


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
    DelayMs(200);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);    
}



void Epd::DisplayFrame(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red) {
    if (frame_buffer_black != NULL) {
        SendCommand(DATA_START_TRANSMISSION_1);
        DelayMs(2);
        for (int i = 0; i < this->width * this->height / 8; i++) {
            SendData(frame_buffer_black[i]);
        }
        DelayMs(2);
    }
    if (frame_buffer_red != NULL) {
        SendCommand(DATA_START_TRANSMISSION_2);
        DelayMs(2);
        for (int i = 0; i < this->width * this->height / 8; i++) {
            SendData(~frame_buffer_red[i]);
        }
        DelayMs(2);
    }
    SendCommand(DISPLAY_REFRESH);
    WaitUntilIdle();
}

void Epd::DisplayFrame1(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red) {
    if (frame_buffer_black != NULL) {
        SendCommand(DATA_START_TRANSMISSION_1);
        DelayMs(2);
        for (int i = 0; i < this->width * this->height / 8; i++) {
            SendData(frame_buffer_black[i]);
        }
        DelayMs(2);
    }
    if (frame_buffer_red != NULL) {
        SendCommand(DATA_START_TRANSMISSION_2);
        DelayMs(2);
        for (int i = 0; i < this->width * this->height / 8; i++) {
            SendData(frame_buffer_red[i]);
        }
        DelayMs(2);
    }
    SendCommand(DISPLAY_REFRESH);
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
                
    SendCommand(0x02);          //power off
    WaitUntilIdle();
    SendCommand(0x07);         //deep sleep
    SendData(0xA5);
}




/* END OF FILE */





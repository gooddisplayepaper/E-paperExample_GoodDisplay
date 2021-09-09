#include <stdlib.h>
#include "epd7in5.h"
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

    SendCommand(POWER_SETTING); 
    SendData(0x37);
    SendData(0x00);

    SendCommand(PANEL_SETTING);
    SendData(0xCF);
    SendData(0x08);
    
    SendCommand(BOOSTER_SOFT_START);
    SendData(0xc7);     
    SendData(0xcc);
    SendData(0x28);

    SendCommand(POWER_ON);
    WaitUntilIdle();

    SendCommand(PLL_CONTROL);
    SendData(0x3a);

    SendCommand(TEMPERATURE_CALIBRATION);
    SendData(0x00);

    SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    SendData(0x77);

    SendCommand(TCON_SETTING);
    SendData(0x22);

    SendCommand(TCON_RESOLUTION);
    SendData(0x02);     //source 600
    SendData(0x58);
    SendData(0x01);     //gate 448
    SendData(0xc0);

    SendCommand(VCM_DC_SETTING);
    SendData(0x28);      //decide by LUT file

    SendCommand(0xe5);           //FLASH MODE            
    SendData(0x03);  

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

void Epd::DisplayFrame(const unsigned char* frame_buffer) {
    unsigned char j,temp1, temp2;
    SendCommand(DATA_START_TRANSMISSION_1);
    for(int i = 0; i < 33600; i++) {
        temp1 = frame_buffer[i];
        for(j=0;j<4;j++)    //1bit to 4bit
        {
           if(temp1&0x80)   //Analysis the first 1bit
               temp2 = 0x00;  //black(1bit to 4bit)
           else
               temp2 = 0x03;  //white(1bit to 4bit)

           temp2 <<= 4;     //move to the Hight 4bit
           temp1 <<= 1;     //move 1bit

           if(temp1&0x80)   //Analysis the second 1bit
               temp2 |= 0x00; //black(1bit to 4bit),Data consolidation
           else
               temp2 |= 0x03; //white(1bit to 4bit),Data consolidation

           temp1 <<= 1;     //move 1bit¡ê?turn the next 1bit

           SendData(temp2); //write a byte,Contains two 4bit pixels
        }
    }
    SendCommand(DISPLAY_REFRESH);
    DelayMs(100);
    WaitUntilIdle();
}

void Epd::Sleep(void) {
    SendCommand(POWER_OFF);
    WaitUntilIdle();
    SendCommand(DEEP_SLEEP);
    SendData(0xa5);
}

/* END OF FILE */



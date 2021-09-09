

#include <stdlib.h>
#include "epd7in5b.h"
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
    SendData(0xC7);     
    SendData(0xCC);
    SendData(0x28);
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
    SendCommand(0xE5);           //FLASH MODE            
    SendData(0x03);  
    SendCommand(POWER_ON);
    WaitUntilIdle();
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
    unsigned char j, temp1,temp2,temp3;
    SendCommand(DATA_START_TRANSMISSION_1);
    for(int i = 0; i < 67200; i++) {  
            temp1 = frame_buffer[i];
            for(j=0;j<2;j++)         //2bit to 4bit
            {
                temp2 = temp1&0xc0 ;   //Analysis the first 2bit
                if(temp2 == 0xc0)
                    temp3 = 0x00;            //black(2bit to 4bit)
                else if(temp2 == 0x00)
                    temp3 = 0x03;        //white(2bit to 4bit)
                else
                    temp3 = 0x04;        //red(2bit to 4bit)

                temp3 <<=4;            //move to the Hight 4bit
                temp1 <<=2;            //move 2bit
                temp2 = temp1&0xc0 ;   //Analysis the second 2bit
                if(temp2 == 0xc0)
                    temp3 |= 0x00;       //black(2bit to 4bit),Data consolidation
                else if(temp2 == 0x00)
                    temp3 |= 0x03;       //white(2bit to 4bit),Data consolidation
                else
                    temp3 |= 0x04;       //red(2bit to 4bit),Data consolidation

                temp1 <<=2;            //move 2bit,turn the next 2bit
                SendData(temp3);
            }
    }
    SendCommand(DISPLAY_REFRESH);
    DelayMs(100);
    WaitUntilIdle();
}
void Epd::DisplayFrame1(const unsigned char* frame_buffer) {
    SendCommand(DATA_START_TRANSMISSION_1);
    for(int i = 0; i < this->width / 2 * this->height; i++) {  
        SendData(frame_buffer[i]);
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



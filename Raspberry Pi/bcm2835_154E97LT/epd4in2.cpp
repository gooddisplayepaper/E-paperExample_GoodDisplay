

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
    WaitUntilIdle();
    SendCommand(0x12); // soft reset
    WaitUntilIdle();
    SendCommand(0x74); //set analog block control
    SendData(0x54);
    SendCommand(0x7E); //set digital block control
    SendData(0x3B);

    SendCommand(0x01); //Driver output control
    SendData(0x97);
    SendData(0x00);
    SendData(0x00);

    SendCommand(0x11); //data entry mode
    SendData(0x01);

    SendCommand(0x44); //set Ram-X address start/end position
    SendData(0x00);
    SendData(0x12);    //0x12-->(18+1)*8=152

    SendCommand(0x45); //set Ram-Y address start/end position
    SendData(0x97);   //0x97-->(151+1)=152
    SendData(0x00);
    SendData(0x00);
    SendData(0x00);
    SendCommand(0x3C); //set border
    SendData(0x01);

    /////////////voltage set/////////////
    SendCommand(0x2C); //set vcom
    SendData( 0x52);

    SendCommand(0x03);//set gate voltage
    SendData(LUT[70]);

    SendCommand(0x04); //set source voltage
    SendData(LUT[71]); //vsh1
    SendData(LUT[72]); //vsh2
    SendData(LUT[73]); //vsl

    SendCommand(0x3A); // set frequency1-dummy line
    SendData(LUT[74]);
    SendCommand(0x3B); // set frequency2-line width
    SendData(LUT[75]);

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
    while(DigitalRead(busy_pin) == 1) {      //1: busy, 0: idle
        DelayMs(100);
    }
}

void Epd::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset
    DelayMs(200);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);
}

void Epd::SetLut(void) {
    unsigned int count;     
    SendCommand(0x32);  //write LUT by MCU
    for(count = 0; count < 70; count++) {
        SendData(LUT[count]);
    }
    WaitUntilIdle();
}

void Epd::DisplayFrame(const unsigned char* frame_buffer) {
    if (frame_buffer != NULL) {
          unsigned int i;
          unsigned char tempOriginal;
          unsigned int tempcol=0;
          unsigned int templine=0;

          SendCommand(0x4E);
          SendData(0x00);


          SendCommand(0x4F);
          SendData(0x97);
          SendData(0x00);
          WaitUntilIdle();
            if(MONO)
            SendCommand(0x24);   //write RAM for black(0)/white (1)
            //if(RED)
            //Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)

            for(i=0;i<ALLSCREEN_BYTES;i++)
           {
             tempOriginal=*(frame_buffer+templine*MAX_COLUMN_BYTES+tempcol); //x*152+y
             templine++;
             if(templine>=MAX_LINE_BYTES)
             {
               tempcol++;
               templine=0;
             }
             SendData(tempOriginal);
           }
    }

    SetLut();
    // Epaper update
    SendCommand(0x21);
    SendData(0x40);
    SendCommand(0x22);
    SendData(0xC7);
    SendCommand(0x20);
    DelayMs(100);
    WaitUntilIdle();

}

void Epd::DisplayFrame1(const unsigned char* frame_buffer) {
    if (frame_buffer != NULL) {
          unsigned int i=0;
          unsigned char tempOriginal;
          unsigned int tempcol=1;
          unsigned int templine=0;
  
          SendCommand(0x4E);
          SendData(0x00);


          SendCommand(0x4F);
          SendData(0x97);
          SendData(0x00);
          WaitUntilIdle();
            if(MONO)
            SendCommand(0x24);   //write RAM for black(0)/white (1)
            //if(RED)
            //Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
            for(i=0;i<ALLSCREEN_BYTES;i++)  //2888
           {
             tempOriginal=*(frame_buffer+ALLSCREEN_BYTES-(MAX_LINE_BYTES*tempcol-i%MAX_LINE_BYTES)); //(2888-(19*y-i%19))
             templine++;
             if(templine>=MAX_LINE_BYTES)  //x>=152
             {
               tempcol++;
               templine=0;
             }
             SendData(tempOriginal);
           }
    }

    SetLut();
    // Epaper update
    SendCommand(0x21);
    SendData(0x40);
    SendCommand(0x22);
    SendData(0xC7);
    SendCommand(0x20);
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
    SendCommand(0x10);         //deep sleep
    SendData(0x01);
    DelayMs(100);
}

const unsigned char LUT[] =
{
0x80,   0xA5,   0x10,   0x0,    0x0,    0x0,    0x0,
0x10,   0xA5,   0x80,   0x0,    0x0,    0x0,    0x0,
0x80,   0xA5,   0x10,   0x0,    0x0,    0x0,    0x0,
0x10,   0xA5,   0x80,   0x0,    0x0,    0x0,    0x0,
0x0,    0x0,    0x0,    0x0,    0x0,    0x0,    0x0,
0x6,    0x8,    0x0,    0x0,    0x2,
0xC,    0x0,    0xC,    0x0,    0x5,
0x8,    0x6,    0x0,    0x0,    0x2,
0x0,    0x0,    0x0,    0x0,    0x0,
0x0,    0x0,    0x0,    0x0,    0x0,
0x0,    0x0,    0x0,    0x0,    0x0,
0x0,    0x0,    0x0,    0x0,    0x0,
0x17,   0x41,   0x0,    0x32,
0x15,   0x0B};




/* END OF FILE */



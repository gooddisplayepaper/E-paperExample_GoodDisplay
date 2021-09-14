#include <stdlib.h>
#include "epd7in5.h"
#include "epdif.h"
#include "imagedata.h" 



Epd::~Epd() {
};

Epd::Epd() {
	/*
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_1;*/
    width = EPD_WIDTH;
    height = EPD_HEIGHT;

};



//////////////////////////////////////////////////////////////////////////////////
//SPI_Delay
void Epd::SPI_Delay(unsigned char xrate)
{
	unsigned char i;
	while(xrate)
	{
		for(i=0;i<2;i++);
		xrate--;
	}
}
//SPI_Write
/*
void Epd::SPI_Write(unsigned char data) {
    SpiTransfer(data);
}
*/
void Epd::SPI_Write(unsigned char value)                                    
{                                                           
    unsigned char i;

	
	SPI_Delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_W21_SCL_0;
		SPI_Delay(1);
        if(value & 0x80)
        	EPD_W21_SDA_1;
        else
        	EPD_W21_SDA_0;		
        value = (value << 1); 
		SPI_Delay(1);
		//driver_delay_us(1);
        EPD_W21_SCL_1; 
        SPI_Delay(1);
    }
}





//EPD_W21_WriteCMD_M1
void Epd::EPD_W21_WriteCMD_M1(unsigned char command)
{
	EPD_W21_CS_M1_0;
	EPD_W21_DC_M1_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_M1_1;
}

void Epd::EPD_W21_WriteDATA_M1(unsigned char command)
{
	EPD_W21_CS_M1_0;
	EPD_W21_DC_M1_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_M1_1;
}


void Epd::EPD_W21_WriteCMD_S1(unsigned char command)
{
	EPD_W21_CS_S1_0;
	EPD_W21_DC_M1_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_S1_1;

}


void Epd::EPD_W21_WriteDATA_S1(unsigned char command)
{
	EPD_W21_CS_S1_0;
	EPD_W21_DC_M1_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_S1_1;
}






void Epd::EPD_W21_WriteCMD_ALL(unsigned char command)
{
	SPI_Delay(1);
	EPD_W21_CS_M1_0;
	EPD_W21_CS_S1_0;
	EPD_W21_CS_M2_0;
	EPD_W21_CS_S2_0;
	SPI_Delay(1);
	EPD_W21_DC_M1_0;		// command write
	EPD_W21_DC_M2_0;		// command write
	SPI_Delay(1);
	SPI_Write(command);
	SPI_Delay(1);
	EPD_W21_CS_S2_1;
	EPD_W21_CS_M2_1;
	EPD_W21_CS_S1_1;
	EPD_W21_CS_M1_1;

}


void Epd::EPD_W21_WriteDATA_ALL(unsigned char command)
{
	SPI_Delay(1);
	EPD_W21_CS_M1_0;
	EPD_W21_CS_S1_0;
	EPD_W21_CS_M2_0;
	EPD_W21_CS_S2_0;
	SPI_Delay(1);
	EPD_W21_DC_M1_1;		// command write
	EPD_W21_DC_M2_1;		// command write
	SPI_Delay(1);
	SPI_Write(command);
	SPI_Delay(1);
	EPD_W21_CS_S2_1;
	EPD_W21_CS_M2_1;
	EPD_W21_CS_S1_1;
	EPD_W21_CS_M1_1;
}



void Epd::EPD_W21_WriteCMD_M1M2(unsigned char command)
{
	SPI_Delay(1);
	EPD_W21_CS_M1_0;
	EPD_W21_CS_M2_0;
	SPI_Delay(1);
	EPD_W21_DC_M1_0;		// command write
	EPD_W21_DC_M2_0;		// command write
	SPI_Delay(1);
	SPI_Write(command);
	SPI_Delay(1);
	EPD_W21_CS_M1_1;
	EPD_W21_CS_M2_1;
}


void Epd::EPD_W21_WriteDATA_M1M2(unsigned char command)
{
	SPI_Delay(1);
	EPD_W21_CS_M1_0;
	EPD_W21_CS_M2_0;
	SPI_Delay(1);
	EPD_W21_DC_M1_1;		// command write
	EPD_W21_DC_M2_1;		// command write
	SPI_Delay(1);
	SPI_Write(command);
	SPI_Delay(1);
	EPD_W21_CS_M1_1;
	EPD_W21_CS_M2_1;
}


void Epd::EPD_W21_WriteCMD_M2(unsigned char command)
{
	SPI_Delay(1);
	EPD_W21_CS_M2_0;
	SPI_Delay(1);
	EPD_W21_DC_M2_0;		// command write
	SPI_Delay(1);
	SPI_Write(command);
	SPI_Delay(1);
	EPD_W21_CS_M2_1;
}


void Epd::EPD_W21_WriteDATA_M2(unsigned char command)
{

	EPD_W21_CS_M2_0;
	EPD_W21_DC_M2_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_M2_1;
}




void Epd::EPD_W21_WriteCMD_S2(unsigned char command)
{
	EPD_W21_CS_S2_0;
	EPD_W21_DC_M2_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_S2_1;
}


void Epd::EPD_W21_WriteDATA_S2(unsigned char command)
{
	EPD_W21_CS_S2_0;
	EPD_W21_DC_M2_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_S2_1;
}


//Read data for EPD
unsigned char Epd:: EPD_W21_ReadDATA_M1_temp(void)
{
	unsigned char i,j;
	EPD_W21_CS_M1_0;
	EPD_W21_CS_S1_1;
	EPD_W21_CS_M2_1;
	EPD_W21_CS_S2_1;
	EPD_W21_DC_M1_1;		// command mwrite
	SPI_Delay(1);

	j=0;
      SDI_IN;
	SPI_Delay(1);
	 for(i=0; i<8; i++)
	{
		 EPD_W21_SCL_0;
		SPI_Delay(1);
		j=(j<<1);
		if(EPD_W21_ReadDATA_SDA==1)
			j|=0x01;
		else
			j&=0xfe;
		SPI_Delay(1);
		EPD_W21_SCL_1;
		SPI_Delay(1);
	}

	 EPD_W21_CS_M1_1;
   SDI_OUT;

 	 return j;
}

void Epd::EPD_W21_Init(void)
{
	EPD_W21_CS_M1_1;
	EPD_W21_CS_S1_1;
	EPD_W21_CS_M2_1;
	EPD_W21_CS_S2_1;

	EPD_W21_RST_M1_0;
	EPD_W21_RST_M2_0;
  //DelayMs(200);
	EPD_W21_RST_M1_1;
	EPD_W21_RST_M2_1;
  //DelayMs(200);
	
}
int Epd::Init(void) {
    if (IfInit() != 0) {
        return -1;
    }
      unsigned char temp;
	EPD_W21_Init();
	
	EPD_W21_WriteCMD_M1(0x00);			//panel setting
	EPD_W21_WriteDATA_M1(0x0f);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	EPD_W21_WriteCMD_S1(0x00);			//panel setting
	EPD_W21_WriteDATA_S1(0x0f);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	//M2¡¢S2 turn  180
	EPD_W21_WriteCMD_M2(0x00);			//panel setting
	EPD_W21_WriteDATA_M2(0x03);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	EPD_W21_WriteCMD_S2(0x00);			//panel setting
	EPD_W21_WriteDATA_S2(0x03);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	
	EPD_W21_WriteCMD_M1(0x06);         //booster soft start
	EPD_W21_WriteDATA_M1 (0x17);		//A
	EPD_W21_WriteDATA_M1 (0x17);		//B
	EPD_W21_WriteDATA_M1 (0x39);		//C
	EPD_W21_WriteDATA_M1 (0x17);
	EPD_W21_WriteCMD_M2(0x06);         //booster soft start
	EPD_W21_WriteDATA_M2 (0x17);		//A
	EPD_W21_WriteDATA_M2 (0x17);		//B
	EPD_W21_WriteDATA_M2 (0x39);		//C
	EPD_W21_WriteDATA_M2 (0x17);

	EPD_W21_WriteCMD_M1(0x61);			//resolution setting
	EPD_W21_WriteDATA_M1 (0x02);
	EPD_W21_WriteDATA_M1 (0x88);       //source 648
	EPD_W21_WriteDATA_M1 (0x01);		//gate 492
	EPD_W21_WriteDATA_M1 (0xEC);
	EPD_W21_WriteCMD_S1(0x61);			//resolution setting
	EPD_W21_WriteDATA_S1 (0x02);
	EPD_W21_WriteDATA_S1 (0x90);       //source 656
	EPD_W21_WriteDATA_S1 (0x01);		//gate 492
	EPD_W21_WriteDATA_S1 (0xEC);
	EPD_W21_WriteCMD_M2(0x61);			//resolution setting
	EPD_W21_WriteDATA_M2 (0x02);
	EPD_W21_WriteDATA_M2 (0x90);       //source 656
	EPD_W21_WriteDATA_M2 (0x01);		//gate 492
	EPD_W21_WriteDATA_M2 (0xEC);
	EPD_W21_WriteCMD_S2(0x61);			//resolution setting
	EPD_W21_WriteDATA_S2 (0x02);
	EPD_W21_WriteDATA_S2 (0x88);       //source 648
	EPD_W21_WriteDATA_S2 (0x01);		//gate 492
	EPD_W21_WriteDATA_S2 (0xEC);


	EPD_W21_WriteCMD_ALL(0x15);			//DUSPI
	EPD_W21_WriteDATA_ALL(0x20);		

	EPD_W21_WriteCMD_ALL(0x50);			//Vcom and data interval setting
	EPD_W21_WriteDATA_ALL(0x11);	  //Border KW
	EPD_W21_WriteDATA_ALL(0x07);


	EPD_W21_WriteCMD_ALL(0x60);//TCON
	EPD_W21_WriteDATA_ALL(0x22);

	EPD_W21_WriteCMD_ALL(0xE3);
	EPD_W21_WriteDATA_ALL(0x00);
	
	
	//temperature
	EPD_W21_WriteCMD_M1(0x40);
	lcd_chkstatus_M1();
	//driver_delay_xms(300);
	temp=EPD_W21_ReadDATA_M1_temp();
	
	EPD_W21_WriteCMD_ALL(0xe0);//Cascade setting
	EPD_W21_WriteDATA_ALL(0x03);
	EPD_W21_WriteCMD_ALL(0xe5);//Force temperature
        EPD_W21_WriteDATA_ALL(temp);
}
void Epd::EPD_refresh(void)
{
	EPD_W21_WriteCMD_M1M2(0x04);
    DelayMs(300);
	EPD_W21_WriteCMD_ALL(0x12);			//DISPLAY REFRESH
	lcd_chkstatus_M1();
	lcd_chkstatus_S1();
	lcd_chkstatus_M2();
	lcd_chkstatus_S2();
}
	//////////Enter sleep//////////////////////////////
void Epd::EPD_sleep(void)
{
	EPD_W21_WriteCMD_ALL(0X02);  	//power off
	DelayMs(200);

	EPD_W21_WriteCMD_ALL(0X07);  	//deep sleep
	EPD_W21_WriteDATA_ALL(0xA5);
	DelayMs(200);
}
void Epd::lcd_chkstatus_M1(void)
{
	unsigned char busy;
	do
		{
		EPD_W21_WriteCMD_M1(0x71);
		busy = EPD_W21_ReadDATA_M1;
		busy =!(busy & 0x01);
		}
	while(busy);
   DelayMs(200);

}

void Epd::lcd_chkstatus_M2(void)
{
	unsigned char busy;
	do
		{
		EPD_W21_WriteCMD_M2(0x71);
		busy = EPD_W21_ReadDATA_M2;
		busy =!(busy & 0x01);
		}
	while(busy);
  DelayMs(200);
}
void Epd::lcd_chkstatus_S1(void)
{
	unsigned char busy;
	do
		{
		EPD_W21_WriteCMD_S1(0x71);
		busy = EPD_W21_ReadDATA_S1;
		busy =!(busy & 0x01);
		}
	while(busy);
  DelayMs(200);
}

void Epd::lcd_chkstatus_S2(void)
{
	unsigned char busy;
	do
		{
		EPD_W21_WriteCMD_S2(0x71);
		busy = EPD_W21_ReadDATA_S2;
		busy =!(busy & 0x01);
		}
	while(busy);
  DelayMs(200);
}


//picture white//
void Epd::pic_display_white(void)
{
	unsigned int column,row;
		////////M1 part//////////648*492
		EPD_W21_WriteCMD_M1(0x10);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(0xff);
		}
		EPD_W21_WriteCMD_M1(0x13);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(0x00);
		}
		
		////////S1 part//////////656*492
		EPD_W21_WriteCMD_S1(0x10);
		for(column=492;column<984;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_S1(0xff);
		}
		EPD_W21_WriteCMD_S1(0x13);
		for(column=492;column<984;column++)
		 for(row=81;row<163;row++)
		{                                                                                                         
		EPD_W21_WriteDATA_S1(0x00);
		}
		
		////////M2 part//////////656*492
		EPD_W21_WriteCMD_M2(0x10);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(0xff);
		}
		EPD_W21_WriteCMD_M2(0x13);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(0x00);
		}
		////////S2 part//////////648*492
		EPD_W21_WriteCMD_S2(0x10);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(0xff);
		}
		EPD_W21_WriteCMD_S2(0x13);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(0x00);
		}

   //REFRESH
 	EPD_W21_WriteCMD_M1M2(0x04);
    DelayMs(300);
	EPD_W21_WriteCMD_ALL(0x12);			//DISPLAY REFRESH
	lcd_chkstatus_M1();
	lcd_chkstatus_S1();
	lcd_chkstatus_M2();
	lcd_chkstatus_S2();

}
//picture//
void Epd::pic_display1(void)
{
	unsigned int column,row;
		////////M1 part//////////648*492
		EPD_W21_WriteCMD_M1(0x10);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(~gImage_1304x984_black[row+column*163]);
		}
		EPD_W21_WriteCMD_M1(0x13);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(gImage_1304x984_red[row+column*163]);
		}
		
		////////S1 part//////////656*492
		EPD_W21_WriteCMD_S1(0x10);
		for(column=492;column<984;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_S1(~gImage_1304x984_black[row+column*163]);
		}
		EPD_W21_WriteCMD_S1(0x13);
		for(column=492;column<984;column++)
		 for(row=81;row<163;row++)
		{                                                                                                         
		EPD_W21_WriteDATA_S1(gImage_1304x984_red[row+column*163]);
		}
		
		////////M2 part//////////656*492
		EPD_W21_WriteCMD_M2(0x10);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(~gImage_1304x984_black[row+column*163]);
		}
		EPD_W21_WriteCMD_M2(0x13);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(gImage_1304x984_red[row+column*163]);
		}
		////////S2 part//////////648*492
		EPD_W21_WriteCMD_S2(0x10);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(~gImage_1304x984_black[row+column*163]);
		}
		EPD_W21_WriteCMD_S2(0x13);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(gImage_1304x984_red[row+column*163]);
		}



   //REFRESH
 	EPD_W21_WriteCMD_M1M2(0x04);
    DelayMs(300);
	EPD_W21_WriteCMD_ALL(0x12);			//DISPLAY REFRESH
	lcd_chkstatus_M1();
	lcd_chkstatus_S1();
	lcd_chkstatus_M2();
	lcd_chkstatus_S2();

}
//picture//
void Epd::DisplayFrame(const unsigned char* frame_buffer_black,const unsigned char* frame_buffer_red)
{
	unsigned int column,row;
		////////M1 part//////////648*492
		EPD_W21_WriteCMD_M1(0x10);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(frame_buffer_black[row+column*163]);
		}
		EPD_W21_WriteCMD_M1(0x13);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(~frame_buffer_red[row+column*163]);
		}
		
		////////S1 part//////////656*492
		EPD_W21_WriteCMD_S1(0x10);
		for(column=492;column<984;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_S1(frame_buffer_black[row+column*163]);
		}
		EPD_W21_WriteCMD_S1(0x13);
		for(column=492;column<984;column++)
		 for(row=81;row<163;row++)
		{                                                                                                         
		EPD_W21_WriteDATA_S1(~frame_buffer_red[row+column*163]);
		}
		
		////////M2 part//////////656*492
		EPD_W21_WriteCMD_M2(0x10);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(frame_buffer_black[row+column*163]);
		}
		EPD_W21_WriteCMD_M2(0x13);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(~frame_buffer_red[row+column*163]);
		}
		////////S2 part//////////648*492
		EPD_W21_WriteCMD_S2(0x10);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(frame_buffer_black[row+column*163]);
		}
		EPD_W21_WriteCMD_S2(0x13);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(~frame_buffer_red[row+column*163]);
		}

   //REFRESH
 	EPD_W21_WriteCMD_M1M2(0x04);
    DelayMs(300);
	EPD_W21_WriteCMD_ALL(0x12);			//DISPLAY REFRESH
	lcd_chkstatus_M1();
	lcd_chkstatus_S1();
	lcd_chkstatus_M2();
	lcd_chkstatus_S2();

}
/////////////////////////////////////////////////////////////////////////
























/*
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
    unsigned char temp1, temp2;
    SendCommand(DATA_START_TRANSMISSION_1);
    for(int i = 0; i < 30720; i++) {   
        temp1 = frame_buffer[i];
        for(unsigned char j = 0; j < 8; j++) {
            if(temp1 & 0x80)
                temp2 = 0x03;
            else
                temp2 = 0x00;
            temp2 <<= 4;
            temp1 <<= 1;
            j++;
            if(temp1 & 0x80)
                temp2 |= 0x03;
            else
                temp2 |= 0x00;
            temp1 <<= 1;
            SendData(temp2); 
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
*/
/* END OF FILE */



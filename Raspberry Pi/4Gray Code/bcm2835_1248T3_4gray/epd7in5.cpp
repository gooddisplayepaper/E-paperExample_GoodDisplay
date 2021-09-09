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
    DelayMs(1000);
	EPD_W21_RST_M1_1;
	EPD_W21_RST_M2_1;
  DelayMs(1000);
	
}
int Epd::Init(void) {
    if (IfInit() != 0) {
        return -1;
    }
	unsigned char temp;
	EPD_W21_Init();
	
	EPD_W21_WriteCMD_M1(0x00);			//panel setting
	EPD_W21_WriteDATA_M1(0x1f);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	EPD_W21_WriteCMD_S1(0x00);			//panel setting
	EPD_W21_WriteDATA_S1(0x1f);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	//M2?¡éS2 turn  180
	EPD_W21_WriteCMD_M2(0x00);			//panel setting
	EPD_W21_WriteDATA_M2(0x13);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	EPD_W21_WriteCMD_S2(0x00);			//panel setting
	EPD_W21_WriteDATA_S2(0x13);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	
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
	EPD_W21_WriteDATA_ALL(0x21);	//Border KW
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

    return 0;
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
		EPD_W21_WriteDATA_M1(0xff);
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
		EPD_W21_WriteDATA_S1(0xff);
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
		EPD_W21_WriteDATA_M2(0xff);
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
		EPD_W21_WriteDATA_S2(0xff);
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
		EPD_W21_WriteDATA_M1(0xff);
		}
		EPD_W21_WriteCMD_M1(0x13);
		for(column=492;column<984;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_M1(~gImage_1304x984_bw1[row+column*163]);
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
		EPD_W21_WriteDATA_S1(~gImage_1304x984_bw1[row+column*163]);
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
		EPD_W21_WriteDATA_M2(~gImage_1304x984_bw1[row+column*163]);
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
		EPD_W21_WriteDATA_S2(~gImage_1304x984_bw1[row+column*163]);
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
void Epd::DisplayFrame(const unsigned char* frame_buffer)
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
		EPD_W21_WriteDATA_M1(frame_buffer[row+column*163]);
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
		EPD_W21_WriteDATA_S1(frame_buffer[row+column*163]);
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
		EPD_W21_WriteDATA_M2(frame_buffer[row+column*163]);
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
		EPD_W21_WriteDATA_S2(frame_buffer[row+column*163]);
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
///////////////////////////////4Gray///////////////////////////////////
void Epd::Init_4gray(void)
{
	EPD_W21_Init();

	EPD_W21_WriteCMD_M1(0x00);			//panel setting
	EPD_W21_WriteDATA_M1(0x3f);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	EPD_W21_WriteCMD_S1(0x00);			//panel setting
	EPD_W21_WriteDATA_S1(0x3f);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	//M2¡¢S2 turn  180
	EPD_W21_WriteCMD_M2(0x00);			//panel setting
	EPD_W21_WriteDATA_M2(0x33);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	EPD_W21_WriteCMD_S2(0x00);			//panel setting
	EPD_W21_WriteDATA_S2(0x33);		//KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f

	EPD_W21_WriteCMD_M1(0x01);			//POWER SETTING
	EPD_W21_WriteDATA_M1 (0x07);
	EPD_W21_WriteDATA_M1 (0x17);       //VGH=20V,VGL=-20V
	EPD_W21_WriteDATA_M1 (0x3F);		//VDH=15V
	EPD_W21_WriteDATA_M1 (0x3F);		//VDL=-15V
//	EPD_W21_WriteDATA_M1 (0x0d);
	EPD_W21_WriteCMD_M2(0x01);			//POWER SETTING
	EPD_W21_WriteDATA_M2 (0x07);
	EPD_W21_WriteDATA_M2 (0x17);       //VGH=20V,VGL=-20V
	EPD_W21_WriteDATA_M2 (0x3F);		//VDH=15V
	EPD_W21_WriteDATA_M2 (0x3F);		//VDL=-15V
//	EPD_W21_WriteDATA_M2 (0x0d);

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


	EPD_W21_WriteCMD_ALL(0x15);			//
	EPD_W21_WriteDATA_ALL(0x20);		//

	EPD_W21_WriteCMD_ALL(0x30);			//PLL
	EPD_W21_WriteDATA_ALL(0x06);		//50HZ

	EPD_W21_WriteCMD_ALL(0x50);			//
	EPD_W21_WriteDATA_ALL(0x31);		//
	EPD_W21_WriteDATA_ALL(0x07);


	EPD_W21_WriteCMD_ALL(0x60);
	EPD_W21_WriteDATA_ALL(0x22);

	EPD_W21_WriteCMD_M1(0xE0);			//POWER SETTING
	EPD_W21_WriteDATA_M1 (0x01);
	EPD_W21_WriteCMD_M2(0xE0);			//POWER SETTING
	EPD_W21_WriteDATA_M2 (0x01);

	EPD_W21_WriteCMD_ALL(0xE3);
	EPD_W21_WriteDATA_ALL(0x00);


	EPD_W21_WriteCMD_M1(0x82);
	EPD_W21_WriteDATA_M1(0x26);
	EPD_W21_WriteCMD_M2(0x82);
	EPD_W21_WriteDATA_M2(0x26);

	lut11();
}

	
//////////Enter sleep//////////////////////////////


//picture//

void Epd::pic_4bit(void)
{
	unsigned int column,row;
		////////M1 part//////////648*492      //white
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
		EPD_W21_WriteDATA_M1(0xff);
		}
		
		////////S1 part//////////656*492    //gray1
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
		
		////////M2 part//////////656*492   //gray2
		EPD_W21_WriteCMD_M2(0x10);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(0x00);
		}
		EPD_W21_WriteCMD_M2(0x13);
		for(column=0;column<492;column++)
		 for(row=81;row<163;row++)
		{
		EPD_W21_WriteDATA_M2(0xff);
		}
		////////S2 part//////////648*492   //black
		EPD_W21_WriteCMD_S2(0x10);
		for(column=0;column<492;column++)
		 for(row=0;row<81;row++)
		{
		EPD_W21_WriteDATA_S2(0x00);
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


//4 gray
const unsigned char lut_vcom11[] =
{
0x00	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x60	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x00	,0x00	,0x00	,0x01,
0x00	,0x13	,0x0A	,0x01	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00
				
};
//R21
const unsigned char lut_ww11[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x10	,0x14	,0x0A	,0x00	,0x00	,0x01,
0xA0	,0x13	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R22H	r
const unsigned char lut_bw11[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x99	,0x0C	,0x01	,0x03	,0x04	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R23H	w
const unsigned char lut_wb11[] ={
0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x99	,0x0B	,0x04	,0x04	,0x01	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R24H	b
const unsigned char lut_bb11[] ={
0x80	,0x0A	,0x00	,0x00	,0x00	,0x01,
0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
0x20	,0x14	,0x0A	,0x00	,0x00	,0x01,
0x50	,0x13	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//LUT download
void Epd::lut11(void)
{
	unsigned int count;	 
	{
		EPD_W21_WriteCMD_ALL(0x20);							//vcom
		for(count=0;count<44;count++)
			{EPD_W21_WriteDATA_ALL(lut_vcom11[count]);}
		
	EPD_W21_WriteCMD_ALL(0x21);							//red not use
	for(count=0;count<42;count++)
		{EPD_W21_WriteDATA_ALL(lut_ww11[count]);}

		EPD_W21_WriteCMD_ALL(0x22);							//bw r
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA_ALL(lut_bw11[count]);}

		EPD_W21_WriteCMD_ALL(0x23);							//wb w
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA_ALL(lut_wb11[count]);}

		EPD_W21_WriteCMD_ALL(0x24);							//bb b
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA_ALL(lut_bb11[count]);}

		EPD_W21_WriteCMD_ALL(0x25);							//vcom
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA_ALL(lut_ww11[count]);}
	}	         
}

void Epd::DisplayFrame_4gray(void) 
{
    Init_4gray();
    pic_4bit(); //picture
    
}







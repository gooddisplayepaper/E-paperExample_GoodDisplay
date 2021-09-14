#include"Ap_29demo.h"
//IO settings
int BUSY_Pin = 8; 
int RES_Pin = 9; 
int DC_Pin = 10; 
int CS_Pin = 11; 
int SCK_Pin = 12; 
int SDI_Pin = 13; 
#define EPD_W21_MOSI_0  digitalWrite(SDI_Pin,LOW)
#define EPD_W21_MOSI_1  digitalWrite(SDI_Pin,HIGH) 

#define EPD_W21_CLK_0 digitalWrite(SCK_Pin,LOW)
#define EPD_W21_CLK_1 digitalWrite(SCK_Pin,HIGH)

#define EPD_W21_CS_0 digitalWrite(CS_Pin,LOW)
#define EPD_W21_CS_1 digitalWrite(CS_Pin,HIGH)

#define EPD_W21_DC_0  digitalWrite(DC_Pin,LOW)
#define EPD_W21_DC_1  digitalWrite(DC_Pin,HIGH)
#define EPD_W21_RST_0 digitalWrite(RES_Pin,LOW)
#define EPD_W21_RST_1 digitalWrite(RES_Pin,HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)
//960x640///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 120// =960/8
#define MAX_COLUMN_BYTES  640

#define ALLSCREEN_GRAGHBYTES  76800

////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);     
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void EPD_W21_WriteCMD(unsigned char command);
void EPD_W21_WriteDATA(unsigned char command);
//EPD
void Epaper_READBUSY(void);
void Epaper_Spi_WriteByte(unsigned char TxData);
void EPD_W21_WriteCMD(unsigned char cmd);
void EPD_W21_WriteDATA(unsigned char data);

void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update(void);
void EPD_DeepSleep(void);
//Display 
void EPD_WhiteScreen_ALL(const unsigned char *BW_datas);
void EPD_WhiteScreen_ALL_Clean(void);
void setup() {
   pinMode(BUSY_Pin, INPUT); 
   pinMode(RES_Pin, OUTPUT);  
   pinMode(DC_Pin, OUTPUT);    
   pinMode(CS_Pin, OUTPUT);    
   pinMode(SCK_Pin, OUTPUT);    
   pinMode(SDI_Pin, OUTPUT);    
}

//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */
  
void loop() {
  while(1)
  { 
    //Full screen refresh
    EPD_HW_Init(); //Electronic paper initialization
    EPD_WhiteScreen_ALL(gImage_1); //Refresh the picture in full screen
    EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!! 
    delay(3000);   

    //Clean
    EPD_HW_Init(); //Electronic paper initialization
    EPD_WhiteScreen_ALL_Clean();
    EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);
  }
}











///////////////////EXTERNAL FUNCTION////////////////////////////////////////////////////////////////////////
/////////////////////delay//////////////////////////////////////
void driver_delay_us(unsigned int xus)  //1us
{
  for(;xus>1;xus--);
}
void driver_delay_xms(unsigned long xms) //1ms
{  
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
  {
        for(i=0; i<256; i++);
    }
}
void DELAY_S(unsigned int delaytime)     
{
  int i,j,k;
  for(i=0;i<delaytime;i++)
  {
    for(j=0;j<4000;j++)           
    {
      for(k=0;k<222;k++);
                
    }
  }
}
//////////////////////SPI///////////////////////////////////
void SPI_Delay(unsigned char xrate)
{
  unsigned char i;
  while(xrate)
  {
    for(i=0;i<2;i++);
    xrate--;
  }
}

void SPI_Write(unsigned char value)                                    
{                                                           
    unsigned char i;  
   SPI_Delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
       SPI_Delay(1);
       if(value & 0x80)
          EPD_W21_MOSI_1;
        else
          EPD_W21_MOSI_0;   
        value = (value << 1); 
       SPI_Delay(1);
       driver_delay_us(1);
        EPD_W21_CLK_1; 
        SPI_Delay(1);
    }
}

void EPD_W21_WriteCMD(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

/////////////////EPD settings Functions/////////////////////

void EPD_HW_Init(void)
{
    EPD_W21_RST_0;  // Module reset      
    delay(10); //At least 10ms delay 
    EPD_W21_RST_1; 
    delay(10); //At least 10ms delay  
    
    Epaper_READBUSY();
    EPD_W21_WriteCMD(0x12);       //SWRESET
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal
    
    EPD_W21_WriteCMD(0x46);  // Auto Write RAM
    EPD_W21_WriteDATA(0xF7);
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

    EPD_W21_WriteCMD(0x47);  // Auto Write RAM
    EPD_W21_WriteDATA(0xF7);
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

    EPD_W21_WriteCMD(0x0C);  // Soft start setting
    EPD_W21_WriteDATA(0xAE);
    EPD_W21_WriteDATA(0xC7);
    EPD_W21_WriteDATA(0xC3);
    EPD_W21_WriteDATA(0xC0);
    EPD_W21_WriteDATA(0x40);   

    EPD_W21_WriteCMD(0x01);  // Set MUX as 639
    EPD_W21_WriteDATA(0x7F);
    EPD_W21_WriteDATA(0x02);
    EPD_W21_WriteDATA(0x00);

    EPD_W21_WriteCMD(0x11);  // Data entry mode
    EPD_W21_WriteDATA(0x01);
    
    EPD_W21_WriteCMD(0x44);
    EPD_W21_WriteDATA(0x00); // RAM x address start at 0
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0xBF); // RAM x address end at 3BFh -> 959
    EPD_W21_WriteDATA(0x03);
    EPD_W21_WriteCMD(0x45);
    EPD_W21_WriteDATA(0x7F); // RAM y address start at 27Fh;
    EPD_W21_WriteDATA(0x02);
    EPD_W21_WriteDATA(0x00); // RAM y address end at 00h;
    EPD_W21_WriteDATA(0x00);

    EPD_W21_WriteCMD(0x3C); // VBD
    EPD_W21_WriteDATA(0x01); // LUT1, for white

    EPD_W21_WriteCMD(0x18);
    EPD_W21_WriteDATA(0X80);
    EPD_W21_WriteCMD(0x22);
    EPD_W21_WriteDATA(0XB1);  //Load Temperature and waveform setting.
    EPD_W21_WriteCMD(0x20);
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

    EPD_W21_WriteCMD(0x4E); // set RAM x address count to 0;
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteCMD(0x4F); // set RAM y address count to 959;  11D6
    EPD_W21_WriteDATA(0x7F);
    EPD_W21_WriteDATA(0x02);
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(const unsigned char *BW_datas)
{
   long int i;
    EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<28800;i++)
   {               
     EPD_W21_WriteDATA(pgm_read_byte(&BW_datas[i]));
   }
    for(i=28800;i<ALLSCREEN_GRAGHBYTES-28800;i++)
    EPD_W21_WriteDATA(0xff);
   EPD_Update();   
}

/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void)
{   
    EPD_W21_WriteCMD(0x22);
    EPD_W21_WriteDATA(0xC7);//Load LUT from MCU(0x32)
    EPD_W21_WriteCMD(0x20);
    driver_delay_xms(100);          //!!!The delay here is necessary, 200uS at least!!!     
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal


}

void EPD_DeepSleep(void)
{  
  EPD_W21_WriteCMD(0x10); //enter deep sleep
  EPD_W21_WriteDATA(0x01); 
  delay(100);
}
void Epaper_READBUSY(void)
{ 
  while(1)
  {   //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }  
}

void EPD_WhiteScreen_ALL_Clean(void)
{
   long int i;  
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_WriteDATA(0xff);
   }
   EPD_Update();   
}



//////////////////////////////////END//////////////////////////////////////////////////

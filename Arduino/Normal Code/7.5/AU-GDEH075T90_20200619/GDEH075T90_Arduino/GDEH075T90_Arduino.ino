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
//880*528///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 110 // =880/8
#define MAX_COLUMN_BYTES  528

#define ALLSCREEN_GRAGHBYTES  58080

////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);     
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void Epaper_Write_Command(unsigned char command);
void Epaper_Write_Data(unsigned char command);
//EPD
void Epaper_READBUSY(void);
void SPI_Write(u8 TxData);
void Epaper_Write_Command(u8 cmd);
void Epaper_Write_Data(u8 data);

void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update(void);

void EPD_WhiteScreen_Black(void);
void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);
//Display 
void EPD_WhiteScreen_ALL1(const unsigned char *datas);
void EPD_WhiteScreen_ALL(void);

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

    //Full screen refresh
    EPD_HW_Init(); //Electronic paper initialization
    //EPD_WhiteScreen_ALL(); //Refresh the picture in full screen
    EPD_WhiteScreen_Black();  //Show all white
    EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
   delay(3000);
  
  ////////////////////////////////////////////////////////////////////////  
      //Clean
    EPD_HW_Init();//Electronic paper initialization
    EPD_WhiteScreen_White();  //Show all white
    EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
    while(1); 
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

void Epaper_Write_Command(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void Epaper_Write_Data(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

/////////////////EPD settings Functions/////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//SSD1677
void EPD_HW_Init(void)
{
    EPD_W21_RST_0;  // Module reset      
    delay(1); //At least 10ms delay 
    EPD_W21_RST_1; 
    delay(1); //At least 10ms delay  
    
    Epaper_READBUSY();   
    Epaper_Write_Command(0x12);  //SWRESET
    Epaper_READBUSY();   

    Epaper_Write_Command(0x46);  // Auto Write RAM
    Epaper_Write_Data(0xF7);
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

    Epaper_Write_Command(0x47);  // Auto Write RAM
    Epaper_Write_Data(0xF7);
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

    Epaper_Write_Command(0x0C);  // Soft start setting
    Epaper_Write_Data(0xAE);
    Epaper_Write_Data(0xC7);
    Epaper_Write_Data(0xC3);
    Epaper_Write_Data(0xC0);
    Epaper_Write_Data(0x80);   

    Epaper_Write_Command(0x01);  // Set MUX as 527
    Epaper_Write_Data(0x0F);
    Epaper_Write_Data(0x02);
    Epaper_Write_Data(0x00);

    Epaper_Write_Command(0x11);  // Data entry mode
    Epaper_Write_Data(0x01);
    
    Epaper_Write_Command(0x44);
    Epaper_Write_Data(0x00); // RAM x address start at 0
    Epaper_Write_Data(0x00);
    Epaper_Write_Data(0x6F); // RAM x address end at 36Fh -> 879
    Epaper_Write_Data(0x03);
    Epaper_Write_Command(0x45);
    Epaper_Write_Data(0x0F); // RAM y address start at 20Fh;
    Epaper_Write_Data(0x02);
    Epaper_Write_Data(0x00); // RAM y address end at 00h;
    Epaper_Write_Data(0x00);

    Epaper_Write_Command(0x3C); // VBD
    Epaper_Write_Data(0x01); // LUT1, for white

    Epaper_Write_Command(0x18);
    Epaper_Write_Data(0X80);
    Epaper_Write_Command(0x22);
    Epaper_Write_Data(0XB1);  //Load Temperature and waveform setting.
    Epaper_Write_Command(0x20);
    Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

    Epaper_Write_Command(0x4E); // set RAM x address count to 0;
    Epaper_Write_Data(0x00);
    Epaper_Write_Data(0x00);
    Epaper_Write_Command(0x4F); 
    Epaper_Write_Data(0x0F);
    Epaper_Write_Data(0x02);
  
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL1(const unsigned char *datas)
{
   unsigned int i;  
  Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   EPD_Update();   
}
void EPD_WhiteScreen_ALL(void)
{
   unsigned int i,j;  
  Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<528;i++)
   for(j=0;j<880/8;j++)
   { if(i%8==0)              
     Epaper_Write_Data(0xff);
     else
      Epaper_Write_Data(0x00);
   }
   EPD_Update();   
}
/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void)
{
  Epaper_Write_Command(0x22); //Display Update Control
  Epaper_Write_Data(0xF7);   
  Epaper_Write_Command(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();    

}

void EPD_DeepSleep(void)
{  
  Epaper_Write_Command(0x10); //enter deep sleep
  Epaper_Write_Data(0x01); 
  delay(100);
}
void Epaper_READBUSY(void)
{ 
  while(1)
  {   //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }  
}
/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_White(void)

{
   unsigned int i,k;
   Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<880;k++)
  {
    for(i=0;i<66;i++)
    {
      Epaper_Write_Data(0xff);
      }
  }
  EPD_Update();
}
void EPD_WhiteScreen_Black(void)

{
   unsigned int i,k;
   Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<880;k++)
  {
    for(i=0;i<66;i++)
    {
      Epaper_Write_Data(0x00);
      }
  }
  EPD_Update();
}



//////////////////////////////////END//////////////////////////////////////////////////

#include"Ap_29demo.h"
//IO settings
int BUSY_Pin = A14; 
int RES_Pin = A15; 
int DC_Pin = A16; 
int CS_Pin = A17; 
int SCK_Pin = A18; 
int SDI_Pin = A19; 
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
//250*122///////////////////////////////////////
#define  MONO 1
#define  RED  2



#define MAX_LINE_BYTES 16// =128/8
#define MAX_COLUMN_BYTES  250

#define ALLSCREEN_GRAGHBYTES  4000

char vcom=0x8F;    
const unsigned char LUT_bw[]=
{0xA0,  0xA0, 0x54, 0xA2, 0xAA, 0x55,
0x8,  0x1,  0xA0, 0x50, 0x0,  0x0,
0x0,  0x0,  0x0,  0x0,  0x2A, 0xA,
0x32, 0x13, 0x62, 0x42, 0x2F, 0x10,
0x26, 0x3,  0x0,  0x0,  0x0,  0x6,
0x19, 0x0B};        

          
      
const unsigned char LUT_r[]=  
{0x88,  0x44, 0x88, 0x44, 0x20, 0x1,
0x44, 0x44, 0x0,  0x0,  0x0,  0x0,
0x0,  0x0,  0x0,  0x0,  0xC4, 0x18,
0xC3, 0xF,  0xA1, 0x3,  0xA,  0xD,
0x0,  0x0,  0x0,  0x0,  0x0,  0x6,
0x33, 0x0B};  

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
void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update_Red(void);
void EPD_Update_BW(void);

void EPD_WhiteScreen_Black(void);
void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);

//Display 
void EPD_WhiteScreen_ALL(const unsigned char *BW_datas,const unsigned char *R_datas);
void Epaper_Load_Image(const unsigned char *datas,const unsigned char mode);
void Epaper_LUT(const unsigned char * wave_datas);

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
    //Full screen refresh
    EPD_HW_Init(); //Electronic paper initialization
    Epaper_Load_Image(gImage_BW,MONO);
    Epaper_Load_Image(gImage_R,RED);
    EPD_Update_BW();
    EPD_Update_Red();
    EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!! 
    delay(2000);   
    
    //Clean
    EPD_HW_Init(); //Electronic paper initialization
    EPD_WhiteScreen_ALL_Clean();
     EPD_Update_BW();
    EPD_Update_Red();
    EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); 
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
//
void EPD_HW_Init(void)
{
   delay(100);
  EPD_W21_RST_0;  // Module reset      
  delay(10); //At least 10ms delay 
  EPD_W21_RST_1; 
  delay(10); //At least 10ms delay  
    
  Epaper_READBUSY();   
  Epaper_Write_Command(0x12);  //SWRESET
  Epaper_READBUSY();   
    
  Epaper_Write_Command(0x01); //Driver output control      
  Epaper_Write_Data(0xF9);
  Epaper_Write_Data(0x01);

  Epaper_Write_Command(0x11); //data entry mode       
  Epaper_Write_Data(0x03);

  Epaper_Write_Command(0x44); //set Ram-X address start/end position   
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x0F);    //0x0F-->(15+1)*8=128

  Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
  Epaper_Write_Data(0x00);   //0xF9-->(249+1)=250
  Epaper_Write_Data(0xf9);
  
  
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(const unsigned char *BW_datas,const unsigned char *R_datas)
{
   unsigned int i;  
   unsigned int tempOriginal;  
   unsigned int tempcol=0;  
   unsigned int templine=0;  
   
   Epaper_Write_Command(0x4E);
   Epaper_Write_Data(0x00); 
   Epaper_Write_Command(0x4F);
   Epaper_Write_Data(0x00); 
   
   
  Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*(BW_datas+templine*250+tempcol));
     templine++;
   }
  Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
    
     Epaper_Write_Data(*(R_datas+templine*250+tempcol));
     templine++;
   }
   if(templine>=16)
     {
       tempcol++;
       templine=0;
     }   

}

void EPD_WhiteScreen_ALL_Clean(void)
{
   unsigned int i;  
   unsigned int j;
   Epaper_Write_Command(0x4E);     
    Epaper_Write_Data(0x00);
 
    Epaper_Write_Command(0x4F);       
    Epaper_Write_Data(0x00);
  
    Epaper_READBUSY();
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1) 
    for(i=0;i<250;i++)
   {
     for(j=0;j<16;j++)
     {
      Epaper_Write_Data(0xff);
     }
   }
   
    Epaper_Write_Command(0x4E);     
    Epaper_Write_Data(0x00);
  
    Epaper_Write_Command(0x4F);       
    Epaper_Write_Data(0x00);
  
    Epaper_READBUSY();
    Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1) 
    for(i=0;i<250;i++)
   {
     for(j=0;j<16;j++)
     {
      Epaper_Write_Data(0x00);
     }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update_Red(void)
{

  Epaper_Write_Command(0x03);       
      Epaper_Write_Data(0x02);
      Epaper_Write_Data(0x0A);
      Epaper_Write_Command(0x04);       
      Epaper_Write_Data(LUT_r[30]);

      Epaper_Write_Command(0x05);       
      Epaper_Write_Data(0xC0);

      Epaper_Write_Command(0x2C);       
      Epaper_Write_Data( vcom);

      Epaper_Write_Command(0x3C); 
      Epaper_Write_Data(0x71);
      Epaper_Write_Command(0x3A);       
      Epaper_Write_Data(LUT_r[29]);

      Epaper_Write_Command(0x3B);       
      Epaper_Write_Data(LUT_r[31]);

      Epaper_LUT(LUT_r);

      Epaper_Write_Command(0x75);       
      Epaper_Write_Data(0x00);
      Epaper_Write_Data(0x80);
      Epaper_Write_Data(0x00);
      
  Epaper_Write_Command(0x22); //Display Update Control
  Epaper_Write_Data(0xC7);   
  Epaper_Write_Command(0x20);  //Activate Display Update Sequence
  Epaper_READBUSY(); 
  delay(100);  

}


void EPD_Update_BW(void)
{

  Epaper_Write_Command(0x03);       
      Epaper_Write_Data(0x10);
      Epaper_Write_Data(0x0A);
      Epaper_Write_Command(0x04);       
      Epaper_Write_Data(LUT_bw[30]);

      Epaper_Write_Command(0x05);       
      Epaper_Write_Data(0x00);

      Epaper_Write_Command(0x2C);       
      Epaper_Write_Data( vcom);

      Epaper_Write_Command(0x3C); 
      Epaper_Write_Data(0x71);
      Epaper_Write_Command(0x3A);       
      Epaper_Write_Data(LUT_bw[29]);

      Epaper_Write_Command(0x3B);       
      Epaper_Write_Data(LUT_bw[31]);

      Epaper_LUT(LUT_bw);

      Epaper_Write_Command(0x75);       
      Epaper_Write_Data(0x00);
      Epaper_Write_Data(0x00);
      Epaper_Write_Data(0x00);
      
  Epaper_Write_Command(0x22); //Display Update Control
  Epaper_Write_Data(0xC7);   
  Epaper_Write_Command(0x20);  //Activate Display Update Sequence
  Epaper_READBUSY(); 
  delay(100);  

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
     delay(1);
  }  
  delay(1);
}


void Epaper_Load_Image(const unsigned char *datas,const unsigned char mode)
{
  unsigned int i; 
  unsigned int tempOriginal;      
  unsigned int tempcol=0;
  unsigned int templine=0;

    Epaper_Write_Command(0x4E);     
    Epaper_Write_Data(0x00);

  
    Epaper_Write_Command(0x4F);       
    Epaper_Write_Data(0x00);
  
    Epaper_READBUSY();
 if(mode==MONO)
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  if(mode==RED)
    Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
  
  for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {          
     tempOriginal=*(datas+templine*MAX_COLUMN_BYTES+tempcol);
     templine++;
     if(templine>=MAX_LINE_BYTES)
     {
       tempcol++;
       templine=0;
     }     
     Epaper_Write_Data(tempOriginal);
   } 

}

void Epaper_LUT(const unsigned char * wave_datas)
{        
  unsigned int count;
  Epaper_Write_Command(0x32);//write LUT by MCU
  for(count=0;count<29;count++) Epaper_Write_Data(*wave_datas++); 
  Epaper_READBUSY();
 
}

//////////////////////////////////END//////////////////////////////////////////////////

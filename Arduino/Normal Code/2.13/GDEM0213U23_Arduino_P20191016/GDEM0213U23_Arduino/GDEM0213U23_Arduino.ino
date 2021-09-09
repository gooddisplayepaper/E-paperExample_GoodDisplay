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
//152*152///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3
#define  MONO 1
#define  RED  2

//250x122
#define MAX_LINE_BYTES    16
#define MAX_COLUMN_BYTES  250
#define ALLSCREEN_BYTES   4000

////////FUNCTION//////
void delay_us(unsigned int xus);
void delay_xms(unsigned long xms);
void delay_S(unsigned int delaytime);     
void SPI_delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void Epaper_Write_Command(unsigned char command);
void Epaper_Write_Data(unsigned char command);
//EPD
void EpaperIO_Init(void);
void Epaper_READBUSY(void);
void Epaper_Write_Command(u8 cmd);
void Epaper_Write_Data(u8 data);
void Epaper_Init(void);
void LUT_Written_by_MCU(u8 mode);
void Epaper_Load_Image(u8 *datas,u32 num,u8 mode);
void Epaper_Update(void);
void Epaper_DeepSleep(void);
void setup() {
   pinMode(BUSY_Pin, INPUT); 
   pinMode(RES_Pin, OUTPUT);  
   pinMode(DC_Pin, OUTPUT);    
   pinMode(CS_Pin, OUTPUT);    
   pinMode(SCK_Pin, OUTPUT);    
   pinMode(SDI_Pin, OUTPUT);    
}
////////Partial refresh schematic////////////////

/////Y/// (0,0)        /---/(x,y)
          //                 /---/
          //                /---/  
          //x
          //
          //
//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */
 
void loop() {
  while(1)
  { 
    //PICTURE1      
    
     Epaper_Init(); //Electronic paper initialization
     Epaper_Load_Image((u8*)gImage_black1,ALLSCREEN_BYTES,MONO);//Display black and white pictures
     Epaper_Load_Image((u8*)gImage_red1,ALLSCREEN_BYTES,RED);//Display red and white pictures
     LUT_Written_by_MCU(MONO); //Load black and white waveform files
     Epaper_Update(); //Display update
     LUT_Written_by_MCU(RED);//Load red and white wave files
     Epaper_Update(); //Display update
     Epaper_DeepSleep();//Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
     delay(500);
     
    //CLEAN 
     Epaper_Init();
     Display_All_White();//All white
     LUT_Written_by_MCU(MONO);// Load black and white waveform files
     Epaper_Update();//Display update
     LUT_Written_by_MCU(RED);//Load red and white wave files
     Epaper_Update();//Display update
     Epaper_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!  
     delay(500);

    while(1);

  }
}











///////////////////EXTERNAL FUNCTION////////////////////////////////////////////////////////////////////////
/////////////////////delay//////////////////////////////////////
void delay_us(unsigned int xus)  //1us
{
  for(;xus>1;xus--);
}
void delay_xms(unsigned long xms) //1ms
{  
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
  {
        for(i=0; i<256; i++);
    }
}
void delay_S(unsigned int delaytime)     
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
void SPI_delay(unsigned char xrate)
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
   SPI_delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
       SPI_delay(1);
       if(value & 0x80)
          EPD_W21_MOSI_1;
        else
          EPD_W21_MOSI_0;   
        value = (value << 1); 
       SPI_delay(1);
       delay_us(1);
        EPD_W21_CLK_1; 
        SPI_delay(1);
    }
}

void Epaper_Write_Command(unsigned char command)
{
  SPI_delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void Epaper_Write_Data(unsigned char command)
{
  SPI_delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

/////////////////EPD settings Functions/////////////////////

/////////////////////////////////////LUT//////////////////////////////////////////////
const unsigned char LUT_bw[] PROGMEM=
{0xA0,  0xA0, 0x54, 0xA2, 0xAA, 0x55,
0x8,  0x1,  0xA0, 0x50, 0x0,  0x0,
0x0,  0x0,  0x0,  0x0,  0x2A, 0xA,
0x32, 0x13, 0x62, 0x42, 0x2F, 0x10,
0x26, 0x3,  0x0,  0x0,  0x0,  0x6,
0x19, 0x0B};        

          
      
const unsigned char LUT_r[] PROGMEM=  
{0x88,  0x44, 0x88, 0x44, 0x20, 0x1,
0x44, 0x44, 0x0,  0x0,  0x0,  0x0,
0x0,  0x0,  0x0,  0x0,  0xC4, 0x18,
0xC3, 0xF,  0xA1, 0x3,  0xA,  0xD,
0x0,  0x0,  0x0,  0x0,  0x0,  0x6,
0x33, 0x0B};        
void Epaper_LUT(u8 * wave_data)
{        
  u8 count;
  Epaper_Write_Command(0x32);//write LUT by MCU
  for(count=0;count<29;count++)  Epaper_Write_Data(pgm_read_byte(&wave_data[count]));
  Epaper_READBUSY();
 
}

/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void Epaper_Init(void)
{
  EPD_W21_RST_0;  // Module reset      
  delay(1); //At least 10ms delay 
  EPD_W21_RST_1; 
  delay(1); //At least 10ms delay 

  Epaper_READBUSY();
  Epaper_Write_Command(0x12); // soft reset
  Epaper_READBUSY();

  Epaper_Write_Command(0x01); //Driver output control      
   Epaper_Write_Data(0xf9);
   Epaper_Write_Data(0x01);

  Epaper_Write_Command(0x11); //data entry mode       
   Epaper_Write_Data(0x03);
  
  Epaper_Write_Command(0x44); //set Ram-X address start/end position   
   Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x0F);    //0x0F-->(15+1)*8=128

  Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
   Epaper_Write_Data(0x00);   //0xD3-->(211+1)=212
  Epaper_Write_Data(0xF9);
  
}

void LUT_Written_by_MCU(u8 mode)
{

  if(mode==MONO)        //2.13a
  {

      Epaper_Write_Command(0x03);       
      Epaper_Write_Data(0x10);
      Epaper_Write_Data(0x0A);
      Epaper_Write_Command(0x04);       
      Epaper_Write_Data(pgm_read_byte(&LUT_bw[30]));

      Epaper_Write_Command(0x05);       
      Epaper_Write_Data(0x00);

      Epaper_Write_Command(0x2C);       
      Epaper_Write_Data( 0x8F);

      Epaper_Write_Command(0x3C); 
      Epaper_Write_Data(0x71);
      Epaper_Write_Command(0x3A);       
      Epaper_Write_Data(pgm_read_byte(&LUT_bw[29]));

      Epaper_Write_Command(0x3B);       
      Epaper_Write_Data(pgm_read_byte(&LUT_bw[31]));

      Epaper_LUT((u8*)LUT_bw);


      Epaper_Write_Command(0x75);       
      Epaper_Write_Data(0x00);
      Epaper_Write_Data(0x00);
      Epaper_Write_Data(0x00);
    
  }
  if(mode==RED)        //2.13r
  {

  
      Epaper_Write_Command(0x03);       
      Epaper_Write_Data(0x02);
      Epaper_Write_Data(0x0A);
      Epaper_Write_Command(0x04);       
      Epaper_Write_Data(pgm_read_byte(&LUT_r[30]));

      Epaper_Write_Command(0x05);       
      Epaper_Write_Data(0xC0);

//      Epaper_Write_Command(0x05);       
//      Epaper_Write_Data(0x00);

      Epaper_Write_Command(0x2C);       
      Epaper_Write_Data( 0x8F);

      Epaper_Write_Command(0x3C); 
      Epaper_Write_Data(0x71);
      Epaper_Write_Command(0x3A);       
      Epaper_Write_Data(pgm_read_byte(&LUT_r[29]));

      Epaper_Write_Command(0x3B);       
      Epaper_Write_Data(pgm_read_byte(&LUT_r[31]));

      Epaper_LUT((u8*)LUT_r);
      Epaper_Write_Command(0x75);       
      Epaper_Write_Data(0x00);
      Epaper_Write_Data(0x80);
      Epaper_Write_Data(0x00);
    
  }
}
  
void Epaper_Load_Image(u8 *datas,u32 num,u8 mode)
{
  u32 i; 

    Epaper_Write_Command(0x4E);     
    Epaper_Write_Data(0x00);

    Epaper_Write_Command(0x4F);       
    Epaper_Write_Data(0x00);
  
    Epaper_READBUSY();
 if(mode==MONO)
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  if(mode==RED)
    Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
  
  for(i=0;i<num;i++)
   {          
   
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   } 

}
void Epaper_DeepSleep(void)
{
   Epaper_Write_Command(0x10);
   Epaper_Write_Data(0x01);   
   delay(100);   
}
void Epaper_Update(void)
{

    Epaper_Write_Command(0x22); //Display Update Control 
    Epaper_Write_Data(0xC7);          
    Epaper_Write_Command(0x20);//Activate Display Update Sequence
    Epaper_READBUSY();
    delay(100);  
}
void Epaper_READBUSY(void)
{ 
  while(1)
  {   //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
     delay_us(5) ;
  }  
   delay_us(100) ;
}



void Display_All_White(void)
{
  u32 i,j; 


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
      Epaper_Write_Data(0xFF);
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


//////////////////////////////////END//////////////////////////////////////////////////

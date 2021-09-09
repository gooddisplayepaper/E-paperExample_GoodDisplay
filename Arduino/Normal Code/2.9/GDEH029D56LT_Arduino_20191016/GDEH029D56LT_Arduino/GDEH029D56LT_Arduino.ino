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
//296*128///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 16// =128/8
#define MAX_COLUMN_BYTES  296

#define ALLSCREEN_GRAGHBYTES  4736

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
void EPD_Part_Init(void); //Local refresh initialization

void EPD_Part_Update(void); 
void EPD_Update(void);

void EPD_WhiteScreen_Black(void);
void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);
//Display 
void EPD_WhiteScreen_ALL(void);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);

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
    unsigned char fen_L,fen_H,miao_L,miao_H; 

    EPD_HW_Init(); //Electronic paper initialization
    EPD_WhiteScreen_ALL(); //Full screen refresh picture 1
    delay(2000);
    
//////////////////////Partial refresh digital presentation//////////////////////////////////////  
    EPD_HW_Init(); //Electronic paper initialization
    EPD_SetRAMValue_BaseMap(gImage_basemap);  //Partial refresh background color
    EPD_Part_Init();//Local refresh initialization
    delay(100);
    EPD_Dis_Part(0,32,gImage_num1,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num2,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num3,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num4,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num5,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num6,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num7,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num8,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num9,32,32); //x,y,DATA,resolution 32*32
   delay(2000);   
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

/////////////////////////////////////LUT//////////////////////////////////////////////
const unsigned char LUT_DATA[] PROGMEM= {   
0x80,  0xA5, 0x10, 0x0,  0x0,  0x0,  0x0,
0x10, 0xA5, 0x80, 0x0,  0x0,  0x0,  0x0,
0x80, 0xA5, 0x10, 0x0,  0x0,  0x0,  0x0,
0x10, 0xA5, 0x80, 0x0,  0x0,  0x0,  0x0,
0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
0x6,  0x8,  0x0,  0x0,  0x2,    
0xC,  0x0,  0xC,  0x0,  0x5,    
0x8,  0x6,  0x0,  0x0,  0x2,    
0x0,  0x0,  0x0,  0x0,  0x0,    
0x0,  0x0,  0x0,  0x0,  0x0,    
0x0,  0x0,  0x0,  0x0,  0x0,    
0x0,  0x0,  0x0,  0x0,  0x0,    
0x17, 0x41, 0x0,  0x32,     
0x1,  0x8}; 
const unsigned char LUT_DATA_part[] PROGMEM={ 
0X00,0x40,0x00,0x00,0x00,0x00,0x00,  // L0 0-6 ABCD    
0X80,0x80,0x00,0x00,0x00,0x00,0x00, // L1 0-6 ABCD    
0X40,0x40,0x00,0x00,0x00,0x00,0x00, // L2 0-6 ABCD    
0X00,0x80,0x00,0x00,0x00,0x00,0x00, // L3 0-6 ABCD    
0X00,0x00,0x00,0x00,0x00,0x00,0x00, // VCOM 0-6 ABCD    
      
0x14,0x00,0x00,0x00,0x02,//0A 0B 0C 0D R      
0x04,0x00,0x00,0x00,0x00,//1A 0B 0C 0D R      
0x00,0x00,0x00,0x00,0x00,//2A 0B 0C 0D R      
0x00,0x00,0x00,0x00,0x00,//3A 0B 0C 0D R      
0x00,0x00,0x00,0x00,0x00,//4A 0B 0C 0D R      
0x00,0x00,0x00,0x00,0x00,//5A 0B 0C 0D R      
0x00,0x00,0x00,0x00,0x00,//6A 0B 0C 0D R

0x17, 0x41, 0x0,  0x32, 0x25, 0x06  
};         
void EPD_select_LUT(const unsigned char * wave_data)
{        
     unsigned char count;
     Epaper_Write_Command(0x32);
   for(count=0;count<70;count++)
  Epaper_Write_Data(pgm_read_byte(&wave_data[count]));

} 

/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void EPD_HW_Init(void)
{
    EPD_W21_RST_0;  // Module reset      
    delay(1); //At least 10ms delay 
    EPD_W21_RST_1; 
    delay(1); //At least 10ms delay  
    
    Epaper_READBUSY();
    Epaper_Write_Command(0x12); // soft reset
    Epaper_READBUSY();
    
    Epaper_Write_Command(0x74);       // 
    Epaper_Write_Data(0x54);    //
    
    Epaper_Write_Command(0x7E);       //   
    Epaper_Write_Data(0x3B);
    
    Epaper_Write_Command(0x01);      //    
    Epaper_Write_Data(0x27);//
    Epaper_Write_Data(0x01);//
    Epaper_Write_Data(0x01);//
    
    Epaper_Write_Command(0x11);      //    
    Epaper_Write_Data(0x03);//
    
    Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
    Epaper_Write_Data(0x00);    // RAM x address start at 00h;
    Epaper_Write_Data(0x0f);    // RAM x address end at 0fh(15+1)*8->128 
    
    Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
    Epaper_Write_Data(0x00);    // RAM y address start at 0127h;
    Epaper_Write_Data(0x00);    // RAM y address start at 0127h;
    Epaper_Write_Data(0x27);    // RAM y address end at 00h;
    Epaper_Write_Data(0x01);    // ????=0    
    
    
    Epaper_Write_Command(0x3C);   //BorderWavefrom     
    Epaper_Write_Data(0x03);
    
    
    
    
    Epaper_Write_Command(0x03);       
    Epaper_Write_Data(LUT_DATA[70]);
    
    Epaper_Write_Command(0x04);       
    Epaper_Write_Data(LUT_DATA[71]);    
    Epaper_Write_Data(LUT_DATA[72]);    
    Epaper_Write_Data(LUT_DATA[73]);    
    
    Epaper_Write_Command(0x2C);     // 
    Epaper_Write_Data(0x28);    //
    
    Epaper_Write_Command(0x3A);     // 
    Epaper_Write_Data(LUT_DATA[74]);    
    Epaper_Write_Command(0x3B);     // 
    Epaper_Write_Data(LUT_DATA[75]);   
    
    EPD_select_LUT((unsigned char *)LUT_DATA);
    
    
    Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
    Epaper_Write_Data(0x00);
    Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
    Epaper_Write_Data(0x00);
    Epaper_Write_Data(0x00);
  
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(void)
{
   unsigned int i;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(pgm_read_byte(&gImage_1[i]));
   }
   EPD_Update();   
}

/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void)
{   
  Epaper_Write_Command(0x22);  //Display Update Control
  Epaper_Write_Data(0xC7);   
  Epaper_Write_Command(0x20);  //Activate Display Update Sequence
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
///////////////////////////Part update//////////////////////////////////////////////
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
  unsigned int i;   
  const unsigned char  *datas_flag;   
  datas_flag=datas;
  Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   datas=datas_flag;
  Epaper_Write_Command(0x26);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   EPD_Update();   
}

void EPD_Part_Init(void)
{
  Epaper_Write_Command(0x2C);     //VCOM Voltage
  Epaper_Write_Data(0x26);  
  
  Epaper_READBUSY();  
  EPD_select_LUT(( unsigned char *)LUT_DATA_part);
  Epaper_Write_Command(0x37); 
  Epaper_Write_Data(0x00);  
  Epaper_Write_Data(0x00);  
  Epaper_Write_Data(0x00);  
  Epaper_Write_Data(0x00);  
  Epaper_Write_Data(0x40);  
  Epaper_Write_Data(0x00);  
  Epaper_Write_Data(0x00);   

  Epaper_Write_Command(0x22); 
  Epaper_Write_Data(0xC0);   
  Epaper_Write_Command(0x20); 
  Epaper_READBUSY();  
  
  Epaper_Write_Command(0x3C); //BorderWavefrom
  Epaper_Write_Data(0x01);

}
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;  
  unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
  x_start=x_start/8;//
  x_end=x_start+PART_LINE/8-1; 
  
  y_start=296-y_start;
  y_start1=0;
  y_start2=y_start;
  if(y_start>=256)
  {
    y_start1=y_start2/256;
    y_start2=y_start2%256;
  }
  y_end1=0;
  y_end2=y_start+PART_COLUMN-1;
  if(y_end2>=256)
  {
    y_end1=y_end2/256;
    y_end2=y_end2%256;    
  }   
  
  Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
  Epaper_Write_Data(x_start);    // RAM x address start at 00h;
  Epaper_Write_Data(x_end);    // RAM x address end at 0fh(15+1)*8->128 
  Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
  Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
  Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
  Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
  Epaper_Write_Data(y_end1);    // ????=0 


  Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
  Epaper_Write_Data(x_start); 
  Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
  Epaper_Write_Data(y_start2);
  Epaper_Write_Data(y_start1);
  
  
   Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   } 
   EPD_Part_Update();

}

void EPD_Part_Update(void)
{
  Epaper_Write_Command(0x22);  //Display Update Control
  Epaper_Write_Data(0x0C);   
  Epaper_Write_Command(0x20);  //Activate Display Update Sequence
  Epaper_READBUSY();    
}


/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_Black(void)

{
   unsigned int i,k;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<296;k++)
  {
    for(i=0;i<16;i++)
    {
      Epaper_Write_Data(0x00);
      }
  }
    EPD_Update();
}

void EPD_WhiteScreen_White(void)

{
   unsigned int i,k;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<296;k++)
  {
    for(i=0;i<16;i++)
    {
      Epaper_Write_Data(0xff);
      }
  }
  EPD_Update();
}



//////////////////////////////////END//////////////////////////////////////////////////

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
////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);     
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void EPD_display_Clean(void);

//4 Gray

void EPD_init_4Gray(void);//EPD init 4 Gray
void EPD_display_4Gray(void);
void pic_display_4bit(void);
void lut(void);

unsigned char HRES_byte1,HRES_byte2,VRES_byte1,VRES_byte2;

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

    //Clear screen (OTP)
    EPD_init(); //EPD init
    EPD_display_Clean(); //Clear screen
    EPD_refresh();//EPD_refresh   
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!

    //4 gray picture
    EPD_init_4Gray(); //EPD init 4 Gray
    EPD_display_4Gray(); //pic1
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000);
    

    //Clear screen (OTP)
    EPD_init(); //EPD init
    EPD_display_Clean(); //Clear screen
    EPD_refresh();//EPD_refresh   
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!

    while(1); 
  }


}
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
void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(100); //At least 10ms
  EPD_W21_RST_1;
  delay(100);  
}

void EPD_init(void)
{
    EPD_W21_Init(); //Electronic paper IC reset
  
    EPD_W21_WriteCMD(0x06);         //boost soft start
    EPD_W21_WriteDATA (0x07);   //A
    EPD_W21_WriteDATA (0x07);   //B
    EPD_W21_WriteDATA (0x17);   //C       

    EPD_W21_WriteCMD(0x04);  //Power on
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

    EPD_W21_WriteCMD(0x00);     //panel setting
    EPD_W21_WriteDATA(0x1f);    //LUT from OTP,128x296
    
  
    EPD_W21_WriteCMD(0x16);
    EPD_W21_WriteDATA(0x00);        //KW-BF   KWR-AF  BWROTP 0f 
  
    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x60);
    EPD_W21_WriteDATA(0xa5);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x73);
    EPD_W21_WriteDATA (0x23);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x7C);
    EPD_W21_WriteDATA(0x00);
    
    EPD_W21_WriteCMD(0X50);
    EPD_W21_WriteDATA(0x97);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}
void EPD_init_4Gray(void)
{
    HRES_byte1=0x00;      //176
    HRES_byte2=0xb0;            
    VRES_byte1=0x01;      //264
    VRES_byte2=0x08;
    EPD_W21_Init(); //Electronic paper IC reset
    EPD_W21_WriteCMD(0x01);     //POWER SETTING
    EPD_W21_WriteDATA (0x03);
    EPD_W21_WriteDATA (0x00);    
    EPD_W21_WriteDATA (0x2b);                              
    EPD_W21_WriteDATA (0x2b);   


    EPD_W21_WriteCMD(0x06);         //booster soft start
    EPD_W21_WriteDATA (0x07);   //A
    EPD_W21_WriteDATA (0x07);   //B
    EPD_W21_WriteDATA (0x17);   //C 
  
    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x60);
    EPD_W21_WriteDATA (0xA5);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x89);
    EPD_W21_WriteDATA (0xA5);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x90);
    EPD_W21_WriteDATA (0x00);
    
    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x93);
    EPD_W21_WriteDATA (0x2A);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0xa0);
    EPD_W21_WriteDATA (0xa5);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0xa1);
    EPD_W21_WriteDATA (0x00);

    EPD_W21_WriteCMD(0xF8);         //boost??
    EPD_W21_WriteDATA (0x73);
    EPD_W21_WriteDATA (0x41);

    EPD_W21_WriteCMD(0x16);
    EPD_W21_WriteDATA(0x00);  
    
    EPD_W21_WriteCMD(0x04);  //Power on
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
    
    EPD_W21_WriteCMD(0x00);     //panel setting
    EPD_W21_WriteDATA(0xbf);    //KW-BF   KWR-AF  BWROTP 0f
    
    EPD_W21_WriteCMD(0x30);     //PLL setting
    EPD_W21_WriteDATA (0x90);       //100hz 
    
    EPD_W21_WriteCMD(0x61);     //resolution setting
    EPD_W21_WriteDATA (HRES_byte1);   //176
    EPD_W21_WriteDATA (HRES_byte2);        
    EPD_W21_WriteDATA (VRES_byte1);   //264
    EPD_W21_WriteDATA (VRES_byte2);

    EPD_W21_WriteCMD(0x82);     //vcom_DC setting
    EPD_W21_WriteDATA (0x12);

    EPD_W21_WriteCMD(0X50);     //VCOM AND DATA INTERVAL SETTING      
    EPD_W21_WriteDATA(0x97);


  }

//4 grayscale demo function
/********Color display description
      white  gray1  gray2  black
0x10|  01     01     00     00
0x13|  01     00     01     00
                                   ****************/
void pic_display_4bit (void)
{
  u32 i,j;
  u8 temp1,temp2,temp3;

    //old  data
    EPD_W21_WriteCMD(0x10);        

    for(i=0;i<5808;i++)                //5808*4  296*128
    { 
      temp3=0;
      for(j=0;j<4;j++)  
      {
        temp1 = pgm_read_byte(&gImage_1[i*4+j]);
        temp2 = temp1&0xF0 ;
        if(temp2 == 0xF0)
          temp3 |= 0x01;//white
        else if(temp2 == 0x00)
          temp3 |= 0x00;  //black
        else if((temp2>0xA0)&&(temp2<0xF0)) 
          temp3 |= 0x01;  //gray1
        else 
          temp3 |= 0x00; //gray2
        temp3 <<= 1;  
        temp1 <<= 4;
        temp2 = temp1&0xF0 ;
        if(temp2 == 0xF0)  //white
          temp3 |= 0x01;
        else if(temp2 == 0x00) //black
          temp3 |= 0x00;
        else if((temp2>0xA0)&&(temp2<0xF0))
          temp3 |= 0x01; //gray1
        else    
            temp3 |= 0x00;  //gray2 
        if(j!=3)          
        temp3 <<= 1;  
        
      
     }  
        EPD_W21_WriteDATA(temp3);     
    }
    //new  data
    EPD_W21_WriteCMD(0x13);        

    for(i=0;i<5808;i++)                //5808*4   152*152
    { 
      temp3=0;
      for(j=0;j<4;j++)  
      {
        temp1 = pgm_read_byte(&gImage_1[i*4+j]);
        temp2 = temp1&0xF0 ;
        if(temp2 == 0xF0)
          temp3 |= 0x01;//white
        else if(temp2 == 0x00)
          temp3 |= 0x00;  //black
        else if((temp2>0xA0)&&(temp2<0xF0)) 
          temp3 |= 0x00;  //gray1
        else 
          temp3 |= 0x01; //gray2
        temp3 <<= 1;  
        temp1 <<= 4;
        temp2 = temp1&0xF0 ;
        if(temp2 == 0xF0)  //white
          temp3 |= 0x01;
        else if(temp2 == 0x00) //black
          temp3 |= 0x00;
        else if((temp2>0xA0)&&(temp2<0xF0)) 
          temp3 |= 0x00;//gray1
        else    
            temp3 |= 0x01;  //gray2
        if(j!=3)        
        temp3 <<= 1;        
      
     }  
        EPD_W21_WriteDATA(temp3);     
    }
}
/***************************full display function*************************************/
void EPD_display_4Gray(void)
{

    
    pic_display_4bit(); //picture
    lut(); //Power settings
    EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
    driver_delay_xms(100);      //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
}
void EPD_refresh(void)
{
    EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
    driver_delay_xms(100);          //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
} 
void EPD_sleep(void)
{
    EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING  
    EPD_W21_WriteDATA(0xf7);
       
    EPD_W21_WriteCMD(0X02);   //power off
    lcd_chkstatus();
    EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);
}


void EPD_display_Clean(void)
{
    unsigned int i;
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<5808;i++)       
  {
    EPD_W21_WriteDATA(0xff);
  }
  
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<5808;i++)       
  {
    EPD_W21_WriteDATA(0xff);
  }
}
void lcd_chkstatus(void)
{
  while(isEPD_W21_BUSY==0);   
  driver_delay_xms(200);                         
}


//LUT download
void lut(void)
{
  unsigned int count;  
  {
    EPD_W21_WriteCMD(0x20);             //vcom
    for(count=0;count<44;count++)
      {EPD_W21_WriteDATA(pgm_read_byte(&lut_vcom[count]));}
    
  EPD_W21_WriteCMD(0x21);             //red not use
  for(count=0;count<42;count++)
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_ww[count]));}

    EPD_W21_WriteCMD(0x22);             //bw r
    for(count=0;count<42;count++)
      {EPD_W21_WriteDATA(pgm_read_byte(&lut_bw[count]));}

    EPD_W21_WriteCMD(0x23);             //wb w
    for(count=0;count<42;count++)
      {EPD_W21_WriteDATA(pgm_read_byte(&lut_wb[count]));}

    EPD_W21_WriteCMD(0x24);             //bb b
    for(count=0;count<42;count++)
      {EPD_W21_WriteDATA(pgm_read_byte(&lut_bb[count]));}

    EPD_W21_WriteCMD(0x25);             //vcom
    for(count=0;count<42;count++)
      {EPD_W21_WriteDATA(pgm_read_byte(&lut_ww[count]));}
  }          
}

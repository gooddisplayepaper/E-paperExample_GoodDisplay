#include"Ap_29demo.h"
//IO settings
int BUSY_Pin = D0; 
int RES_Pin = D1; 
int DC_Pin = D2; 
int CS_Pin = D5; 
int SCK_Pin = D6; 
int SDI_Pin = D7; 

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
void EPD_display_init_Full(void);//EPD init Full
void EPD_display_init_Part(void);//EPD init Part
void full_display(void pic_display(void)); //full  display
void partial_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end ,void partial_old(void),void partial_new(void)); //partial display
void Full_lut_bw(void);
void Part_lut_bw(void);
void lcd_chkstatus(void);
void EPD_sleep(void); //Enter deep sleep mode
// full display
void pic_display_white(void);
void pic_display1(void);
void pic_display2(void);
//partial display
void partial_full00(void);
void partial_full01(void);
void partial_full02(void);
void partial_full03(void);
void partial_full04(void);
void partial_full05(void);
void partial_full_basemap(void);
void partial00(void);
void partial01(void);
void partial02(void);
void partial03(void);
void partial04(void);
void partial05(void);
void partial06(void);
void partial07(void);
void partial08(void);
void partial09(void);

void Sys_run(void)
{
   ESP.wdtFeed(); //Feed dog to prevent system reset
  }

void LED_run(void)
{
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  delay(500);
  }
void setup() {
  
   pinMode(BUSY_Pin, INPUT); 
   pinMode(RES_Pin, OUTPUT);  
   pinMode(DC_Pin, OUTPUT);    
   pinMode(CS_Pin, OUTPUT);    
   pinMode(SCK_Pin, OUTPUT);    
   pinMode(SDI_Pin, OUTPUT);    

   pinMode(LED_BUILTIN, OUTPUT); //ESP8266 Status light 
   ESP.wdtDisable();//Turn off the software watchdog
}
//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */

void loop() {

      EPD_display_init_Full(); //EPD init Full
      full_display(pic_display1); //pic1
       delay(3000); 
      /******screen clear*****/
      EPD_display_init_Full(); //EPD init Full
      full_display(pic_display_white); //pic_white
       delay(1000); 
      /*********partial display 0~9*********/
      EPD_display_init_Part(); //EPD init Part
      partial_display(0,80,0,128,partial_full00, partial_full_basemap); //partial full  basemap display   
       delay(1000);  
      partial_display(0,32,0,64, partial00, partial01); //partial display 0 1                             
      partial_display(0,32,0,64, partial01, partial02); //partial display 1 2                         //////////////(x,y)   ----Y----
      partial_display(0,32,0,64, partial02, partial03); //partial display 2 3                        /     /      /                   X|
      partial_display(0,32,0,64, partial03, partial04); //partial display 3 4                       /W    /      /                     |                  
      partial_display(0,32,0,64, partial04, partial05); //partial display 4 5                      ///// L //////                      |
      partial_display(0,32,0,64, partial05, partial06); //partial display 5 6                    
      partial_display(0,32,0,64, partial06, partial07); //partial display 6 7
      partial_display(0,32,0,64, partial07, partial08); //partial display 7 8
      partial_display(0,32,0,64, partial08, partial09); //partial display 8 9
      delay(1000);  

      EPD_display_init_Part(); //EPD init Part
      partial_display(0,80,0,128,partial_full00, partial_full_basemap); //partial full  basemap display   
       delay(1000); 
           /******screen clear*****/
      EPD_display_init_Full(); //EPD init Full
      full_display(pic_display_white); //pic_white
       delay(1000); 
    /*********partial full screen display *********/
        EPD_display_init_Part(); //EPD init Part     
        partial_display(0,80,0,128,partial_full00, partial_full01); //partial full display pic1 
         delay(1000); 
        partial_display(0,80,0,128,partial_full01, partial_full02); //partial full display  pic2  
         delay(1000); 
        partial_display(0,80,0,128,partial_full02, partial_full03); //partial full display  pic3        
         delay(1000);   
      /******screen clear*****/
      EPD_display_init_Full(); //EPD init Full
      full_display(pic_display_white); //pic_white
       delay(1000); 
        
       EPD_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
      while(1) 
      {
         Sys_run();//System run
         LED_run();//Breathing lamp
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////extern function/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************** full screen display picture*************************/
void pic_display_white(void)
{
  unsigned int i;
    EPD_W21_WriteCMD(0x10);
    for(i=0;i<1280;i++)      
    {
        EPD_W21_WriteDATA(0x00);  
    }  
    driver_delay_xms(2);

    EPD_W21_WriteCMD(0x13);
    for(i=0;i<1280;i++)      
    {
        EPD_W21_WriteDATA(0xff);  
    }  
    driver_delay_xms(2);     
}
void pic_display1(void)
{
  unsigned int i;
    EPD_W21_WriteCMD(0x10);
    for(i=0;i<1280;i++)      
    {
        EPD_W21_WriteDATA(0x00);  
    }  
    driver_delay_xms(2);

    EPD_W21_WriteCMD(0x13);
    for(i=0;i<1280;i++)      
    {
        EPD_W21_WriteDATA(pgm_read_byte(&gImage_1[i]));  
    }  
    driver_delay_xms(2);     
}

void pic_display2(void)
{
  unsigned int i;
  EPD_W21_WriteCMD(0x10);
  for(i=0;i<1280;i++)      
  {
    EPD_W21_WriteDATA(0x00);  
  }  

  EPD_W21_WriteCMD(0x13);     
  for(i=0;i<1280;i++)      
  {
   EPD_W21_WriteDATA(pgm_read_byte(&gImage_2[i]));  

  }  
}


/***************** partial full screen display picture*************************/
void partial_full00(void)
{
  unsigned int i;
  for(i=0;i<1280;i++)      
  {
      EPD_W21_WriteDATA(0xff);  
  }  
}
void partial_full01(void)
{
  unsigned int i;
  for(i=0;i<1280;i++)      
  {
      EPD_W21_WriteDATA(pgm_read_byte(&gImage_1[i]));  
  }  
}
void partial_full02(void)
{
  unsigned int i;
  for(i=0;i<1280;i++)      
  {
      EPD_W21_WriteDATA(pgm_read_byte(&gImage_2[i]));  
  }  
}
void partial_full03(void)
{   
  unsigned int i;
  for(i=0;i<1280;i++)      
  {
      EPD_W21_WriteDATA(pgm_read_byte(&gImage_3[i]));  
  }  
}
void partial_full_basemap(void)
{   
  unsigned int i;
  for(i=0;i<1280;i++)      
  {
      EPD_W21_WriteDATA(pgm_read_byte(&gImage_basemap[i]));  
  }  
}
/***************** partial display 0~9 picture*************************/
void partial00(void)
{
  unsigned int i;
  for(i=0;i<256;i++)       
  {
      EPD_W21_WriteDATA(0xff);  
  }  
}

void partial01(void)
{
  unsigned int i;

    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num1[i]));
      driver_delay_xms(2);  
      } 
  }
void partial02(void)
{
  unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num2[i]));
      driver_delay_xms(2);  
      } 
  }
void partial03(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num3[i]));
      driver_delay_xms(2);  
      } 
  }
void partial04(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num4[i]));
      driver_delay_xms(2);  
      } 
  }
void partial05(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num5[i]));
      driver_delay_xms(2);  
      } 
  }
void partial06(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num6[i]));
      driver_delay_xms(2);  
      } 
  }
void partial07(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num7[i]));
      driver_delay_xms(2);  
      } 
  }
void partial08(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num8[i]));
      driver_delay_xms(2);  
      } 
  }
void partial09(void)
{
    unsigned int i;
    for(i=0;i<256;i++)       
      {
      EPD_W21_WriteDATA (pgm_read_byte(&gImage_num9[i]));
      driver_delay_xms(2);  
      } 
  }
/*************************EPD display init function******************************************************/

void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(100); //At least 10ms
  EPD_W21_RST_1;
  delay(100);  
}
void EPD_display_init_Full(void)
{

  EPD_W21_Init();  //Electronic paper IC reset
  
  EPD_W21_WriteCMD(0xD2);     
  EPD_W21_WriteDATA(0x3F);
             
  EPD_W21_WriteCMD(0x00);       
  EPD_W21_WriteDATA (0x6F);  //from outside

  EPD_W21_WriteCMD(0x01);       //power setting
  EPD_W21_WriteDATA (0x03);     
  EPD_W21_WriteDATA (0x00);
  EPD_W21_WriteDATA (0x2b);   
  EPD_W21_WriteDATA (0x2b); 
  
  EPD_W21_WriteCMD(0x06);       
  EPD_W21_WriteDATA(0x3f);
  
  EPD_W21_WriteCMD(0x2A);     
  EPD_W21_WriteDATA(0x00); 
  EPD_W21_WriteDATA(0x00); 
  
  EPD_W21_WriteCMD(0x30); 
  EPD_W21_WriteDATA(0x13); 

  EPD_W21_WriteCMD(0x50);
  EPD_W21_WriteDATA(0x57);      

  EPD_W21_WriteCMD(0x60);     
  EPD_W21_WriteDATA(0x22);

  EPD_W21_WriteCMD(0x61);     //resolution setting
  EPD_W21_WriteDATA (0x50);       //source 128   
  EPD_W21_WriteDATA (0x80);       

  EPD_W21_WriteCMD(0x82);     
  EPD_W21_WriteDATA(0x12);  //-1v

  EPD_W21_WriteCMD(0xe3);     
  EPD_W21_WriteDATA(0x33);

  Full_lut_bw();  
  
  EPD_W21_WriteCMD(0x04);  //Power on
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
  }
void EPD_display_init_Part(void)
{
  EPD_W21_Init(); //Electronic paper IC reset
  EPD_W21_WriteCMD(0xD2);     
  EPD_W21_WriteDATA(0x3F);
             
  EPD_W21_WriteCMD(0x00);       
  EPD_W21_WriteDATA (0x6F);  //from outside


  EPD_W21_WriteCMD(0x01);       //power setting
  EPD_W21_WriteDATA (0x03);     
  EPD_W21_WriteDATA (0x00);
  EPD_W21_WriteDATA (0x2b);   
  EPD_W21_WriteDATA (0x2b); 
  
  EPD_W21_WriteCMD(0x06);       
  EPD_W21_WriteDATA(0x3f);
  
  EPD_W21_WriteCMD(0x2A);     
  EPD_W21_WriteDATA(0x00); 
  EPD_W21_WriteDATA(0x00); 
  
  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x05);
        
  EPD_W21_WriteCMD(0x50);     
  EPD_W21_WriteDATA(0xF2);

  EPD_W21_WriteCMD(0x60);     
  EPD_W21_WriteDATA(0x22);

  EPD_W21_WriteCMD(0x82);     
  EPD_W21_WriteDATA(0x00);//-0.1v

  EPD_W21_WriteCMD(0xe3);     
  EPD_W21_WriteDATA(0x33);

  Part_lut_bw();  
  
  EPD_W21_WriteCMD(0x04);  //Power on
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
}
/***************************full display function*************************************/
void full_display(void pic_display(void))
{

    
    pic_display(); //picture
  
    EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
    driver_delay_xms(100);      //!!!The delay here is necessary, 200uS at least!!!     
    EPD_W21_WriteCMD(0x02);
    lcd_chkstatus();
}

/***************************partial display function*************************************/

void partial_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end ,void partial_old(void),void partial_new(void)) //partial display
{
    EPD_W21_WriteCMD(0x91);   //This command makes the display enter partial mode
    EPD_W21_WriteCMD(0x90);   //resolution setting
    EPD_W21_WriteDATA (x_start);   //x-start     
    EPD_W21_WriteDATA (x_end-1);   //x-end  

    EPD_W21_WriteDATA (y_start);   //y-start    
    EPD_W21_WriteDATA (y_end-1);  //y-end
    EPD_W21_WriteDATA (0x00); 

    EPD_W21_WriteCMD(0x10);       //writes Old data to SRAM for programming
    partial_old();
    EPD_W21_WriteCMD(0x13);      //writes New data to SRAM.
    partial_new();
      
    EPD_W21_WriteCMD(0x12);    //DISPLAY REFRESH                 
    driver_delay_xms(10);     //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
    
}
/////////////////////////////Enter deep sleep mode////////////////////////
void EPD_sleep(void)
{
    EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING  
    EPD_W21_WriteDATA(0xf7);
       
    EPD_W21_WriteCMD(0X02);   //power off
    lcd_chkstatus();
    EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);
}

//LUT download
void Full_lut_bw(void)
{
  unsigned int count;
  EPD_W21_WriteCMD(0x23);
  for(count=0;count<42;count++)      
  {EPD_W21_WriteDATA(pgm_read_byte(&lut_w1[count]));}    
  
  EPD_W21_WriteCMD(0x24);
  for(count=0;count<42;count++)      
  {EPD_W21_WriteDATA(pgm_read_byte(&lut_b1[count]));}          
}

void Part_lut_bw(void)
{
  unsigned int count;
  EPD_W21_WriteCMD(0x23);
  for(count=0;count<42;count++)      
  {EPD_W21_WriteDATA(pgm_read_byte(&lut_w[count]));}    
  
  EPD_W21_WriteCMD(0x24);
  for(count=0;count<42;count++)      
  {EPD_W21_WriteDATA(pgm_read_byte(&lut_b[count]));}          
}


//Detection busy
void lcd_chkstatus(void)
{
    EPD_W21_WriteCMD(0x71);
  while(!isEPD_W21_BUSY)//0 is busy
  {
    ESP.wdtFeed(); //Feed dog to prevent system reset
    }                      
}


////////////////////////////////////////////////////

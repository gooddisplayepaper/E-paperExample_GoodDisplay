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
void EPD_init(void);
void PIC_display(const unsigned char* picData_old,const unsigned char* picData_new);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clean(void);
unsigned char HRES,VRES_byte1,VRES_byte2;

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

    //PICTURE1
    
    EPD_init(); //EPD init
    PIC_display(gImage_BW,gImage_R);//EPD_picture1
    EPD_refresh();//EPD_refresh   
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000);

    EPD_init(); //EPD init
    PIC_display_Clean();//EPD_picture1
    EPD_refresh();//EPD_refresh   
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!

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
void lut_bw(void)
{
  unsigned int count;
  EPD_W21_WriteCMD(0x20);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_vcom0[count]));}
  
  EPD_W21_WriteCMD(0x21);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_w[count]));}   
  
  EPD_W21_WriteCMD(0x22);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_b[count]));}    
  
  EPD_W21_WriteCMD(0x23);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_g1[count]));}    
  
  EPD_W21_WriteCMD(0x24);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_g2[count]));}          
}

void lut_red(void)
{
  unsigned int count;
  EPD_W21_WriteCMD(0x25);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_vcom1[count]));}
  
  EPD_W21_WriteCMD(0x26);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_red0[count])); }  
  
  EPD_W21_WriteCMD(0x27);
  for(count=0;count<15;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_red1[count])); }   
}
void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(1000); //At least 10ms
  EPD_W21_RST_1;
  delay(1000);  
}
void EPD_init(void)
{
     HRES=0xc8;            //200
    VRES_byte1=0x00;      //200
    VRES_byte2=0xc8;
    EPD_W21_Init(); //Electronic paper IC reset
    EPD_W21_WriteCMD(0x01); 
    EPD_W21_WriteDATA(0x07);      //Set high and low voltage
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x08);
    EPD_W21_WriteDATA(0x00);
  
    EPD_W21_WriteCMD(0x06);         //Boost settings
    EPD_W21_WriteDATA(0x07);
    EPD_W21_WriteDATA(0x07);
    EPD_W21_WriteDATA(0x07);
  
    EPD_W21_WriteCMD(0x04);         //Power on 
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
  

    EPD_W21_WriteCMD(0X00);
    EPD_W21_WriteDATA(0xcf);    //Select maximum resolution
  
    EPD_W21_WriteCMD(0X50);
    EPD_W21_WriteDATA(0x37);
    
    EPD_W21_WriteCMD(0x30);     //PLL settings
    EPD_W21_WriteDATA(0x39);    
    
    EPD_W21_WriteCMD(0x61);     //Pixel settings
    EPD_W21_WriteDATA(HRES);          //200 pixels
    EPD_W21_WriteDATA(VRES_byte1);    //200 pixels
    EPD_W21_WriteDATA(VRES_byte2);
    
    EPD_W21_WriteCMD(0x82);     //vcom settings
    EPD_W21_WriteDATA(0x30);    //Update VCOM, original 0x0E upgrade to 0X30  
    lut_bw();
    lut_red();
 }
void EPD_refresh(void)
{
    EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
    driver_delay_xms(100);          //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
} 
void EPD_sleep(void)
{
      EPD_W21_WriteCMD(0X50);
      EPD_W21_WriteDATA(0x17);    //BD floating
      EPD_W21_WriteCMD(0x82);     //to solve Vcom drop    
      EPD_W21_WriteDATA(0x00);    
      EPD_W21_WriteCMD(0x01);     //power setting      
      EPD_W21_WriteDATA(0x02);    //gate switch to external
      EPD_W21_WriteDATA(0x00);
      EPD_W21_WriteDATA(0x00); 
      EPD_W21_WriteDATA(0x00); 

      driver_delay_xms(1500);     //delay 1.5S
      EPD_W21_WriteCMD(0X02);     //power off
      driver_delay_xms(40000);
}


void PIC_display(const unsigned char* picData_old,const unsigned char* picData_new)
{
    unsigned int i;
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<10000;i++)      
  {
    EPD_W21_WriteDATA(pgm_read_byte(&picData_old[i]));
  }
  
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<50000;i++)      
  {
    EPD_W21_WriteDATA(pgm_read_byte(&picData_new[i]));
  }
}
void PIC_display_Clean(void)
{
    unsigned int i;
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<10000;i++)      
  {
    EPD_W21_WriteDATA(0xff);
  }
  
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<50000;i++)      
  {
    EPD_W21_WriteDATA(0xff);
  }
}
void lcd_chkstatus(void)
{
    EPD_W21_WriteCMD(0x71);
  while(!isEPD_W21_BUSY)//0 is busy
  {
    ESP.wdtFeed(); //Feed dog to prevent system reset
    }                      
}



//////////////////////////////////END/////////////////////////////////////////

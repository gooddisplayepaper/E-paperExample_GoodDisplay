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
void delay(unsigned long xms);
void DELAY_S(unsigned int delaytime);     
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
//EPD
void EPD_display_init(void);//EPD init 
void EPD_full_display_clearing(void);//Clear screen after power on
void EPD_full_display(const unsigned char *old_data,const unsigned char *new_data,unsigned char mode);// mode0:Refresh picture1,mode1:Refresh picture2... ,mode2¡¢3:Clear
void partial_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end ,const unsigned char *old_data,const unsigned char *new_data,unsigned char mode); //partial display
void lut(void);
void lut1(void);
void lcd_chkstatus(void);
void EPD_deep_sleep(void); //Enter deep sleep mode

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
      /******Clear screen after power on*****/
  EPD_display_init(); //EPD init
  EPD_full_display_clearing(); //Clear screen after power on
  EPD_deep_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  
  EPD_display_init(); //EPD init
  EPD_full_display(gImage_1,gImage_1,0); //pic1
  EPD_deep_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  delay(3000);

  EPD_display_init(); //EPD init
  EPD_full_display(gImage_1,gImage_2,1); //pic2
  EPD_deep_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  delay(3000);
                                                                                                          
  EPD_display_init(); //EPD init
  EPD_full_display(gImage_2,gImage_3,1); //pic3
  EPD_deep_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  delay(3000);

      /******End screen clearing*****/
  EPD_display_init(); //EPD init
  EPD_full_display(gImage_3,gImage_3,2); //End screen clearing
  EPD_full_display(gImage_3,gImage_3,3); //End screen clearing
  
//(Perform a full-screen refresh operation after 5 partial refreshes, otherwise the residual image may not be removed.) 
//////////////////////////partial display 0~9//////////////////////////////////////////// 
  EPD_display_init(); //EPD init
  partial_display(0,32,0,64, gImage_num1,gImage_num1,0); //partial display 0 1                             
  partial_display(0,32,0,64, gImage_num1,gImage_num2,1); //partial display 1 2                         //////////////£¨x,y£©   ----Y----
  partial_display(0,32,0,64, gImage_num2,gImage_num3,1); //partial display 1 2                         //////////////£¨x,y£©   ----Y----
  partial_display(0,32,0,64, gImage_num3,gImage_num4,1); //partial display 1 2                         //////////////£¨x,y£©   ----Y----
  partial_display(0,32,0,64, gImage_num4,gImage_num5,1); //partial display 1 2                         //////////////£¨x,y£©   ----Y----

/*After the partial refresh, you need to use OTP to clean the screen, otherwise the screen of the electronic paper may not be removed.*/
  /******Clear screen after Partial refresh*****/
  EPD_display_init(); //EPD init
  EPD_full_display_clearing(); //Clear screen after power on
  EPD_deep_sleep(); //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  while(1);


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
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
       if(value & 0x80)
          EPD_W21_MOSI_1;
        else
          EPD_W21_MOSI_0;   
        value = (value << 1); 
        EPD_W21_CLK_1; 
    }
}

void EPD_W21_WriteCMD(unsigned char command)
{
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}



//*************************EPD display init function******************************************************/
void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(10);
  EPD_W21_RST_1;
  delay(10);
}
void EPD_display_init(void)
{
   EPD_W21_Init();
    delay(100);          //reset IC and select BUS 
    EPD_W21_WriteCMD(0x00);             //panel setting
    EPD_W21_WriteDATA (0xDf);
    EPD_W21_WriteDATA (0x0e); 
  
    EPD_W21_WriteCMD(0x4D);             //FITIinternal code
    EPD_W21_WriteDATA (0x55);

    EPD_W21_WriteCMD(0xaa);             
    EPD_W21_WriteDATA (0x0f);
    
    EPD_W21_WriteCMD(0xE9);             
    EPD_W21_WriteDATA (0x02);

    EPD_W21_WriteCMD(0xb6);             
    EPD_W21_WriteDATA (0x11);
    
    EPD_W21_WriteCMD(0xF3);             
    EPD_W21_WriteDATA (0x0a);     

    EPD_W21_WriteCMD(0x61);     //resolution setting
    EPD_W21_WriteDATA (0xc8);
    EPD_W21_WriteDATA (0x00);   
    EPD_W21_WriteDATA (0xc8);    
    
    EPD_W21_WriteCMD(0x60);          //Tcon setting   
    EPD_W21_WriteDATA (0x00);
    
    EPD_W21_WriteCMD(0X50);           
    EPD_W21_WriteDATA(0x97);//
    
    EPD_W21_WriteCMD(0XE3);           
    EPD_W21_WriteDATA(0x00);
    
    EPD_W21_WriteCMD(0x04);//Power on
    delay(100);
    lcd_chkstatus();  
      
  }
/***************************full display function*************************************/
  void EPD_full_display_clearing(void)//Clear the screen for the first time
  {
    unsigned int i,j;

    
    for(j=0;j<2;j++)
    {
      EPD_W21_WriteCMD(0x10);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(0x00);  
      }  
      delay(2);
      EPD_W21_WriteCMD(0x13);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(0xff);  
      }  
      delay(2);
    
      EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
      delay(100);      //!!!The delay here is necessary, 200uS at least!!!     
      lcd_chkstatus();  
    }
 }    
  
  void EPD_full_display(const unsigned char *old_data,const unsigned char *new_data,unsigned char mode)// mode0:Refresh picture1,mode1:Refresh picture2... ,mode2¡¢3:Clear
{   
    unsigned int i;
    
    if(mode==0)  //mode0:Refresh picture1
    {
      EPD_W21_WriteCMD(0x10);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(0xff);  
      }  
      delay(2);
      EPD_W21_WriteCMD(0x13);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(pgm_read_byte(&new_data[i]));  
      }  
      delay(2);
    }
    
    else if(mode==1)  //mode0:Refresh picture2...
    {
      EPD_W21_WriteCMD(0x10);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(old_data[i]);  
      }  
      delay(2);
      EPD_W21_WriteCMD(0x13);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(pgm_read_byte(&new_data[i]));  
      }  
      delay(2);
    }
    
   else if(mode==2) 
    {
      EPD_W21_WriteCMD(0x10);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(pgm_read_byte(&old_data[i]));  
      }  
      delay(2);
      EPD_W21_WriteCMD(0x13);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(0xff);  
      }  
      delay(2);
    }  
   else if(mode==3) 
    {
      EPD_W21_WriteCMD(0x10);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(0xff); 
      }  
      delay(2);
      EPD_W21_WriteCMD(0x13);
      for(i=0;i<5000;i++)      
      {
          EPD_W21_WriteDATA(0xff);  
      }  
      delay(2);
    }

    EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
    delay(10);      //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
}

/***************************partial display function*************************************/

void partial_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end ,const unsigned char *old_data,const unsigned char *new_data,unsigned char mode) //partial display
{
    unsigned datas,i;
    EPD_W21_WriteCMD(0x00);             //panel setting
    EPD_W21_WriteDATA (0xff);
    EPD_W21_WriteDATA (0x0e);       
    lut1();

    EPD_W21_WriteCMD(0x91);   //This command makes the display enter partial mode
    EPD_W21_WriteCMD(0x90);   //resolution setting
    EPD_W21_WriteDATA (x_start);   //x-start     
    EPD_W21_WriteDATA (x_end-1);   //x-end  
    EPD_W21_WriteDATA (0);   //x Reserved 

    EPD_W21_WriteDATA (y_start);   //y-start    
    EPD_W21_WriteDATA (0);   //y Reserved   
    EPD_W21_WriteDATA (y_end);   //y-end  
    EPD_W21_WriteDATA (0x01); 
    datas=(x_end-x_start)*(y_end-y_start)/8;
    
    EPD_W21_WriteCMD(0x10);        //writes Old data to SRAM for programming
    if(mode==0)
    {
      for(i=0;i<datas;i++)       
      {
        EPD_W21_WriteDATA(0xff);  
      }       
    }
    else
    {
      for(i=0;i<datas;i++)       
      {
        EPD_W21_WriteDATA(pgm_read_byte(&old_data[i]));  
      } 
    }
    EPD_W21_WriteCMD(0x13);        //writes New data to SRAM.
    for(i=0;i<datas;i++)       
    {
      EPD_W21_WriteDATA(pgm_read_byte(&new_data[i]));  
    } 
      
    EPD_W21_WriteCMD(0x12);    //DISPLAY REFRESH                 
    delay(100);     //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
    
}
/////////////////////////////Enter deep sleep mode////////////////////////
void EPD_deep_sleep(void) //Enter deep sleep mode
{
    EPD_W21_WriteCMD(0X50);
    EPD_W21_WriteDATA(0xf7);  
    EPD_W21_WriteCMD(0X02);   //power off
    lcd_chkstatus();
    EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);
}

void lut1(void)
{
  unsigned int count;
  EPD_W21_WriteCMD(0x20);
  for(count=0;count<42;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_vcomDC1[count]));}

  EPD_W21_WriteCMD(0x21);
  for(count=0;count<42;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_ww1[count]));}   
  
  EPD_W21_WriteCMD(0x22);
  for(count=0;count<42;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_bw1[count]));} 

  EPD_W21_WriteCMD(0x23);
  for(count=0;count<42;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_wb1[count]));} 

  EPD_W21_WriteCMD(0x24);
  for(count=0;count<42;count++)      
    {EPD_W21_WriteDATA(pgm_read_byte(&lut_bb1[count]));}   
}




void lcd_chkstatus(void)
{
  while(!isEPD_W21_BUSY);   
                       
}

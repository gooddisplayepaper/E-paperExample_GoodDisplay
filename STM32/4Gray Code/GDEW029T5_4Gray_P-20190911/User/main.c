#include "stm32f10x.h"
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	


ErrorStatus HSEStartUpStatus;

unsigned char HRES,VRES_byte1,VRES_byte2;


/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

//EPD--OTP
void EPD_init(void);
void PIC_display (const unsigned char* picData);
void EPD_display_Clean(void);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);

//4 Gray

void EPD_init_4Gray(void);//EPD init 4 Gray
void EPD_full(void pic_display(void)); //full  display
void pic_display_4bit(void);
void pic_4bit(void);
void lut11(void);
//EPD

void EPD_full(void pic_display(void)); //full  display
void EPD_partial_display(u16 x_start,u16 y_start,const unsigned char *old_data,const unsigned char *new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode); //partial display 
void lut(void);
void lut1(void);
//partial display
void partial_full00(void);
void partial_full01(void);
void partial_full02(void);
void partial_full03(void);

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


unsigned char old_data[1000];
void driver_delay_us(unsigned int xus)
{
	for(;xus>1;xus--);
}

void driver_delay_xms(unsigned long xms)	
{	
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
	{
        for(i=0; i<256; i++);
    }
}
void DELAY_S(unsigned int delaytime)     //  1s
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

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
#define NVIC_VectTab_FLASH  misc.h
*******************************************************************************/

int	main(void)
{
	RCC_Configuration();
	//GPIO config
	GPIO_Configuration();
	
	
	while(1)
	{	
		
		//2 gray picture(OTP)
		EPD_init(); //EPD init
		PIC_display(gImage_1); //Clear screen
    EPD_refresh();//EPD_refresh		
		EPD_sleep();//EPD_sleep`
    DELAY_S(30);

		//Clear screen (OTP)
		EPD_init(); //EPD init
		EPD_display_Clean(); //Clear screen
    EPD_refresh();//EPD_refresh		
		EPD_sleep();//EPD_sleep`		
		//4 gray picture
		EPD_init_4Gray(); //EPD init 4 Gray
		EPD_full(pic_display_4bit); //pic1
		EPD_sleep(); //Enter deep sleep mode
		DELAY_S(30);

		//Clear screen (OTP)
		EPD_init(); //EPD init
		EPD_display_Clean(); //Clear screen
    EPD_refresh();//EPD_refresh		
		EPD_sleep();//EPD_sleep`
		
/********partial********************/

	EPD_init_4Gray(); //EPD init 4 Gray
  //Demo1
	EPD_partial_display(0,0,gImage_run1,gImage_run1,296,128,0); //partial display 
	EPD_partial_display(0,0,gImage_run1,gImage_run2,190,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run2,gImage_run3,190,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run3,gImage_run4,190,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run4,gImage_run5,190,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run5,gImage_run6,190,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run6,gImage_run1,296,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run1,gImage_run2,296,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run2,gImage_run3,296,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run3,gImage_run4,296,128,1); //partial display 
	EPD_partial_display(0,0,gImage_run4,gImage_run5,296,128,1); //partial display 


//Clear screen (OTP)
		EPD_init(); //EPD init
		EPD_display_Clean(); //Clear screen
    EPD_refresh();//EPD_refresh		
		EPD_sleep();//EPD_sleep

		while(1);	 
	}
 }


 
 
 
 
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////extern function/////////////////////////////////////////////////////////////////////////////////////////////////////////////



/********Color display description
      white  gray1  gray2  black
0x10|  ff     ff     00     00
0x13|  ff     00     ff     00
                                   ****************/
void pic_4bit(void)
{
		unsigned int i,r,t,y;
		
		EPD_W21_WriteCMD(0x10);	  	
		for(y=0;y<592;y++)	     
		{
			EPD_W21_WriteDATA(0xff);  //white
		}  
		for(t=0;t<592;t++)	     
		{
			EPD_W21_WriteDATA(0xff);  //gray1
		}  
		for(r=0;r<592;r++)	     
		{
			EPD_W21_WriteDATA(0x00);  //gray2
		}  
		for(i=0;i<592;i++)	     
		{
			EPD_W21_WriteDATA(0x00);  //black
		}  
		EPD_W21_WriteCMD(0x13);
		for(i=0;i<592;i++)	     
		{
			EPD_W21_WriteDATA(0xff);  //white
		}  
		for(r=0;r<592;r++)	     
		{
			EPD_W21_WriteDATA(0x00); //gray1
		}  
		for(t=0;t<592;t++)	     
		{
			EPD_W21_WriteDATA(0xff);  //gray2
		}  
		for(y=0;y<592;y++)	     
		{
			EPD_W21_WriteDATA(0x00); //black
		}  
	
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

		for(i=0;i<4736;i++)	               //4736*4  212*104
		{ 
			temp3=0;
      for(j=0;j<4;j++)	
			{
				temp1 = gImage_11[i*4+j];
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
						temp3 |= 0x00;	//gray2	
        if(j!=3)					
			  temp3 <<= 1;	
				
			
		 }	
       	EPD_W21_WriteDATA(temp3);			
		}
    //new  data
		EPD_W21_WriteCMD(0x13);	       

		for(i=0;i<4736;i++)	               //4736*4   212*104
		{ 
			temp3=0;
      for(j=0;j<4;j++)	
			{
				temp1 = gImage_11[i*4+j];
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
						temp3 |= 0x01;	//gray2
        if(j!=3)				
			  temp3 <<= 1;				
			
		 }	
       	EPD_W21_WriteDATA(temp3);			
		}
}


/*************************EPD display init function******************************************************/
void EPD_init_4Gray(void)
{
		HRES=0x80;					  	//128
	  VRES_byte1=0x01;				//296
	  VRES_byte2=0x28;
		EPD_W21_Init();
		EPD_W21_WriteCMD(0x01);			//POWER SETTING
		EPD_W21_WriteDATA (0x03);
		EPD_W21_WriteDATA (0x00);      
		EPD_W21_WriteDATA (0x2b);																	 
		EPD_W21_WriteDATA (0x2b);		
		EPD_W21_WriteDATA (0x13);

		EPD_W21_WriteCMD(0x06);         //booster soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C 
		
		EPD_W21_WriteCMD(0x04);
		lcd_chkstatus();
		
		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0xbf);		//KW-bf   KWR-2F	BWROTP 0f	BWOTP 1f
		
		EPD_W21_WriteCMD(0x30);			//PLL setting
		EPD_W21_WriteDATA (0x3c);      	//100hz 
		
		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (HRES);        	 
		EPD_W21_WriteDATA (VRES_byte1);		
		EPD_W21_WriteDATA (VRES_byte2);

		EPD_W21_WriteCMD(0x82);			//vcom_DC setting
	  EPD_W21_WriteDATA (0x10);

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97); //VBDF 17|D7 VBDW 97 VBDB 57		VBDF F7 VBDW 77 VBDB 37  VBDR B7


	}
/***************************full display function*************************************/
void EPD_full(void pic_display(void))
{	
		pic_display(); //picture
		lut11(); //Power settings
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	    //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}


/////////////////////////////Enter deep sleep mode////////////////////////
void EPD_sleep(void) //Enter deep sleep mode
{
		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0xf7);	
		EPD_W21_WriteCMD(0X02);  	//power off
	  lcd_chkstatus();
		EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}

//LUT download
void lut11(void)
{
	unsigned int count;	 
	{
		EPD_W21_WriteCMD(0x20);							//vcom
		for(count=0;count<44;count++)
			{EPD_W21_WriteDATA(lut_vcom11[count]);}
		
	EPD_W21_WriteCMD(0x21);							//red not use
	for(count=0;count<42;count++)
		{EPD_W21_WriteDATA(lut_ww11[count]);}

		EPD_W21_WriteCMD(0x22);							//bw r
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_bw11[count]);}

		EPD_W21_WriteCMD(0x23);							//wb w
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_wb11[count]);}

		EPD_W21_WriteCMD(0x24);							//bb b
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_bb11[count]);}

		EPD_W21_WriteCMD(0x25);							//vcom
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_ww11[count]);}
	}	         
}






///////////////////OTP/////////////////////////////////////////////////////////////////
void EPD_init(void)
{
		HRES=0x80;					  	//128
	  VRES_byte1=0x01;				//296
	  VRES_byte2=0x28;
	
		EPD_W21_Init();
	
		EPD_W21_WriteCMD(0x06);         //boost soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C       

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x1f);		//LUT from OTP£¬128x296
	  EPD_W21_WriteDATA(0x0d);     //VCOM to 0V

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (HRES);        	 
		EPD_W21_WriteDATA (VRES_byte1);		
		EPD_W21_WriteDATA (VRES_byte2);

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}
void PIC_display(const unsigned char* picData)
{
    unsigned int i;
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<4736;i++)	     
	  EPD_W21_WriteDATA(0xff); 
	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<4736;i++)	     
	{
	  EPD_W21_WriteDATA(*picData);
	  picData++;
	}

}

/***************** full screen display picture*************************/
void EPD_display_Clean(void)
{
	unsigned int i;
		EPD_W21_WriteCMD(0x10);
		for(i=0;i<4736;i++)	     
		{
				EPD_W21_WriteDATA(0xff);  
		}  
		driver_delay_xms(2);	

		EPD_W21_WriteCMD(0x13);
		for(i=0;i<4736;i++)	     
		{
				EPD_W21_WriteDATA(0xff);  
		}  
		driver_delay_xms(2);		 
}

void EPD_refresh(void)
{
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	        //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}

//Detection busy
void lcd_chkstatus(void)
{
	unsigned char busy;
	do
	{
		EPD_W21_WriteCMD(0x71);
		busy = isEPD_W21_BUSY;
		busy =!(busy & 0x01);        
	}
	while(busy);   
	driver_delay_xms(200);                       
}






///////////////partial////////////////////////////////////////////////
//LUT download
void lut(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x20);
	for(count=0;count<44;count++)	     
		{EPD_W21_WriteDATA(lut_vcomDC[count]);}

	EPD_W21_WriteCMD(0x21);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_ww[count]);}   
	
	EPD_W21_WriteCMD(0x22);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_bw[count]);} 

	EPD_W21_WriteCMD(0x23);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_wb[count]);} 

	EPD_W21_WriteCMD(0x24);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_bb[count]);} 
}

void lut1(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x20);
	for(count=0;count<44;count++)	     
		{EPD_W21_WriteDATA(lut_vcom1[count]);}

	EPD_W21_WriteCMD(0x21);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_ww1[count]);}   
	
	EPD_W21_WriteCMD(0x22);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_bw1[count]);} 

	EPD_W21_WriteCMD(0x23);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_wb1[count]);} 

	EPD_W21_WriteCMD(0x24);
	for(count=0;count<42;count++)	     
		{EPD_W21_WriteDATA(lut_bb1[count]);}   
}


/***************************partial display function*************************************/

void EPD_partial_display(u16 x_start,u16 y_start,const unsigned char *old_data,const unsigned char *new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode) //partial display 
{
	unsigned int i,count;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	x_start=x_start;//×ª»»Îª×Ö½Ú
	x_end=x_start+PART_LINE-1; 
	
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
	
count=PART_COLUMN*PART_LINE/8;
	
	  EPD_W21_WriteCMD(0x82);			//vcom_DC setting  	
    EPD_W21_WriteDATA (0x08);	
		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0x47);		
		lut1();
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start1);
		EPD_W21_WriteDATA (y_start2);   //y-start    
		
		EPD_W21_WriteDATA (y_end1);		
		EPD_W21_WriteDATA (y_end2);  //y-end
		EPD_W21_WriteDATA (0x28);	

		EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
 
	if(mode==0)
	for(i=0;i<count;i++)	     
	{
	 EPD_W21_WriteDATA(0x00);  
	}
	else
	 for(i=0;i<count;i++)	     
	{
	 EPD_W21_WriteDATA(~old_data[i]);  
	}  
	
	EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
	if(mode!=2) //new  datas
	{
		for(i=0;i<count;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data[i]);  
		//old_data[i]=new_data[i];
	 }
  }
  else  //white
  {
		for(i=0;i<count;i++)	     
		{
		 EPD_W21_WriteDATA(0x00);  
		}		
	}		
    	
		EPD_W21_WriteCMD(0x12);		 //DISPLAY REFRESH 		             
		driver_delay_xms(1);     //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
	  
}






/***********************************************************
						end file
***********************************************************/















/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
 
  // Reset RCC clock configuration
  RCC_DeInit();
 
  // Enable external crystal
  RCC_HSEConfig(RCC_HSE_ON);
  
  // Waiting for the external crystal to stabilize
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    // Set the phase-locked loop frequency PLLCLK = 8MHz * 9 = 72 MHz
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  }
  else {
    // Enable internal crystal
    RCC_HSICmd(ENABLE);
    // Waiting for the internal crystal to stabilize
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // Set the phase-locked loop frequency PLLCLK = 8MHz/2 * 16 = 64 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
  }

    // Enable flash prefetch cache
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  //Set the code delay, FLASH_Latency_2 is two delay cycles
  FLASH_SetLatency(FLASH_Latency_2);
	
  //Set the system total clock
  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  //Set the high speed device total clock, RCC_HCLK_Div1 is the system clock divided by 1
  RCC_PCLK2Config(RCC_HCLK_Div1); 

  //Set the low speed device total clock, RCC_HCLK_Div2 is the system clock divided by 2
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //Enable phase-locked loop multiplier
  RCC_PLLCmd(ENABLE);
  
  // Waiting for the frequency of the phase-locked loop to multiply after frequency stabilization
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  // Select the phase-locked loop clock as the system clock
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  // Waiting for setup to complete
  while(RCC_GetSYSCLKSource() != 0x08);
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
            ENABLE);

}

/*******************************************************************************
* Function name  : GPIO_Configuration
* Description         : Set the GPIO pin parameters used by the SPI serial port.
* Input        : None
* Output        : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14 |GPIO_Pin_15;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
  //NVIC_InitTypeDef NVIC_InitStructure;
  ;
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif







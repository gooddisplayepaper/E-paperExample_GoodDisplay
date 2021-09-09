#include "stm32f10x.h"
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

ErrorStatus HSEStartUpStatus;


unsigned char k=2;
unsigned int size;
unsigned char HRES,VRES_byte1,VRES_byte2;


/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

void EPD_init_OTP(void);
void EPD_display_init(void);//EPD init 
void PIC_display(void pic_display(void)); //full  display
void EPD_full_display(const unsigned char *old_data,const unsigned char *new_data,unsigned char mode);// mode0:Clear,mode1:Refresh picture
void EPD_partial_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end ,void partial_old(void),void partial_new(void)); //partial display
void lut(void);
void lut1(void);
void lcd_chkstatus(void);
void EPD_deep_sleep(void); //Enter deep sleep mode
void EPD_refresh(void);
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

void PIC_display_Clean(void);

unsigned char  EPD_W21_ReadDATA(void);
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
//	unsigned int i;
	RCC_Configuration();
	//GPIO config
	GPIO_Configuration();

		/******screen clear*****/	
	EPD_display_init(); //EPD init
	PIC_display(pic_display_white);//Clear screen after power on
	EPD_deep_sleep();//Enter deep sleep mode,This step is a must

	
	EPD_display_init(); //EPD init
	EPD_full_display(gImage_1,gImage_1,0); //pic1
	EPD_deep_sleep(); //Enter deep sleep mode,This step is a must
	driver_delay_xms(50000);

	EPD_display_init(); //EPD init
	EPD_full_display(gImage_1,gImage_2,1); //pic2
	EPD_deep_sleep(); //Enter deep sleep mode,This step is a must

	
//(Perform a full-screen refresh operation after 5 partial refreshes, otherwise the residual image may not be removed.)	
//////////////////////////partial display 0~9////////////////////////////////////////////	
	
  EPD_display_init(); //EPD init
  EPD_partial_display(0,32,0,64, partial00, partial01); //partial display 0 1                             
	EPD_partial_display(0,32,0,64, partial01, partial02); //partial display 1 2                         //////////////（x,y）   ----Y----
	EPD_partial_display(0,32,0,64, partial02, partial03); //partial display 2 3                        /     /      /                   X|
	EPD_partial_display(0,32,0,64, partial03, partial04); //partial display 3 4                       /W    /      /                     |                  
	EPD_partial_display(0,32,0,64, partial04, partial05); //partial display 4 5                      ///// L //////                      |


	/******Clear screen after Partial refresh*****/
		//EPD_Clean
		EPD_init_OTP(); //EPD init
	  PIC_display_Clean();//Clear screen after Partial refresh
		EPD_refresh();//EPD_refresh		
		EPD_deep_sleep();//Enter deep sleep mode,This step is a must
 }


 
 
 
 
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////extern function/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************** full screen display picture*************************/
void pic_display_white(void)
{
	unsigned int i;
		EPD_W21_WriteCMD(0x10);
		for(i=0;i<2888;i++)	     
		{
				EPD_W21_WriteDATA(0x00);  
		}  
		driver_delay_xms(2);

		EPD_W21_WriteCMD(0x13);
		for(i=0;i<2888;i++)	     
		{
				EPD_W21_WriteDATA(0xff);  
		}  
		driver_delay_xms(2);		 
}
void pic_display1(void)
{
	unsigned int i;
		EPD_W21_WriteCMD(0x10);
		for(i=0;i<2888;i++)	     
		{
				EPD_W21_WriteDATA(0x00);  
		}  
		driver_delay_xms(2);

		EPD_W21_WriteCMD(0x13);
		for(i=0;i<2888;i++)	     
		{
				EPD_W21_WriteDATA(gImage_1[i]);  
		}  
		driver_delay_xms(2);	 	 
}

void pic_display2(void)
{
	unsigned int i;
	EPD_W21_WriteCMD(0x10);
	for(i=0;i<2888;i++)	     
	{
		EPD_W21_WriteDATA(0x00);  
	}  

	EPD_W21_WriteCMD(0x13);	  	
	for(i=0;i<2888;i++)	     
	{
   EPD_W21_WriteDATA(gImage_2[i]);  

	}  
}


/***************** partial full screen display picture*************************/
void partial_full00(void)
{
	unsigned int i;
	for(i=0;i<2888;i++)	     
	{
			EPD_W21_WriteDATA(0x00);  
	}  
}
void partial_full01(void)
{
	unsigned int i;
	for(i=0;i<2888;i++)	     
	{
			EPD_W21_WriteDATA(~gImage_1[i]);  
	}  
}
void partial_full02(void)
{
	unsigned int i;
	for(i=0;i<2888;i++)	     
	{
			EPD_W21_WriteDATA(~gImage_2[i]);  
	}  
}
void partial_full03(void)
{   
	unsigned int i;
	for(i=0;i<2888;i++)	     
	{
			EPD_W21_WriteDATA(~gImage_3[i]);  
	}  
}

/***************** partial display 0~9 picture*************************/
void partial00(void)
{
	unsigned int i;
	for(i=0;i<256;i++)	     
	{
			EPD_W21_WriteDATA(0x00);  
	}  
}

void partial01(void)
{
	unsigned int i;

		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num1[i]);
			driver_delay_xms(2);  
			}	
	}
void partial02(void)
{
  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num2[i]);
			driver_delay_xms(2);  
			}	
	}
void partial03(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num3[i]);
			driver_delay_xms(2);  
			}	
	}
void partial04(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num4[i]);
			driver_delay_xms(2);  
			}	
	}
void partial05(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num5[i]);
			driver_delay_xms(2);  
			}	
	}
void partial06(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num6[i]);
			driver_delay_xms(2);  
			}	
	}
void partial07(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num7[i]);
			driver_delay_xms(2);  
			}	
	}
void partial08(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num8[i]);
			driver_delay_xms(2);  
			}	
	}
void partial09(void)
{
	  unsigned int i;
		for(i=0;i<256;i++)	     
			{
			EPD_W21_WriteDATA (~gImage_num9[i]);
			driver_delay_xms(2);  
			}	
	}
/*************************EPD display init function******************************************************/
void EPD_init_OTP(void)
{
	  HRES=0x98;						//152
	  VRES_byte1=0x00;			//152
	  VRES_byte2=0x98;
	
		EPD_W21_Init(); //Electronic paper IC reset
	
		EPD_W21_WriteCMD(0x06);     //boost soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C       

		EPD_W21_WriteCMD(0x04);  //Power on
		lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

		EPD_W21_WriteCMD(0x00);			 //panel setting
		EPD_W21_WriteDATA(0x1f);		 //LUT from OTP  
	  EPD_W21_WriteDATA(0x0d);     //VCOM to 0V fast,This data is necessary, please do not delete!!!

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (HRES);      	//152    	 
		EPD_W21_WriteDATA (VRES_byte1);	//152	
		EPD_W21_WriteDATA (VRES_byte2);

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}
void EPD_display_init(void)
{
	  HRES=0x98;						//152
	  VRES_byte1=0x00;			//152
	  VRES_byte2=0x98;
	  EPD_W21_Init();
		EPD_W21_WriteCMD(0x01);			//POWER SETTING 
		EPD_W21_WriteDATA (0x03);	          
		EPD_W21_WriteDATA (0x00);
		EPD_W21_WriteDATA (0x2b);
		EPD_W21_WriteDATA (0x2b);
		EPD_W21_WriteDATA (0x03);

		EPD_W21_WriteCMD(0x06);         //boost soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C       

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0xbf);		//LUT from OTP，128x296
		EPD_W21_WriteDATA(0x0d);		//VCOM to 0V fast
		
		EPD_W21_WriteCMD(0x30);			//PLL setting
    EPD_W21_WriteDATA (0x3c);   // 3a 100HZ   29 150Hz 39 200HZ	31 171HZ

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (HRES);        	 
		EPD_W21_WriteDATA (VRES_byte1);		
		EPD_W21_WriteDATA (VRES_byte2);
		
		EPD_W21_WriteCMD(0x82);			//vcom_DC setting  	
    EPD_W21_WriteDATA (0x12);	

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
	}
/***************************full display function*************************************/

	void EPD_full_display(const unsigned char *old_data,const unsigned char *new_data,unsigned char mode)// mode0:Refresh picture1,mode1:Refresh picture2... ,mode2:Clear
{		
		unsigned int i;
		
    if(mode==0)  //mode0:Refresh picture1
		{
			EPD_W21_WriteCMD(0x10);
			for(i=0;i<2888;i++)	     
			{
					EPD_W21_WriteDATA(0xff);  
			}  
			driver_delay_xms(2);
		  EPD_W21_WriteCMD(0x13);
			for(i=0;i<2888;i++)	     
			{
					EPD_W21_WriteDATA(new_data[i]);  
			}  
			driver_delay_xms(2);
	  }
		
		else if(mode==1)  //mode0:Refresh picture2...
		{
			EPD_W21_WriteCMD(0x10);
			for(i=0;i<2888;i++)	     
			{
					EPD_W21_WriteDATA(old_data[i]);  
			}  
			driver_delay_xms(2);
		  EPD_W21_WriteCMD(0x13);
			for(i=0;i<2888;i++)	     
			{
					EPD_W21_WriteDATA(new_data[i]);  
			}  
			driver_delay_xms(2);
	  }
		
   else 
		{
		  EPD_W21_WriteCMD(0x10);
			for(i=0;i<2888;i++)	     
			{
					EPD_W21_WriteDATA(old_data[i]);  
			}  
			driver_delay_xms(2);
			EPD_W21_WriteCMD(0x13);
			for(i=0;i<2888;i++)	     
			{
					EPD_W21_WriteDATA(0xff);  
			}  
			driver_delay_xms(2);
	  }	 

	  lut(); //Power settings
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	    //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}
	
	void PIC_display(void pic_display(void))
{
		lut(); //Power settings
		pic_display(); //picture
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	    //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
	
		pic_display(); //picture
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	    //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}
void PIC_display_Clean(void)
{
    unsigned int i;
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<2888;i++)	     
	{
	  EPD_W21_WriteDATA(0xff);
	}
	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<2888;i++)	     
	{
	  EPD_W21_WriteDATA(0xff);
	}
}
void EPD_refresh(void)
{
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	        //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}	
/***************************partial display function*************************************/

void EPD_partial_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end ,void partial_old(void),void partial_new(void)) //partial display
{
	  EPD_W21_WriteCMD(0x82);			//vcom_DC setting  	
    EPD_W21_WriteDATA (0x08);	
		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0x47);		
		lut1();
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end-1);	 //x-end	

		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start    
		
		EPD_W21_WriteDATA (y_end/256);		
		EPD_W21_WriteDATA (y_end%256-1);  //y-end
		EPD_W21_WriteDATA (0x28);	

		EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
		partial_old();
		EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
		partial_new();
    	
		EPD_W21_WriteCMD(0x12);		 //DISPLAY REFRESH 		             
		driver_delay_xms(10);     //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
	  
}

/////////////////////////////Enter deep sleep mode////////////////////////
void EPD_deep_sleep(void) //Enter deep sleep mode
{
		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0xf7);	
		EPD_W21_WriteCMD(0X02);  	//power off
		EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}

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
 
  // 复位RCC时钟配置(用于调试模式) 
  RCC_DeInit();
 
  // 使能外部晶振 
  RCC_HSEConfig(RCC_HSE_ON);
  
  // 等待外部晶振稳定 
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    // 设置锁相环频率PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  }
  else {
    // 使能内部晶振 
    RCC_HSICmd(ENABLE);
    // 等待内置振荡器稳定 
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // 设置锁相环频率PLLCLK = 8MHz/2 * 16 = 64 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
  }

    // 使能FLASH的预取缓冲 
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  //设置代码延时值,FLASH_Latency_2为两个延时周期
  FLASH_SetLatency(FLASH_Latency_2);
	
  //设置系统总线时钟
  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  //设置高速设备总线时钟，RCC_HCLK_Div1为系统时钟除以1
  RCC_PCLK2Config(RCC_HCLK_Div1); 

  //设置低速设备总线时钟，RCC_HCLK_Div2为系统时钟除以2
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //使能锁相环倍频
  RCC_PLLCmd(ENABLE);
  
  // 等待锁相环倍频后的频率稳定 
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  // 选择锁相环时钟为系统时钟源 
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  // 等待设置完成 
  while(RCC_GetSYSCLKSource() != 0x08);
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
            ENABLE);

}

/*******************************************************************************
* 函数名   : GPIO_Configuration
* 描述         : 设置设置串口所用GPIO引脚的参数
* 输入         : None
* 输出         : None
* 返回         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_14 |GPIO_Pin_15;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//测试LED灯功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;    //LED
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
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







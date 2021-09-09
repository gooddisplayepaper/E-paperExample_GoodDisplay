/***********************************************************
Copyright(C), Good Display
FileName	: main.c
Author		: Yukewantong, Zhongxiaodong
Date	  	: 2012/3/13
Description	: 
Version		: V1.0
History		: 
--------------------------------
2012/3/13: created
2012/9/21: Visionpeak MP test version
***********************************************************/
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

extern const unsigned char pic[4736];
extern const unsigned char pic5[5600];
extern const unsigned char pic0[224];
extern const unsigned char pic1[224];
extern const unsigned char pic2[224];
extern const unsigned char pic3[224];
extern const unsigned char pic4[224];

const unsigned char LUTDefault_part[31] = {
	0x32,	// command

/*	0x00,0x00,0x00,0x18,	
	0x18,0x18,0x18,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x40,0x14,0x34,0x01,
	0x00,0x00,0x00,0x00,
	0x00,0x00,
*/
 0x10 //C221 25C partial update waveform
,0x18
,0x18
,0x08
,0x18
,0x18
,0x08
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00
,0x13
,0x14
,0x44
,0x12
,0x00
,0x00
,0x00
,0x00
,0x00
,0x00

	};

const unsigned char LUTDefault_full[31] = {
	0x32,	// command
/*	0x11,0x11,0x10,0x02,	// full
	0x02,0x22,0x22,0x22,
	0x22,0x22,0x51,0x51,
	0x55,0x88,0x08,0x08,
    	0x88,0x88,0x00,0x00,
	0x34,0x23,0x12,0x21,
	0x24,0x28,0x22,0x21,
	0xA1,0x01
*/
 0x02 //C221 25C Full update waveform
,0x02
,0x01
,0x11
,0x12
,0x12
,0x22
,0x22
,0x66
,0x69
,0x69
,0x59
,0x58
,0x99
,0x99
,0x88
,0x00
,0x00
,0x00
,0x00
,0xF8
,0xB4
,0x13
,0x51
,0x35
,0x51
,0x51
,0x19
,0x01
,0x00
	};


void driver_delay_xms(unsigned long xms)	
{	
    unsigned int i = 0;

    while(xms)
    {
        for(; i<2100; i++);
        xms--;
    }    
}

void fulltest()
{
		EPD_W21_Init();	
		EPD_W21_WirteLUT((unsigned char *)LUTDefault_full);
	   	EPD_W21_POWERON();
   		
    		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0xFF);	// black
		driver_delay_xms(1000);

    		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0xFF);	// black
		EPD_W21_Update();
		driver_delay_xms(400000);
		driver_delay_xms(1000);
}

void fullparttest(void)
{
//		EPD_W21_Init();	
        EPD_W21_BS_0;
		EPD_W21_WirteLUT((unsigned char *)LUTDefault_part);
	   	EPD_W21_POWERON();
		//EPD_W21_SetRamArea(0x00,0x18,0xc7,0x00,0x00,0x00);	  
		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0xFF);	// white		
		//EPD_W21_Update1();
		//driver_delay_xms(400000);
		driver_delay_xms(10000);

		EPD_W21_WriteDispRamMono(200, 200, 0xFF);	// white		
		EPD_W21_Update1();
		driver_delay_xms(400000);
		driver_delay_xms(10000);

		//EPD_W21_SetRamArea(0x00,0x18,0xc7,0x00,0x00,0x00);	  
		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0x00);	// white		
		EPD_W21_Update1();
		driver_delay_xms(10000);
		driver_delay_xms(400000);

		EPD_W21_WriteDispRamMono(200, 200, 0x00);	// white		
		//EPD_W21_Update1();
		//driver_delay_xms(400000);
		driver_delay_xms(10000);


}

void parttest()
{
		//EPD_W21_Init();	
		EPD_W21_WirteLUT((unsigned char *)LUTDefault_part);
	   	EPD_W21_POWERON();
		EPD_W21_SetRamArea(0x00,0x18,0xc7,0x00,0x00,0x00);	  
		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0x00);	// white		
		driver_delay_xms(10000);

		EPD_W21_WriteDispRamMono(200, 200, 0x00);	// white		
		EPD_W21_Update1();
		driver_delay_xms(400000);
		driver_delay_xms(10000);


        part_display(0x00,0x03,0xc7,0x00,0x8f,0x00);	// set ram	
   		
		EPD_W21_UpdataDisplay((unsigned char *)pic0,32,56);
 		EPD_W21_Update1();
		driver_delay_xms(100000);
		part_display(0x00,0x03,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic0,32,56);
		driver_delay_xms(10000);
		
   		
		part_display(0x04,0x07,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic1,32,56);
 		EPD_W21_Update1();
		driver_delay_xms(100000);
		part_display(0x04,0x07,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic1,32,56);
		driver_delay_xms(10000);

		
		part_display(0x09,0x0c,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic2,32,56);
 		EPD_W21_Update1();
		driver_delay_xms(100000);
		part_display(0x09,0x0c,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic2,32,56);
		driver_delay_xms(10000);

   			
		part_display(0x0e,0x11,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic3,32,56);
 		EPD_W21_Update1();
		driver_delay_xms(100000);
		part_display(0x0e,0x11,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic3,32,56);
		driver_delay_xms(10000);

   			
		part_display(0x13,0x16,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic4,32,56);
		EPD_W21_Update1();
		driver_delay_xms(100000);
		part_display(0x13,0x16,0xc7,0x00,0x8f,0x00);	// set ram	
		EPD_W21_UpdataDisplay((unsigned char *)pic4,32,56);
		driver_delay_xms(10000);

   		
}

void EPD_W29_init(void)
{		
		EPD_W21_Init();			// display
		EPD_W21_WirteLUT((unsigned char *)LUTDefault_full);
	    EPD_W21_POWERON();
   		
    	EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0xFF);	// black
		driver_delay_xms(1000);

    	EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0xFF);	// black
		EPD_W21_Update();
		driver_delay_xms(400000);
		driver_delay_xms(1000);


		
		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0x00);	// white		
		EPD_W21_Update();

		driver_delay_xms(400000);
		driver_delay_xms(1000);
		EPD_W21_SetRamPointer(0x00,0xC7,0x00);	// set ram
		EPD_W21_WriteDispRamMono(200, 200, 0x00);	// white		
		driver_delay_xms(1000);
		parttest();
		//fullparttest();
		fulltest();
}


/***********************************************************
						end file
***********************************************************/

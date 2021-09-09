#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

void delay_xms(unsigned int xms)
{
	unsigned int i;
	while(xms--)
	{
		i=12000;
		while(i--);
	}
}
/////////////////////////////////////LUT//////////////////////////////////////////////
const unsigned char LUT_DATA[]= {
0x80,0x60,0x40,0x00,0x00,0x00,0x00,             //LUT0: BB:     VS 0 ~7
0x10,0x60,0x20,0x00,0x00,0x00,0x00,             //LUT1: BW:     VS 0 ~7
0x80,0x60,0x40,0x00,0x00,0x00,0x00,             //LUT2: WB:     VS 0 ~7
0x10,0x60,0x20,0x00,0x00,0x00,0x00,             //LUT3: WW:     VS 0 ~7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT4: VCOM:   VS 0 ~7

0x03,0x03,0x00,0x00,0x02,                       // TP0 A~D RP0
0x09,0x09,0x00,0x00,0x02,                       // TP1 A~D RP1
0x03,0x03,0x00,0x00,0x02,                       // TP2 A~D RP2
0x00,0x00,0x00,0x00,0x00,                       // TP3 A~D RP3
0x00,0x00,0x00,0x00,0x00,                       // TP4 A~D RP4
0x00,0x00,0x00,0x00,0x00,                       // TP5 A~D RP5
0x00,0x00,0x00,0x00,0x00,                       // TP6 A~D RP6

0x15,0x41,0xA8,0x32,0x30,0x0A,
};	

//////////////////////////////////waveform1
const unsigned char LUT_DATA_part[]={  //20 bytes


0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT0: BB:     VS 0 ~7
0x80,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT1: BW:     VS 0 ~7
0x40,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT2: WB:     VS 0 ~7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT3: WW:     VS 0 ~7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT4: VCOM:   VS 0 ~7

0x1A,0x00,0x00,0x00,0x00,                       // TP0 A~D RP0
0x00,0x00,0x00,0x00,0x00,                       // TP1 A~D RP1
0x00,0x00,0x00,0x00,0x00,                       // TP2 A~D RP2
0x00,0x00,0x00,0x00,0x00,                       // TP3 A~D RP3
0x00,0x00,0x00,0x00,0x00,                       // TP4 A~D RP4
0x00,0x00,0x00,0x00,0x00,                       // TP5 A~D RP5
0x00,0x00,0x00,0x00,0x00,                       // TP6 A~D RP6

0x15,0x41,0xA8,0x32,0x30,0x0A,
};
///////////4Gray///////////////////////

const unsigned char LUT_DATA_4Gray[] =   //76bytes

{						
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,
0x8,	0x48,	0x10,	0x0,	0x0,	0x0,	0x0,
0x2,	0x48,	0x4,	0x0,	0x0,	0x0,	0x0,
0x20,	0x48,	0x1,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0xA,	0x19,	0x3,	0x8,	0x0,		
0x14,	0x0,	0x14,	0x0,	0x3,		
0xA,	0x3,	0x8,	0x19,	0x0,		
0x0,	0x0,	0x0,	0x0,	0x0,		
0x0,	0x0,	0x0,	0x0,	0x4,		
0x0,	0x0,	0x0,	0x0,	0x0,		
0x0,	0x0,	0x0,	0x0,	0x6,		
0x17,	0x41,	0xAC,	0x32,			
0x2C,	0x0A
};	
void EPD_Display(unsigned char *Image)
{
    unsigned int Width, Height,i,j;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;

    EPD_W21_WriteCMD(0x24);
    for ( j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
           EPD_W21_WriteDATA(Image[i + j * Width]);
        }
    }
    EPD_Update();		 
}

void Epaper_Spi_WriteByte(unsigned char TxData)
{				   			 
	unsigned char TempData;
	unsigned char scnt;
	TempData=TxData;

  EPD_W21_CLK_0;  
	for(scnt=0;scnt<8;scnt++)
	{ 
		if(TempData&0x80)
		  EPD_W21_MOSI_1 ;
		else
		  EPD_W21_MOSI_0 ;
		EPD_W21_CLK_1;  
	  EPD_W21_CLK_0;  
		TempData=TempData<<1;

  }

}

void Epaper_READBUSY(void)
{ 
  while(1)
  {	 //=1 BUSY
     if(isEPD_W21_BUSY==0) break;;
  }  
}

void Epaper_Write_Command(unsigned char cmd)
{
	EPD_W21_CS_1;
	EPD_W21_CS_0;
	EPD_W21_DC_0;  // D/C#   0:command  1:data

	Epaper_Spi_WriteByte(cmd);
	EPD_W21_CS_1;
}

void Epaper_Write_Data(unsigned char data)
{
	EPD_W21_CS_1;
	EPD_W21_CS_0;
	EPD_W21_DC_1;  // D/C#   0:command  1:data

	Epaper_Spi_WriteByte(data);
	EPD_W21_CS_1;
}

void EPD_select_LUT(unsigned char * wave_data)
{        
     unsigned char count;
     Epaper_Write_Command(0x32);
	 for(count=0;count<70;count++)Epaper_Write_Data(wave_data[count]);

}	
	
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//SSD1675A
void EPD_HW_Init(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();
	Epaper_Write_Command(0x12); // soft reset
	Epaper_READBUSY();

	Epaper_Write_Command(0x74); //set analog block control       
	Epaper_Write_Data(0x54);
	Epaper_Write_Command(0x7E); //set digital block control          
	Epaper_Write_Data(0x3B);

	Epaper_Write_Command(0x01); //Driver output control      
	Epaper_Write_Data(0xF9);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00);

	Epaper_Write_Command(0x11); //data entry mode       
	Epaper_Write_Data(0x01);

	Epaper_Write_Command(0x44); //set Ram-X address start/end position   
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x0F);    //0x0C-->(15+1)*8=128

	Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
	Epaper_Write_Data(0xF9);   //0xF9-->(249+1)=250
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00); 

	Epaper_Write_Command(0x3C); //BorderWavefrom
	Epaper_Write_Data(0x03);	


	Epaper_Write_Command(0x2C);     //VCOM Voltage
	Epaper_Write_Data(0x70);    //

	Epaper_Write_Command(0x03); // Gate Driving Voltage Control     
	Epaper_Write_Data(LUT_DATA[70]);

	Epaper_Write_Command(0x04); // Source Driving Voltage Control          
	Epaper_Write_Data(LUT_DATA[71]);    
	Epaper_Write_Data(LUT_DATA[72]);    
	Epaper_Write_Data(LUT_DATA[73]);    


	Epaper_Write_Command(0x3A);     //Dummy Line 	 
	Epaper_Write_Data(LUT_DATA[74]);    
	Epaper_Write_Command(0x3B);     //Gate time 
	Epaper_Write_Data(LUT_DATA[75]);   

	EPD_select_LUT((unsigned char *)LUT_DATA); //LUT

	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(0x00);
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(0xF9);
	Epaper_Write_Data(0x00);
	Epaper_READBUSY();
	
}
void EPD_HW_Init_GUI(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();
	Epaper_Write_Command(0x12); // soft reset
	Epaper_READBUSY();

	Epaper_Write_Command(0x74); //set analog block control       
	Epaper_Write_Data(0x54);
	Epaper_Write_Command(0x7E); //set digital block control          
	Epaper_Write_Data(0x3B);

	Epaper_Write_Command(0x01); //Driver output control      
	Epaper_Write_Data(0x27);
	Epaper_Write_Data(0x01);
	Epaper_Write_Data(0x01);//Show mirror

	Epaper_Write_Command(0x11); //data entry mode       
	Epaper_Write_Data(0x01);

	Epaper_Write_Command(0x44); //set Ram-X address start/end position   
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x0F);    //0x0F-->(15+1)*8=128

	Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
	Epaper_Write_Data(0x27);   //0x0127-->(295+1)=296
	Epaper_Write_Data(0x01);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00); 

	Epaper_Write_Command(0x3C); //BorderWavefrom
	Epaper_Write_Data(0x03);	


	Epaper_Write_Command(0x2C);     //VCOM Voltage
	Epaper_Write_Data(0x70);    //

	Epaper_Write_Command(0x03); // Gate Driving Voltage Control     
	Epaper_Write_Data(LUT_DATA[70]);

	Epaper_Write_Command(0x04); // Source Driving Voltage Control          
	Epaper_Write_Data(LUT_DATA[71]);    
	Epaper_Write_Data(LUT_DATA[72]);    
	Epaper_Write_Data(LUT_DATA[73]);    


	Epaper_Write_Command(0x3A);     //Dummy Line 	 
	Epaper_Write_Data(LUT_DATA[74]);    
	Epaper_Write_Command(0x3B);     //Gate time 
	Epaper_Write_Data(LUT_DATA[75]);   

	EPD_select_LUT((unsigned char *)LUT_DATA); //LUT

	Epaper_Write_Command(0x4E);     
	Epaper_Write_Data(0x00);
	
	Epaper_Write_Command(0x4F);       
	Epaper_Write_Data(0x27);
	Epaper_Write_Data(0x01);
  Epaper_READBUSY();
}
void EPD_HW_Init_4GRAY(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 

	Epaper_READBUSY();
	Epaper_Write_Command(0x12); // soft reset
	Epaper_READBUSY();

	Epaper_Write_Command(0x74); //set analog block control       
	Epaper_Write_Data(0x54);
	Epaper_Write_Command(0x7E); //set digital block control          
	Epaper_Write_Data(0x3B);
//
    Epaper_Write_Command(0x2B); //set reduce glitch
    Epaper_Write_Data(0x04);
    Epaper_Write_Data(0x63);

    Epaper_Write_Command(0x0C); //set soft start     
    Epaper_Write_Data(0x8B);
    Epaper_Write_Data(0x9C);
    Epaper_Write_Data(0x96);
    Epaper_Write_Data(0x0F);
	//
	Epaper_Write_Command(0x01); //Driver output control      
	Epaper_Write_Data(0xF9);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00);

	Epaper_Write_Command(0x11); //data entry mode       
	Epaper_Write_Data(0x01);

	Epaper_Write_Command(0x44); //set Ram-X address start/end position   
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x0F);    //0x0C-->(15+1)*8=128

	Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
	Epaper_Write_Data(0xF9);   //0xF9-->(249+1)=250
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00);
	Epaper_Write_Data(0x00); 

	Epaper_Write_Command(0x3C); //BorderWavefrom
	Epaper_Write_Data(0x00);	


	Epaper_Write_Command(0x2C);     //VCOM Voltage
	Epaper_Write_Data(0x1C);    //0x1C

	Epaper_Write_Command(0x03); //      
	Epaper_Write_Data(LUT_DATA_4Gray[70]);

	Epaper_Write_Command(0x04); //      
	Epaper_Write_Data(LUT_DATA_4Gray[71]);    
	Epaper_Write_Data(LUT_DATA_4Gray[72]);    
	Epaper_Write_Data(LUT_DATA_4Gray[73]);    


	Epaper_Write_Command(0x3A);     //Dummy Line 	 
	Epaper_Write_Data(LUT_DATA_4Gray[74]);    
	Epaper_Write_Command(0x3B);     //Gate time 
	Epaper_Write_Data(LUT_DATA_4Gray[75]);   

	EPD_select_LUT((unsigned char *)LUT_DATA_4Gray); //LUT

	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(0x00);
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(0xF9);
	Epaper_Write_Data(0x00);
	Epaper_READBUSY();

}



u8 In2bytes_Out1byte_RAM1(u8 data1,u8 data2)
{
  u32 i; 
  u8 TempData1,TempData2;
	u8 outdata=0x00;
TempData1=data1;
TempData2=data2;
	
    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
        if( ((TempData1&0xC0)==0xC0) || ((TempData1&0xC0)==0x40))
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData1=TempData1<<2;

        //delay_us(5) ; 
     }

    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
         if((TempData2&0xC0)==0xC0||(TempData2&0xC0)==0x40)
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData2=TempData2<<2;

       // delay_us(5) ; 
     }
		 return outdata;
}
u8 In2bytes_Out1byte_RAM2(u8 data1,u8 data2)
{
  u32 i; 
  u8 TempData1,TempData2;
	u8 outdata=0x00;
TempData1=data1;
TempData2=data2;
	
    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
        if( ((TempData1&0xC0)==0xC0) || ((TempData1&0xC0)==0x80))
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData1=TempData1<<2;

       // delay_us(5) ; 
     }

    for(i=0;i<4;i++)
     { 
        outdata=outdata<<1;
         if((TempData2&0xC0)==0xC0||(TempData2&0xC0)==0x80)
           outdata=outdata|0x01;
        else 
          outdata=outdata|0x00;

        TempData2=TempData2<<2;

        //delay_us(5) ; 
     }
		 return outdata;
}

//The picture needs to be made into 250x128 resolution
void EPD_WhiteScreen_ALL_4GRAY(const unsigned char *datas)
{
   unsigned int i;
	 u8 tempOriginal;   
	
	
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<4000*2;i+=2)
   {               
		tempOriginal= In2bytes_Out1byte_RAM1( *(datas+i),*(datas+i+1));
		 Epaper_Write_Data(~tempOriginal); 
   }
	 
	 Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<4000*2;i+=2)
   {               
		tempOriginal= In2bytes_Out1byte_RAM2( *(datas+i),*(datas+i+1));
		 Epaper_Write_Data(~tempOriginal); 
   }
   EPD_Update();	 
}
/////////////////////////////////////////////////////////////////////////////////////////
/*When the electronic paper screen is updated, do not unplug the electronic paper to avoid damage to the screen*/

void EPD_Update(void)
{   
  Epaper_Write_Command(0x22); //Display Update Control
  Epaper_Write_Data(0xC7);   
  Epaper_Write_Command(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}
/*When the electronic paper screen is updated, do not unplug the electronic paper to avoid damage to the screen*/
void EPD_Part_Update(void)
{
	Epaper_Write_Command(0x22); //Display Update Control
	Epaper_Write_Data(0x0C);   
	Epaper_Write_Command(0x20); //Activate Display Update Sequence
	Epaper_READBUSY(); 			
}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(const unsigned char *datas)
{
   unsigned int i;	
  Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<4000;i++)
   {               
     Epaper_Write_Data(*datas);
			datas++;
   }
   EPD_Update();	 
}
///////////////////////////Part update//////////////////////////////////////////////
//The x axis is reduced by one byte, and the y axis is reduced by one pixel.
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
	unsigned int i;   
	const unsigned char  *datas_flag;   
	datas_flag=datas;

	
  Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<4000;i++)
   {               
     Epaper_Write_Data(*datas);
			datas++;
   }
	 datas=datas_flag;
  Epaper_Write_Command(0x26);   //Write Black and White image to RAM
   for(i=0;i<4000;i++)
   {               
     Epaper_Write_Data(*datas);
			datas++;
   }
   EPD_Update();	
   EPD_Part_Init();	  
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

  Epaper_Write_Command(0x22); //Display Update Control
  Epaper_Write_Data(0xC0);   
  Epaper_Write_Command(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();  
	
//  Epaper_Write_Command(0x3C); //BorderWavefrom
//	Epaper_Write_Data(0x01);

}
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	x_start=x_start/8;
	x_end=x_start+PART_LINE/8-1; 
	
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
     Epaper_Write_Data(*datas);
			datas++;
   } 
	 EPD_Part_Update();

}

void EPD_DeepSleep(void)
{  	
  Epaper_Write_Command(0x10); //enter deep sleep
  Epaper_Write_Data(0x01); 
  delay_xms(100);
}


/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_White(void)

{
   unsigned int i,k;
	 Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
	for(k=0;k<250;k++)
  {
		for(i=0;i<25;i++)
		{
			Epaper_Write_Data(0xff);
			}
  }
	EPD_Update();
}

/////////////////////////////////////TIME///////////////////////////////////////////////////
void EPD_Dis_Part_myself(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      )
{
	unsigned int i;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	
	//Data A////////////////////////////
	x_startA=x_startA/8;//Convert to byte
	x_end=x_startA+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startA-1;
	if(y_startA>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startA+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
	Epaper_Write_Data(x_startA);    // RAM x address start at 00h;
	Epaper_Write_Data(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
	Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
	Epaper_Write_Data(y_end1);    


	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(x_startA); 
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(y_start2);
	Epaper_Write_Data(y_start1);
	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     Epaper_Write_Data(*datasA);
			datasA++;
   } 
	//Data B/////////////////////////////////////
	x_startB=x_startB/8;//Convert to byte
	x_end=x_startB+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startB-1;
	if(y_startB>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startB+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
	Epaper_Write_Data(x_startB);    // RAM x address start at 00h;
	Epaper_Write_Data(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
	Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
	Epaper_Write_Data(y_end1);   


	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(x_startB); 
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(y_start2);
	Epaper_Write_Data(y_start1);
	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     Epaper_Write_Data(*datasB);
			datasB++;
   } 	 
	 
	//Data C//////////////////////////////////////
	x_startC=x_startC/8;//Convert to byte
	x_end=x_startC+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startC-1;
	if(y_startC>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startC+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
	Epaper_Write_Data(x_startC);    // RAM x address start at 00h;
	Epaper_Write_Data(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
	Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
	Epaper_Write_Data(y_end1);   


	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(x_startC); 
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(y_start2);
	Epaper_Write_Data(y_start1);
	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     Epaper_Write_Data(*datasC);
			datasC++;
   } 	 	 
 	 
	//Data D//////////////////////////////////////
	x_startD=x_startD/8;//Convert to byte
	x_end=x_startD+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startD-1;
	if(y_startD>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startD+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
	Epaper_Write_Data(x_startD);    // RAM x address start at 00h;
	Epaper_Write_Data(x_end);        // RAM x address end at 0fh(15+1)*8->128 
	Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
	Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
	Epaper_Write_Data(y_end1);    


	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(x_startD); 
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(y_start2);
	Epaper_Write_Data(y_start1);
	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     Epaper_Write_Data(*datasD);
			datasD++;
   } 
	//Data E//////////////////////////////////////
	x_startE=x_startE/8;//Convert to byte
	x_end=x_startE+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startE-1;
	if(y_startE>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startE+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
	Epaper_Write_Data(x_startE);    // RAM x address start at 00h;
	Epaper_Write_Data(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
	Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
	Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
	Epaper_Write_Data(y_end1);    


	Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
	Epaper_Write_Data(x_startE); 
	Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
	Epaper_Write_Data(y_start2);
	Epaper_Write_Data(y_start1);
	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     Epaper_Write_Data(*datasE);
			datasE++;
   } 	  
	 EPD_Part_Update();

}

/***********************************************************
						end file
***********************************************************/


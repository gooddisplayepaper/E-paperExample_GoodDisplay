#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"


unsigned char oldData[4736];
/*------------------4GRAY  LUT-----------------*/
const unsigned char lut_vcom[] ={	
0x00,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x00,	0x23,	0x01,	0x23,	0x00,	0x02,	
0x00,	0x05,	0x07,	0x00,	0x00,	0x01,	
0x00,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x00,	0x05,	0x07,	0x00,	0x00,	0x01,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
										
const unsigned char lut_ww[] ={	
0x50,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x48,	0x23,	0x01,	0x23,	0x00,	0x02,	
0x50,	0x05,	0x07,	0x00,	0x00,	0x01,	
0xA0,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0xA0,	0x05,	0x07,	0x00,	0x00,	0x01,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_bw[] ={	
0x50,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x48,	0x23,	0x01,	0x23,	0x00,	0x02,	
0x20,	0x05,	0x07,	0x00,	0x00,	0x01,	
0xA0,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x10,	0x05,	0x07,	0x00,	0x00,	0x01,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_wb[] ={	
0x50,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x48,	0x23,	0x01,	0x23,	0x00,	0x02,	
0x80,	0x05,	0x07,	0x00,	0x00,	0x01,	
0xA0,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
0x40,	0x05,	0x07,	0x00,	0x00,	0x01,	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_bb[] ={	
	0xA0,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
	0x48,	0x23,	0x01,	0x23,	0x00,	0x02,	
	0xA0,	0x05,	0x07,	0x00,	0x00,	0x01,	
	0x50,	0x0A,	0x0A,	0x00,	0x00,	0x01,	
	0x50,	0x05,	0x07,	0x00,	0x00,	0x01,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};

/*------------------PARTIAL  LUT-----------------*/
const unsigned char lut_vcom1[] ={	
	0x00,	0x01,	0x20,	0x01,	0x00,	0x01,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_ww1[] ={	
	0x00,	0x01,	0x20,	0x01,	0x00,	0x01,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_bw1[] ={	
	0x20,	0x01,	0x20,	0x01,	0x00,	0x01,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_wb1[] ={	
	0x10,	0x01,	0x20,	0x01,	0x00,	0x01,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
};
							
							
							
const unsigned char lut_bb1[] ={	
	0x00,	0x01,	0x20,	0x01,	0x00,	0x01,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	
	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
};


void delay_xms(unsigned int xms)
{
	unsigned int i;
	while(xms--)
	{
		i=12000;
		while(i--);
	}
}

void EPD_W21_Init(void)
{
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 

	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 

	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	
}

void EPD_Display(unsigned char *Image)
{
    unsigned int Width, Height,i,j;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;

    EPD_W21_WriteCMD(0x10);
    for (j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
            EPD_W21_WriteDATA(0x00);
        }
    }

    EPD_W21_WriteCMD(0x13);
    for ( j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
           EPD_W21_WriteDATA(Image[i + j * Width]);
        }
    }
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		delay_xms(1);	    //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}
//UC8151D
void EPD_init(void)
{	
		EPD_W21_Init(); //Electronic paper IC reset
    
		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();//waiting for the electronic paper IC to release the idle signal

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x1f);		//LUT from OTP£¬KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}


/*----------------4GRAY------------------*/
void lut(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x20);
	for(count=0;count<36;count++)	     
		{EPD_W21_WriteDATA(lut_vcom[count]);}

	EPD_W21_WriteCMD(0x21);
	for(count=0;count<36;count++)	     
		{EPD_W21_WriteDATA(lut_ww[count]);}   
	
	EPD_W21_WriteCMD(0x22);
	for(count=0;count<36;count++)	     
		{EPD_W21_WriteDATA(lut_bw[count]);} 

	EPD_W21_WriteCMD(0x23);
	for(count=0;count<36;count++)	     
		{EPD_W21_WriteDATA(lut_wb[count]);} 

	EPD_W21_WriteCMD(0x24);
	for(count=0;count<36;count++)	     
		{EPD_W21_WriteDATA(lut_bb[count]);} 
}

//UC8151D
void EPD_init_4GRAY(void)
{
	  EPD_W21_Init();
		EPD_W21_WriteCMD(0x01);			//POWER SETTING 
		EPD_W21_WriteDATA (0x03);	          
		EPD_W21_WriteDATA (0x00);
		EPD_W21_WriteDATA (0x2b);
		EPD_W21_WriteDATA (0x2b);

		EPD_W21_WriteCMD(0x06);         //boost soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C       

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0xbf);		//KW-bf   KWR-2F	BWROTP 0f	BWOTP 1f
	
		EPD_W21_WriteCMD(0x30);			
    EPD_W21_WriteDATA (0x3C);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (0x80);   //128    	 
		EPD_W21_WriteDATA (0x01);		//296
		EPD_W21_WriteDATA (0x28);
		
	  EPD_W21_WriteCMD(0x82);			//vcom_DC setting  	
    EPD_W21_WriteDATA (0x12);	
		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0x97);		
		lut();	
	}	
//4 GRAYscale demo function
/********Color display description
      white  GRAY1  GRAY2  black
0x10|  01     01     00     00
0x13|  01     00     01     00
                                   ****************/
void PIC_display_4GRAY(const unsigned char *DATA_4GRAY)
{
  u32 i,j;
	u8 temp1,temp2,temp3;

	  //old  data
		EPD_W21_WriteCMD(0x10);	       

		for(i=0;i<4736;i++)	               //4736*4  296*128
		{ 
			temp3=0;
      for(j=0;j<4;j++)	
			{
				temp1 = DATA_4GRAY[i*4+j];
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)
					temp3 |= 0x01;//white
				else if(temp2 == 0x00)
					temp3 |= 0x00;  //black
				else if((temp2>0xA0)&&(temp2<0xF0)) 
					temp3 |= 0x01;  //GRAY1
				else 
					temp3 |= 0x00; //GRAY2
				temp3 <<= 1;	
				temp1 <<= 4;
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)  //white
					temp3 |= 0x01;
				else if(temp2 == 0x00) //black
					temp3 |= 0x00;
				else if((temp2>0xA0)&&(temp2<0xF0))
					temp3 |= 0x01; //GRAY1
				else    
						temp3 |= 0x00;	//GRAY2	
        if(j!=3)					
			  temp3 <<= 1;	
				
			
		 }	
       	EPD_W21_WriteDATA(temp3);			
		}
    //new  data
		EPD_W21_WriteCMD(0x13);	       

		for(i=0;i<4736;i++)	               //4736*4    296*128
		{ 
			temp3=0;
      for(j=0;j<4;j++)	
			{
				temp1 = DATA_4GRAY[i*4+j];
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)
					temp3 |= 0x01;//white
				else if(temp2 == 0x00)
					temp3 |= 0x00;  //black
				else if((temp2>0xA0)&&(temp2<0xF0)) 
					temp3 |= 0x00;  //GRAY1
				else 
					temp3 |= 0x01; //GRAY2
				temp3 <<= 1;	
				temp1 <<= 4;
				temp2 = temp1&0xF0 ;
				if(temp2 == 0xF0)  //white
					temp3 |= 0x01;
				else if(temp2 == 0x00) //black
					temp3 |= 0x00;
				else if((temp2>0xA0)&&(temp2<0xF0)) 
					temp3 |= 0x00;//GRAY1
				else    
						temp3 |= 0x01;	//GRAY2
        if(j!=3)				
			  temp3 <<= 1;				
			
		 }	
       	EPD_W21_WriteDATA(temp3);			
		}
		
	 //Refresh
		EPD_W21_WriteCMD(0x12);		 //DISPLAY REFRESH 		             
		delay_xms(10);     //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();		
}
/*----------------PARTIAL------------------*/
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

//UC8151D
void EPD_init_LUT(void)
{
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
		EPD_W21_WriteDATA(0xbf);		//KW-bf   KWR-2F	BWROTP 0f	BWOTP 1f
		
		EPD_W21_WriteCMD(0x30);			
    EPD_W21_WriteDATA (0x3C);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (0x80);   //128    	 
		EPD_W21_WriteDATA (0x01);		//296
		EPD_W21_WriteDATA (0x28);
		
	  EPD_W21_WriteCMD(0x82);			//vcom_DC setting  	
    EPD_W21_WriteDATA (0x12);	
		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0x47);		
		lut1();	
	}	
void EPD_sleep(void)
{
		EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0xf7); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	

		EPD_W21_WriteCMD(0X02);  	//power off
	  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
		EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}



void PIC_display(const unsigned char* picData)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<4736;i++)	  
    {	
	  EPD_W21_WriteDATA(0xff); 
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<4736;i++)	     
	  {
	  EPD_W21_WriteDATA(*picData);  //Transfer the actual displayed data
	  picData++;
	  }
	 //Refresh
	  EPD_W21_WriteCMD(0x12);		//DISPLAY REFRESH 	
		delay_xms(1);	  //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal


}
void PIC_display_Clear(void)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<4736;i++)	  
    {	
	  EPD_W21_WriteDATA(0xFF); 
    }
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<4736;i++)	     
	  {
	  EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
	  }
		//Refresh
  	EPD_W21_WriteCMD(0x12);		//DISPLAY REFRESH 	
		delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

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
}

void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode) //mode 0: first  1: other...
{
unsigned int datas,i;
unsigned int x_end,y_end;
	x_end=x_start+PART_LINE-1; 
  y_end=y_start+PART_COLUMN-1;
	datas=PART_LINE*PART_COLUMN/8;

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
		for(i=0;i<datas;i++)	     
		 {
			 if(mode==0)
			EPD_W21_WriteDATA(0x00); 
       else
 			EPD_W21_WriteDATA(~oldData[i]); 	 
		 }  
 
		EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
		for(i=0;i<datas;i++)	     
	 {
		EPD_W21_WriteDATA(~new_data[i]);
    oldData[i]=new_data[i]; 			 
	 } 
	 //Refresh
		EPD_W21_WriteCMD(0x12);		 //DISPLAY REFRESH 		             
		delay_xms(10);     //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
	  
}













/***********************************************************
						end file
***********************************************************/


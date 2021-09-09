
/***********************************************************/
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"


void EPD_W21_Init(void)
{
	EPD_W21_BS_0;		// 4 wire spi mode selected

	EPD_W21_RST_0;		// Module reset
	driver_delay_xms(1000);
	EPD_W21_RST_1;
	driver_delay_xms(1000);
	
//	EPD_W21_DispInit();		// pannel configure

//	EPD_W21_WirteLUT(LUTDefault);	// update wavefrom

}

/***********************************************************
						end file
***********************************************************/


#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	



//Tips//
/*
1.When the e-paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
2.When the partial refresh is performed, the screen does not flash.
3.After the e-paper is refreshed, you need to put it into sleep mode, please do not delete the sleep command.
4.Please do not take out the electronic paper when power is on.
5.Wake up from sleep, need to re-initialize the e-paper.
6.When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode.
*/
int	main(void)
{
		delay_init();	    	     //Delay function initialization
		NVIC_Configuration(); 	//Set NVIC interrupt grouping 2
    EPD_GPIO_Init();       //EPD GPIO  initialization
	while(1)
	{
    EPD_init(); //EPD init
	  PIC_display(gImage_BW,gImage_R);//EPD_picture1
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(3); //3s	
		
		//Clear
		EPD_init(); //EPD init
	  PIC_display_Clear();//EPD Clear
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(3); //3s	
		while(1);
		
	}
}	



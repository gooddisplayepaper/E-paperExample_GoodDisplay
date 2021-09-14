#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	
//GUI
#include "GUI_Paint.h"
#include "fonts.h"

unsigned char BlackImage[48000];//Define canvas space  

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
  ///////////////////////////Normal picture display/////////////////////////////////////////////////////////////////
		/************Normal picture display*******************/
    EPD_init(); //EPD init
	  PIC_display(gImage_1);//EPD_picture1
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(2); //2s	
		
		//Clear
		EPD_init(); //EPD init
	  PIC_display_Clear();//EPD Clear
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(2); //2s	
		
		
		
		
  ///////////////////////////GUI///////////////////////////////////////////////////////////////////////////////////
   //Data initialization settings
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set screen size and display orientation
    Paint_SelectImage(BlackImage);//Set the virtual canvas data storage location

    /**************Drawing**********************/
		EPD_init(); //EPD init
		Paint_Clear(WHITE);
		//Point   
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
		//Line
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(170, 15, 170, 55, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(150, 35, 190, 35, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
		//Rectangle
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    //Circle
		Paint_DrawCircle(300, 300, 150, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(500, 300, 150, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    EPD_Display(BlackImage);//display image
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!    
    delay_s(2); //2s		
		
    /***********String***************************/ 
		EPD_init(); //EPD init
		Paint_Clear(WHITE);
    Paint_DrawString_EN(0, 0, "Good Display", &Font8, WHITE, BLACK);  //5*8
		Paint_DrawString_EN(0, 10, "Good Display", &Font12, WHITE, BLACK); //7*12
		Paint_DrawString_EN(0, 25, "Good Display", &Font16, WHITE, BLACK); //11*16
		Paint_DrawString_EN(0, 45, "Good Display", &Font20, WHITE, BLACK); //14*20
		Paint_DrawString_EN(0, 70, "Good Display", &Font24, WHITE, BLACK); //17*24
		
	  Paint_DrawString_EN(180, 200, "Good Display", &Font8, WHITE, BLACK);  //5*8
		Paint_DrawString_EN(180, 210, "Good Display", &Font12, WHITE, BLACK); //7*12
		Paint_DrawString_EN(180, 225, "Good Display", &Font16, WHITE, BLACK); //11*16
		Paint_DrawString_EN(180, 245, "Good Display", &Font20, WHITE, BLACK); //14*20
		Paint_DrawString_EN(180, 270, "Good Display", &Font24, WHITE, BLACK); //17*24
		
	  Paint_DrawString_EN(500, 380, "Good Display", &Font8, WHITE, BLACK);  //5*8
		Paint_DrawString_EN(500, 390, "Good Display", &Font12, WHITE, BLACK); //7*12
		Paint_DrawString_EN(500, 405, "Good Display", &Font16, WHITE, BLACK); //11*16
		Paint_DrawString_EN(500, 425, "Good Display", &Font20, WHITE, BLACK); //14*20
		Paint_DrawString_EN(500, 450, "Good Display", &Font24, WHITE, BLACK); //17*24
    EPD_Display(BlackImage); //display image
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay_s(2); //2s		
		/*************Number************************/
		EPD_init(); //EPD init
		Paint_Clear(WHITE);
    Paint_DrawNum(0, 0, 123456789, &Font8, WHITE, BLACK);  //5*8
		Paint_DrawNum(0, 10, 123456789, &Font12, WHITE, BLACK); //7*12
		Paint_DrawNum(0, 25, 123456789, &Font16, WHITE, BLACK); //11*16
		Paint_DrawNum(0, 45, 123456789, &Font20, WHITE, BLACK); //14*20
		Paint_DrawNum(0, 70, 123456789, &Font24, WHITE, BLACK); //17*24
		
	  Paint_DrawNum(220, 200, 123456789, &Font8, WHITE, BLACK);  //5*8
		Paint_DrawNum(220, 210, 123456789, &Font12, WHITE, BLACK); //7*12
		Paint_DrawNum(220, 225, 123456789, &Font16, WHITE, BLACK); //11*16
		Paint_DrawNum(220, 245, 123456789, &Font20, WHITE, BLACK); //14*20
		Paint_DrawNum(220, 270, 123456789, &Font24, WHITE, BLACK); //17*24
		
	  Paint_DrawNum(500, 380, 123456789, &Font8, WHITE, BLACK);  //5*8
		Paint_DrawNum(500, 390, 123456789, &Font12, WHITE, BLACK); //7*12
		Paint_DrawNum(500, 405, 123456789, &Font16, WHITE, BLACK); //11*16
		Paint_DrawNum(500, 425, 123456789, &Font20, WHITE, BLACK); //14*20
		Paint_DrawNum(500, 450, 123456789, &Font24, WHITE, BLACK); //17*24
    EPD_Display(BlackImage); //display image
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay_s(2); //2s	 			

		//Clear
		EPD_init(); //EPD init
	  PIC_display_Clear();//EPD Clear
		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
		delay_s(2); //2s	
		while(1);
	}
}	



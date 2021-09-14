#ifndef EPD7IN5_H
#define EPD7IN5_H

#include "epdif.h"
#include <bcm2835.h>



// Display resolution
#define EPD_WIDTH      1304
#define EPD_HEIGHT      984
//CS
#define EPD_W21_CS_M1_0  DigitalWrite(CSB_M1, LOW) //PIN_12
#define EPD_W21_CS_M1_1  DigitalWrite(CSB_M1, HIGH)

#define EPD_W21_CS_S1_0  DigitalWrite(CSB_S1, LOW) //PIN_38
#define EPD_W21_CS_S1_1  DigitalWrite(CSB_S1, HIGH)

#define EPD_W21_CS_M2_0  DigitalWrite(CSB_M2, LOW) //PIN_13
#define EPD_W21_CS_M2_1  DigitalWrite(CSB_M2, HIGH)

#define EPD_W21_CS_S2_0   DigitalWrite(CSB_S2, LOW) //PIN_7
#define EPD_W21_CS_S2_1   DigitalWrite(CSB_S2, HIGH)

//RST
#define EPD_W21_RST_M1_0  DigitalWrite(RST_M1, LOW) //PIN_18
#define EPD_W21_RST_M1_1  DigitalWrite(RST_M1, HIGH)

#define EPD_W21_RST_M2_0  DigitalWrite(RST_M2, LOW)  //PIN_13
#define EPD_W21_RST_M2_1  DigitalWrite(RST_M2, HIGH)
//DC
#define EPD_W21_DC_M1_0  DigitalWrite(DC_M1, LOW) //PIN_36
#define EPD_W21_DC_M1_1  DigitalWrite(DC_M1, HIGH)

#define EPD_W21_DC_M2_0  DigitalWrite(DC_M2, LOW) //PIN_15
#define EPD_W21_DC_M2_1  DigitalWrite(DC_M2, HIGH)

//SCL
#define EPD_W21_SCL_0   DigitalWrite(SCL, LOW)////PIN_31
#define EPD_W21_SCL_1   DigitalWrite(SCL, HIGH)
//SDA
#define EPD_W21_SDA_0   DigitalWrite(SDI, LOW)//PIN_29
#define EPD_W21_SDA_1   DigitalWrite(SDI, HIGH)


//read SDA
#define EPD_W21_ReadDATA_SDA DigitalRead(SDI) //PIN_29

//BUSY
#define EPD_W21_ReadDATA_M1  DigitalRead(BUSY_M1) //PIN_16
#define EPD_W21_ReadDATA_M2  DigitalRead(BUSY_M2) //PIN_11
#define EPD_W21_ReadDATA_S1  DigitalRead(BUSY_S1) //PIN_40
#define EPD_W21_ReadDATA_S2  DigitalRead(BUSY_S2) //PIN_35


//GPIO--IO IN/OUT
#define SDI_IN  bcm2835_gpio_fsel(SDI, BCM2835_GPIO_FSEL_INPT) //GPIO mode flip  0:INPUT,1:OUTPUT
#define SDI_OUT bcm2835_gpio_fsel(SDI, BCM2835_GPIO_FSEL_OUTP) //GPIO mode flip  0:INPUT,1:OUTPUT


/*
// EPD7IN5 commands
#define PANEL_SETTING                               0x00
#define POWER_SETTING                               0x01
#define POWER_OFF                                   0x02
#define POWER_OFF_SEQUENCE_SETTING                  0x03
#define POWER_ON                                    0x04
#define POWER_ON_MEASURE                            0x05
#define BOOSTER_SOFT_START                          0x06
#define DEEP_SLEEP                                  0x07
#define DATA_START_TRANSMISSION_1                   0x10
#define DATA_STOP                                   0x11
#define DISPLAY_REFRESH                             0x12
#define IMAGE_PROCESS                               0x13
#define LUT_FOR_VCOM                                0x20 
#define LUT_BLUE                                    0x21
#define LUT_WHITE                                   0x22
#define LUT_GRAY_1                                  0x23
#define LUT_GRAY_2                                  0x24
#define LUT_RED_0                                   0x25
#define LUT_RED_1                                   0x26
#define LUT_RED_2                                   0x27
#define LUT_RED_3                                   0x28
#define LUT_XON                                     0x29
#define PLL_CONTROL                                 0x30
#define TEMPERATURE_SENSOR_COMMAND                  0x40
#define TEMPERATURE_CALIBRATION                     0x41
#define TEMPERATURE_SENSOR_WRITE                    0x42
#define TEMPERATURE_SENSOR_READ                     0x43
#define VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define LOW_POWER_DETECTION                         0x51
#define TCON_SETTING                                0x60
#define TCON_RESOLUTION                             0x61
#define SPI_FLASH_CONTROL                           0x65
#define REVISION                                    0x70
#define GET_STATUS                                  0x71
#define AUTO_MEASUREMENT_VCOM                       0x80
#define READ_VCOM_VALUE                             0x81
#define VCM_DC_SETTING                              0x82

extern const unsigned char lut_vcom0[];
extern const unsigned char lut_ww[];
extern const unsigned char lut_bw[];
extern const unsigned char lut_bb[];
extern const unsigned char lut_wb[];
*/
class Epd : EpdIf {
public:
    int width;
    int height;

    Epd();
    ~Epd();
    int  Init(void);
    void WaitUntilIdle(void);
    void Reset(void);
    void DisplayFrame(const unsigned char* frame_buffer);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void Sleep(void);

   //1248
    void SPI_Delay(unsigned char xrate);
	void SPI_Write(unsigned char value);
	void EPD_W21_WriteCMD_M1(unsigned char command);
	void EPD_W21_WriteCMD_S1(unsigned char command);
	void EPD_W21_WriteCMD_M2(unsigned char command);
	void EPD_W21_WriteCMD_S2(unsigned char command);
	void EPD_W21_WriteDATA_M1(unsigned char command);
	void EPD_W21_WriteDATA_S1(unsigned char command);
	void EPD_W21_WriteDATA_M2(unsigned char command);
	void EPD_W21_WriteDATA_S2(unsigned char command);
	void EPD_W21_WriteCMD_ALL(unsigned char command);
	void EPD_W21_WriteDATA_ALL(unsigned char command);
	void EPD_W21_WriteCMD_M1M2(unsigned char command);
	void EPD_W21_WriteDATA_M1M2(unsigned char command);
	//EPD init
	void EPD_W21_Init(void);
	//EPD Read
	unsigned char EPD_W21_ReadDATA_M1_temp(void);

	//EPD
	void EPD_init(void);
	void pic_display1(void);
	void pic_display_white(void);   
	void EPD_sleep(void);
	void EPD_refresh(void);
	void lcd_chkstatus_M1(void);
	void lcd_chkstatus_S1(void);
	void lcd_chkstatus_M2(void);
	void lcd_chkstatus_S2(void);
          

private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;


};

#endif /* EPD7IN5_H */

/* END OF FILE */

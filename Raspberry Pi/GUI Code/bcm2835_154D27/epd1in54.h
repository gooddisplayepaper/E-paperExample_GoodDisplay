#ifndef EPD1IN54_H
#define EPD1IN54_H

#include "epdif.h"
#define  DKE154  
#define  MONO 1  
#define  RED  1  


#ifdef DKE154
#define EPD_WIDTH       200
#define EPD_HEIGHT      200
#define MAX_LINE_BYTES    25
#define MAX_COLUMN_BYTES    200
#define ALLSCREEN_BYTES   5000
#endif

#ifdef DKE213_1
#define EPD_WIDTH       122
#define EPD_HEIGHT      250
#define MAX_LINE_BYTES    16
#define MAX_COLUMN_BYTES   250
#define ALLSCREEN_BYTES   4000
#endif

#ifdef DKE290
#define EPD_WIDTH       128
#define EPD_HEIGHT      296
#define MAX_LINE_BYTES     16
#define MAX_COLUMN_BYTES   296
#define ALLSCREEN_BYTES   4736
#endif

// EPD1IN54 commands
#define DRIVER_OUTPUT_CONTROL                       0x01
#define BOOSTER_SOFT_START_CONTROL                  0x0C
#define GATE_SCAN_START_POSITION                    0x0F
#define DEEP_SLEEP_MODE                             0x10
#define DATA_ENTRY_MODE_SETTING                     0x11
#define SW_RESET                                    0x12
#define TEMPERATURE_SENSOR_CONTROL                  0x1A
#define MASTER_ACTIVATION                           0x20
#define DISPLAY_UPDATE_CONTROL_1                    0x21
#define DISPLAY_UPDATE_CONTROL_2                    0x22
#define WRITE_RAM                                   0x24
#define WRITE_VCOM_REGISTER                         0x2C
#define WRITE_LUT_REGISTER                          0x32
#define SET_DUMMY_LINE_PERIOD                       0x3A
#define SET_GATE_TIME                               0x3B
#define BORDER_WAVEFORM_CONTROL                     0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION        0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION        0x45
#define SET_RAM_X_ADDRESS_COUNTER                   0x4E
#define SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#define TERMINATE_FRAME_READ_WRITE                  0xFF

extern const unsigned char lut_full_update[];
extern const unsigned char lut_partial_update[];

class Epd : public EpdIf {
public:
    int width;
    int height;

    Epd();
    ~Epd();
    int  Init(const unsigned char* lut);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle(void);
    void Reset(void);
    void SetFrameMemory(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
    );
    void SetFrameMemory1(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
    );
    void ClearFrameMemory(unsigned char color);
    void DisplayFrame(void);
    void Sleep(void);

private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
    const unsigned char* lut;

    void SetLut(const unsigned char* lut);
    void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
    void SetMemoryPointer(int x, int y);
};

#endif /* EPD1IN54_H */

/* END OF FILE */

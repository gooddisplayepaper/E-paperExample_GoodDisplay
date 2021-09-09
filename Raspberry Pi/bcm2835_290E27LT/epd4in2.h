

#ifndef EPD4IN2_H
#define EPD4IN2_H

#include "epdif.h"
// Display resolution


#define  DKE290
#define  MONO 1
#define  RED  1  

#ifdef DKE154
#define EPD_WIDTH       152
#define EPD_HEIGHT      152
#define MAX_LINE_BYTES    19
#define MAX_COLUMN_BYTES    152
#define ALLSCREEN_BYTES   2888

#endif

#ifdef DKE213_1
#define MAX_LINE_BYTES    16
#define MAX_COLUMN_BYTES   250
#define ALLSCREEN_BYTES   4000
#endif


#ifdef DKE213_2
#define EPD_WIDTH       104
#define EPD_HEIGHT      212
#define MAX_LINE_BYTES    13
#define MAX_COLUMN_BYTES   212
#define ALLSCREEN_BYTES   2756
#endif

#ifdef DKE290
#define EPD_WIDTH       128
#define EPD_HEIGHT      296
#define MAX_LINE_BYTES     16
#define MAX_COLUMN_BYTES   296
#define ALLSCREEN_BYTES   4736
#endif

#ifdef DKE420
#define MAX_LINE_BYTES    50
#define MAX_COLUMN_BYTES  300
#define ALLSCREEN_BYTES   15000
#endif

extern const unsigned char LUT[];

class Epd : EpdIf {
public:
    int width;
    int height;

    Epd();
    ~Epd();
    int  Init(void);
    void WaitUntilIdle(void);
    void Reset(void);
    void SetLut(void);
    void DisplayFrame(const unsigned char* frame_buffer);
    void DisplayFrame1(const unsigned char* frame_buffer);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void Sleep(void);

private:
    int reset_pin;
    int dc_pin;
    int cs_pin;
    int busy_pin;
};

#endif /* EPD4IN2_H */

/* END OF FILE */

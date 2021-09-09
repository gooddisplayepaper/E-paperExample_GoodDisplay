#ifndef EPDIF_H
#define EPDIF_H

#include <arduino.h>

// Pin definition
#define BUSY_PIN        D0
#define RST_PIN         D1
#define DC_PIN          D2
#define CS_PIN          D5
#define SCL_PIN         D6
#define SDA_PIN         D7

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);
    static void SPI_Write(unsigned char value); 
};

#endif

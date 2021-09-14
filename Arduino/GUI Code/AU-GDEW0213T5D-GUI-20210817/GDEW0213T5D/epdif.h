#ifndef EPDIF_H
#define EPDIF_H

#include <arduino.h>

// Pin definition
#define BUSY_PIN        8
#define RST_PIN         9
#define DC_PIN          10
#define CS_PIN          11
#define SCL_PIN        12
#define SDA_PIN        13

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

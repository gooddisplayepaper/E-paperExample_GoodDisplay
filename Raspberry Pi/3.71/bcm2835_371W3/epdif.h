

#ifndef EPDIF_H
#define EPDIF_H

// Pin definition
#define RST_PIN         17
#define DC_PIN          25
#define CS_PIN           8
#define BUSY_PIN        24

// Pin level definition
#define LOW             0
#define HIGH            1

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);
};
#endif

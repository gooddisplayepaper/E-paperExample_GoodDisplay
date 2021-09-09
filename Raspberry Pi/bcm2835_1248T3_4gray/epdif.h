#ifndef EPDIF_H
#define EPDIF_H

// Pin definition   BCM

#define CSB_M1   	  18
#define BUSY_M1   	  23
#define RST_M1   	  24
#define DC_M1   	  16
#define CSB_S1   	  20
#define BUSY_S1   	  21


#define CSB_S2   	  4
#define BUSY_M2   	  17
#define RST_M2   	  27
#define DC_M2   	  22
#define CSB_M2   	  13
#define BUSY_S2   	  19

#define SCL   	 6
#define SDI   	 5











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

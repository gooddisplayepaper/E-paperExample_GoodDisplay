#ifndef EPD1IN54_H
#define EPD1IN54_H

#include "epdif.h"

#define GDEM213
#define  MONO 1  
#define  RED  1  


#ifdef GDEM154
#define EPD_WIDTH       200
#define EPD_HEIGHT      200
#define MAX_LINE_BYTES    25
#define MAX_COLUMN_BYTES    200
#define ALLSCREEN_BYTES   5000
#endif

#ifdef GDEM213
#define EPD_WIDTH       128
#define EPD_HEIGHT      250
#define MAX_LINE_BYTES    16
#define MAX_COLUMN_BYTES   250
#define ALLSCREEN_BYTES   4000
#endif

#ifdef GDEM290
#define EPD_WIDTH       128
#define EPD_HEIGHT      296
#define MAX_LINE_BYTES     16
#define MAX_COLUMN_BYTES   296
#define ALLSCREEN_BYTES   4736
#endif


class Epd : public EpdIf {
public:
    int width;
    int height;

    Epd();
    ~Epd();
   


void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update(void);

void EPD_Part_Init(void);//Local refresh initialization
void EPD_Part_Update(void); 

void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);//Display 
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);





private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;


};

#endif /* EPD1IN54_H */

/* END OF FILE */

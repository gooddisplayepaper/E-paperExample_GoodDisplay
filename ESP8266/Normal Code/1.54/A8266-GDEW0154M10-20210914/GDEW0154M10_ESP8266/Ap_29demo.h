#include <avr/pgmspace.h>
////////////////array/////////////////////////
const unsigned char gImage_1[2888] PROGMEM = { /* 0X81,0X01,0X98,0X00,0X98,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,
0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X30,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,
0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X30,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0X80,0X20,0X80,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,
0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,
0X01,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF8,0X01,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XB3,0XFF,0XFF,0X80,0X31,0X80,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X21,0XFF,0XFF,0X80,
0X31,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X65,
0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X4D,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X09,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X9B,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X10,
0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8B,0XFF,
0XFF,0X80,0X30,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X09,0XFF,0XFF,0X80,0X21,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X6D,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0X69,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0X9F,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X00,0X00,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0X3F,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,
0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDC,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDC,0XFF,
0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XDD,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X00,0X00,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,
0X20,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X80,0X3C,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFB,0X7F,0XFF,0XFF,0X80,0X3F,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XDD,0XDF,0XFF,0XFF,0XF8,0X01,0XFF,0XFF,0X80,0X03,0XE0,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XDD,0XDF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0X80,0X3F,0XF0,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,0XDF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0X80,0X3C,
0X10,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,0XDF,0XFF,0XFF,0XFF,0X8B,0XFF,
0XFF,0X80,0X20,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,
0XFF,0X09,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,
0X1F,0XFF,0XFF,0XFF,0X6D,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X69,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X24,0X80,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0XFF,0XFF,0XFF,0X83,0XFF,0XFF,
0X80,0X37,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X13,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,0XFF,
0XFF,0XFF,0XFC,0X3D,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XDD,0XFF,0XFF,0XFF,0XF8,0X01,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFB,0XC3,0XFF,0XFF,0X81,0XFF,0X80,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFB,0XCF,0XFF,0XFF,0X81,
0XFF,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X01,
0XFF,0XFF,0X81,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X9F,0XFF,
0XFF,0XF8,0X01,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,
0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X80,0X20,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X31,0X90,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X9F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XF0,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X01,0XFF,0XFF,0X80,0X20,0X10,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0XFF,0XFF,0XF8,0X01,0XFF,0XFF,
0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X13,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,0XFF,
0XFF,0XFF,0XFF,0X81,0XFF,0XFF,0X80,0X37,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XDD,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X24,0X80,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0X59,0XFF,0XFF,0X80,0X3D,0X80,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0X4D,0XFF,0XFF,0X80,
0X19,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X21,
0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XB3,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0XBF,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0XBF,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XF9,0X01,0XFF,0XFF,0X80,0X20,
0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XF9,0X01,0XFF,
0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,
0XDF,0XFF,0XFF,0XFF,0X7D,0XFF,0XFF,0X81,0XFF,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XDD,0XDF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0X81,0XFF,0X80,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,0XDF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0X81,0X31,0X80,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDD,0XDF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,
0X80,0X20,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,
0X7F,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,
0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X00,0X00,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,
0X04,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X81,
0XFF,0XFF,0X80,0X04,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X04,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X59,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0X4D,0XFF,0XFF,0X80,0X00,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0X21,0XFF,0XFF,0X81,0XFF,
0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0XFF,0XFF,0XB3,0XFF,
0XFF,0X81,0XFF,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X81,0X31,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,
0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,0X80,0X20,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFB,0XDF,0XFF,0XFF,0X80,0X1F,0X00,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFB,0XDF,0XFF,0XFF,
0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,
0X01,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0X3F,
0XFF,0XFF,0XF8,0X01,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XC7,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XDF,0XDF,0XFC,0XF7,0XFF,0XFF,0XFF,0XFF,0X80,0X31,0X80,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XDF,0XF8,0X77,0XFF,0XFF,0XFF,0XFF,0X80,
0X31,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0X9F,0XF3,0X37,0XFF,0XFF,
0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X3F,0XF7,
0X97,0XFF,0XFF,0XFF,0XFF,0X80,0X1F,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF0,0X7F,0XF1,0XC7,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0XE7,0XFF,0X7D,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,
0X00,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0X80,0X1F,
0X00,0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X1F,0XF7,0X9F,0XFC,0X01,0XFF,
0XFF,0X80,0X3F,0X80,0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X1F,0XF7,0X0F,
0XFF,0X7F,0XFF,0XFF,0X80,0X31,0X80,0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XFE,
0X3F,0XF6,0X67,0XFF,0X7F,0XFF,0XFF,0X80,0X31,0X80,0X3F,0XFF,0X00,0X00,0X00,0X03,
0XFF,0XFF,0XF8,0XFF,0XF2,0XF7,0XFF,0X7F,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0X00,
0X00,0X00,0X03,0XFF,0XFF,0XE1,0XFF,0XF0,0X47,0XFF,0X01,0XFF,0XFF,0X80,0X1F,0X00,
0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,0XFF,0XC0,0X1F,0XFC,0X4F,0XFF,0X01,0XFF,0XFF,
0X80,0X00,0X00,0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0X80,0X20,0XE0,0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0XFF,0XFF,0X80,0X3C,0XF0,0X3F,0XFF,0X00,0X78,
0X07,0X83,0XFF,0XFF,0XC0,0X1F,0XF0,0X07,0XFF,0X39,0XFF,0XFF,0X80,0X3E,0X90,0X3F,
0XFF,0X00,0X78,0X07,0X83,0XFF,0XFF,0XC0,0X1F,0XF0,0X07,0XFF,0X39,0XFF,0XFF,0X80,
0X22,0X90,0X3F,0XFF,0X00,0X78,0X07,0X83,0XFF,0XFF,0XFF,0XFF,0XF9,0XFF,0XFF,0X01,
0XFF,0XFF,0X80,0X3F,0XF0,0X3F,0XFF,0X00,0X78,0X07,0X83,0XFF,0XFF,0XFF,0XFF,0XFD,
0XFF,0XFF,0X83,0XFF,0XFF,0X80,0X1D,0XE0,0X3F,0XFF,0X00,0X78,0X07,0X83,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0X00,0X78,0X07,
0X83,0XFF,0XFF,0XFF,0XFF,0XFD,0XF7,0XFF,0X83,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,
0X00,0X78,0X07,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X47,0XFF,0X01,0XFF,0XFF,0X80,0X00,
0X80,0X3F,0XFF,0X00,0X78,0X07,0X83,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,0X3D,0XFF,
0XFF,0X80,0X00,0X80,0X3F,0XFF,0X0F,0X01,0XE0,0X03,0XFF,0XFF,0XFF,0X7F,0XFE,0X0F,
0XFF,0X39,0XFF,0XFF,0X80,0X00,0X00,0X3F,0XFF,0X0F,0X01,0XE0,0X03,0XFF,0XFF,0XC0,
0X1F,0XFC,0X47,0XFF,0X00,0X3F,0XFF,0X80,0X20,0X00,0X3F,0XFF,0X0F,0X01,0XE0,0X03,
0XFF,0XFF,0XC0,0X1F,0XFD,0XF7,0XFF,0X00,0X3F,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X0F,
0X01,0XE0,0X03,0XFF,0XFF,0XE3,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0X80,
0X3F,0XFF,0X0F,0X01,0XE7,0X83,0XFF,0XFF,0XF8,0X7F,0XFC,0XF7,0XFF,0X83,0XFF,0XFF,
0X80,0X0F,0X80,0X3F,0XFF,0X0F,0X01,0XE7,0X83,0XFF,0XFF,0XFE,0X7F,0XF8,0X77,0XFF,
0X01,0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X0F,0X01,0XE7,0X83,0XFF,0XFF,0XFF,0XFF,
0XF3,0X37,0XFF,0X3D,0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X0F,0X01,0XE7,0X83,0XFF,
0XFF,0XDE,0X7F,0XF7,0X97,0XFF,0X39,0XFF,0XFF,0X80,0X0F,0X80,0X3F,0XFF,0X0F,0XFF,
0XE7,0X83,0XFF,0XFF,0XDC,0X3F,0XF1,0XC7,0XFF,0X00,0X3F,0XFF,0X80,0X3F,0X80,0X3F,
0XFF,0X0F,0XFF,0XE7,0X83,0XFF,0XFF,0XD9,0X9F,0XF9,0XE7,0XFF,0X00,0X3F,0XFF,0X80,
0X3E,0X00,0X3F,0XFF,0X0F,0XFF,0XE7,0X83,0XFF,0XFF,0XCB,0XDF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X80,0X20,0X00,0X3F,0XFF,0X0F,0XFF,0XE7,0X83,0XFF,0XFF,0XC1,0X1F,0XF7,
0X9F,0XFF,0X01,0XFF,0XFF,0X80,0X20,0X00,0X3F,0XFF,0X00,0X00,0X07,0X83,0XFF,0XFF,
0XF1,0X3F,0XF7,0X0F,0XFF,0X01,0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X00,0X00,0X07,
0X83,0XFF,0XFF,0XFF,0XFF,0XF6,0X67,0XFF,0XF9,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,
0X00,0X00,0X07,0X83,0XFF,0XFF,0XFF,0XDF,0XF2,0XF7,0XFF,0XFD,0XFF,0XFF,0X80,0X0F,
0X80,0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,0XFF,0XFF,0XDF,0XF0,0X47,0XFF,0X01,0XFF,
0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X4F,
0XFF,0X03,0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X00,0X7F,0XFF,0X83,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X0F,0X80,0X3F,0XFF,0X00,0X7F,0XFF,0X83,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XC3,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0X00,
0X7F,0XFF,0X83,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0XC1,0XFF,0XFF,0X80,0X3E,0X00,
0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X1F,0XF0,0X07,0XFB,0X9D,0XFF,0XFF,
0X80,0X20,0X00,0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XC0,0X1F,0XF0,0X07,0XFB,
0X1D,0XFF,0XFF,0X80,0X20,0X00,0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XE7,0XFF,
0XF9,0XFF,0XF8,0X39,0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0X00,0X00,0X00,0X03,0XFF,
0XFF,0XF7,0XFF,0XFD,0XFF,0XFC,0X7B,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0X00,0X00,
0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X0F,0X80,0X3F,
0XFF,0X00,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,
0X3E,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X0F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0X80,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X3E,0X00,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X20,
0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X80,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X00,0X3F,};
const unsigned char gImage_2[2888] PROGMEM = { /* 0X81,0X01,0X98,0X00,0X98,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFC,0XFF,0XFF,0XF0,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XC1,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFE,0X3F,0XFF,0XE3,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X7F,0XFF,
0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,
0XFC,0XFF,0XFF,0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFC,0XFF,0XF9,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XF3,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XE3,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XE7,0XFF,0XFF,0XFF,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XE6,
0X00,0X07,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,
0XFC,0XFF,0XCE,0X0F,0X87,0XFF,0X9F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,
0X80,0X00,0XFF,0XFC,0XFF,0XCE,0X0F,0X83,0XFF,0X9F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFE,0X01,0X80,0X00,0XFF,0XFC,0XFF,0XCE,0X0F,0X83,0XFF,0X9F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0X80,0X00,0XFF,0XFC,0XFF,0X9E,0X0F,0X83,0XE7,0XCF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XC0,0X00,0XFF,0XFC,0XFF,0X9E,0X0F,
0XC3,0XE7,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XFF,0X80,0XFF,0XFC,
0XFF,0X9E,0X0F,0XC7,0XE7,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XFF,
0X80,0XFF,0XFC,0XFF,0X9E,0X0F,0XC7,0XE7,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0X9E,0X0F,0XFF,0XE7,0XCF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0X9E,0X0F,0XFF,0XE7,0XCF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X7E,0X00,0XFF,0XFC,0XFF,0X9E,0X0F,0XFF,
0XE7,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0XFF,0X00,0XFF,0XFC,0XFF,
0X9E,0X0F,0XFF,0XE7,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XDB,0X80,
0XFF,0XFC,0XFF,0XDE,0X0F,0XFF,0XFF,0X9F,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0XFE,
0X01,0X99,0X80,0XFF,0XFC,0XFF,0XCE,0X00,0X03,0XFF,0X9F,0XFF,0XFF,0XFF,0XC7,0XFF,
0XFF,0XFF,0XFE,0X01,0X99,0X80,0XFF,0XFC,0XFF,0XCF,0XFF,0XC3,0XFF,0X1F,0XFF,0XFF,
0XFF,0XE1,0XFF,0XFF,0XFF,0XFE,0X01,0XDB,0X80,0XFF,0XFC,0XFF,0XE7,0XFF,0XC3,0XFF,
0X3F,0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFE,0X00,0XFF,0X00,0XFF,0XFC,0XFF,0XE3,
0XFF,0XC3,0XFE,0X7F,0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFE,0X00,0X7E,0X00,0XFF,
0XFC,0XFF,0XF3,0XFF,0XC3,0XFC,0X7F,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,0XFE,0X00,
0X00,0X00,0XFF,0XFC,0XFF,0XF9,0XFF,0XC3,0XFC,0XFF,0XFF,0XFF,0XFF,0XC7,0XFF,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XF8,0XFF,0XC3,0XF8,0XFF,0XFF,0XFF,0XFF,
0XDF,0XFF,0XFF,0XFF,0XFE,0X01,0XE0,0X00,0XFF,0XFC,0XFF,0XFE,0X7F,0XE7,0XF1,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XFC,0X00,0XFF,0XFC,0XFF,0XFE,0X1F,
0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0XFF,0XFF,0XFE,0X00,0X3F,0X00,0XFF,0XFC,
0XFF,0XFF,0X8F,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,0XFE,0X00,0X0F,
0XC0,0XFF,0XFC,0XFF,0XFF,0XE0,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,
0XFE,0X00,0X07,0XE0,0XFF,0XFC,0XFF,0XFF,0XFC,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,
0X7F,0XFF,0XFF,0XFE,0X00,0X3F,0X70,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XC3,0X7F,0XFF,0XFF,0XFE,0X01,0XFC,0X30,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XC3,0X7F,0XFF,0XFF,0XFE,0X01,0XE0,0X30,0XFF,0XFC,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XFF,0XFF,0XFE,0X00,0X00,0X00,
0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XFF,0XFF,0XFE,
0X00,0XFF,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,
0XFF,0XFF,0XFE,0X01,0XFF,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XCF,0XFF,0XFF,0XFE,0X01,0XB3,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0XFF,0XFF,0XFE,0X01,0XB9,0X80,0XFF,0XFC,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0XFF,0XFF,0XFE,0X01,0X99,0X80,0XFF,
0XFC,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0XFF,0XFF,0XFE,0X01,
0XD9,0X80,0XFF,0XFC,0XFF,0XFF,0XF0,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0XFF,
0XFF,0XFE,0X00,0XFF,0X80,0XFF,0XFC,0XFF,0XFF,0XC1,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,
0XC0,0X0F,0XFF,0XFF,0XFE,0X00,0X6F,0X00,0XFF,0XFC,0XFF,0XFF,0X8F,0XFF,0XC7,0XFF,
0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,0X7F,
0XFF,0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,
0XFF,0XFE,0X7F,0XFF,0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0F,0XFF,
0X80,0XFF,0XFC,0XFF,0XFC,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XFF,0XFF,
0XFE,0X0F,0XFF,0X80,0XFF,0XFC,0XFF,0XF9,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XC0,
0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XF3,0XFF,0XFF,0XFE,0X7F,0XFF,
0XFF,0XFF,0XDE,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XF3,0XFF,0XFF,
0XFF,0X3F,0XFF,0XFF,0XFF,0XDE,0XFF,0XFF,0XFF,0XFE,0X00,0X7E,0X00,0XFF,0XFC,0XFF,
0XF3,0X00,0X03,0XFF,0X3F,0XFF,0XFF,0XFF,0XDE,0XFF,0XFF,0XFF,0XFE,0X00,0XFF,0X00,
0XFF,0XFC,0XFF,0XE7,0X07,0XC3,0XFF,0X9F,0XFF,0XFF,0XFF,0XDE,0XFF,0XFF,0XFF,0XFE,
0X01,0XC3,0X80,0XFF,0XFC,0XFF,0XE7,0X07,0XC1,0XFF,0X9F,0XFF,0XFF,0XFF,0XC0,0X0F,
0XFF,0XFF,0XFE,0X01,0X81,0X80,0XFF,0XFC,0XFF,0XCF,0X07,0XC1,0XF7,0XDF,0XFF,0XFF,
0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X01,0X81,0X80,0XFF,0XFC,0XFF,0XCF,0X07,0XC1,0XF7,
0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XC3,0X80,0XFF,0XFC,0XFF,0XCF,
0X07,0XC1,0XF7,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XFF,0XF0,0XFF,
0XFC,0XFF,0XCF,0X07,0XC1,0XF7,0XCF,0XFF,0XFF,0XFF,0XE7,0X1F,0XFF,0XFF,0XFE,0X01,
0XFF,0XF0,0XFF,0XFC,0XFF,0XCF,0X07,0XE3,0X00,0X4F,0XFF,0XFF,0XFF,0XC6,0X0F,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XCF,0X07,0XFF,0X00,0X4F,0XFF,0XFF,0XFF,
0XDE,0XEF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XCF,0X07,0XFF,0XF7,0XCF,
0XFF,0XFF,0XFF,0XDC,0XEF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XCF,0X07,
0XFF,0XF7,0XCF,0XFF,0XFF,0XFF,0XDD,0XEF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,
0XFF,0XCF,0X07,0XFF,0XF7,0XCF,0XFF,0XFF,0XFF,0XDD,0XEF,0XFF,0XFF,0XFE,0X00,0X00,
0X00,0XFF,0XFC,0XFF,0XEF,0X07,0XFF,0XF7,0X9F,0XFF,0XFF,0XFF,0XC1,0X8F,0XFF,0XFF,
0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XE7,0X07,0XC7,0XFF,0X9F,0XFF,0XFF,0XFF,0XE3,
0X9F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XE7,0X00,0X03,0XFF,0X9F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XE7,0XFF,0XC3,
0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X66,0X00,0XFF,0XFC,0XFF,
0XF3,0XFF,0XC1,0XFF,0X3F,0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X00,0XE7,0X00,
0XFF,0XFC,0XFF,0XF9,0XFF,0XC1,0XFE,0X7F,0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,
0X01,0XC3,0X80,0XFF,0XFC,0XFF,0XF9,0XFF,0XC1,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFE,0X01,0X81,0X80,0XFF,0XFC,0XFF,0XFC,0XFF,0XC1,0XFC,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0X81,0X80,0XFF,0XFC,0XFF,0XFC,0X7F,0XC3,0XF9,
0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFE,0X01,0XC3,0X80,0XFF,0XFC,0XFF,0XFF,
0X7F,0XE3,0XF9,0XFF,0XFF,0XFF,0XFF,0XE0,0X1F,0XFF,0XFF,0XFE,0X00,0XFF,0X00,0XFF,
0XFC,0XFF,0XFF,0X8F,0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,0XCF,0XCF,0XFF,0XFF,0XFE,0X00,
0X7E,0X00,0XFF,0XFC,0XFF,0XFF,0XC1,0XFE,0X0F,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,0XF0,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0XDF,0XEF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,0XFC,0X01,0XFF,0XFF,
0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X0D,0XFF,0X80,0XFF,0XFC,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X0D,0XFF,
0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X00,0XCF,0X00,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0XDF,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0X99,0X80,0XFF,0XFC,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X01,0X99,0X80,
0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,
0X01,0X99,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFE,0X01,0XFB,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF0,0X3F,0XFF,0XFF,0XFE,0X00,0XF3,0X00,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE0,0X1F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0XCF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,
0XFC,0XFF,0XFF,0XFF,0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,0XFE,0X01,
0XFF,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,
0XFF,0XFE,0X01,0XFF,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XF8,0X7F,0XFF,0XFF,0XFF,0XFF,
0XDF,0XEF,0XFF,0XFF,0XFE,0X00,0X03,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,0XF9,0X1F,0XFF,
0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X00,0X01,0X80,0XFF,0XFC,0XFF,0XFF,0XFF,
0XF9,0X87,0XFF,0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFE,0X00,0X01,0X80,0XFF,0XFC,
0XFF,0XFF,0XFF,0XF9,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X01,
0X80,0XFF,0XFC,0XFF,0XFF,0XF0,0X01,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X01,0XFF,0X80,0XFF,0XFC,0XFF,0XFF,0XF0,0X01,0XFC,0X3F,0XFF,0XFF,0XFF,0XF0,
0X3F,0XFF,0XFF,0XFE,0X01,0XFF,0X00,0XFF,0XFC,0XFF,0XFF,0XF3,0XFF,0XFF,0X1F,0XFF,
0XFF,0XFF,0XE0,0X1F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0XFF,0XF3,0XFF,
0XFF,0XC7,0XFF,0XFF,0XFF,0XCF,0XCF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,
0X00,0X03,0XFF,0XFF,0XC3,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,0XFE,0X0F,0XFF,0X80,
0XFF,0XFC,0XFF,0X00,0X03,0XFF,0XFF,0X0F,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,0XFE,
0X0F,0XFF,0X80,0XFF,0XFC,0XFF,0X3F,0XF3,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XDF,0XEF,
0XFF,0XFF,0XFE,0X07,0XC0,0X00,0XFF,0XFC,0XFF,0X3F,0XF0,0X01,0XF8,0X7F,0XFF,0XFF,
0XFF,0XCF,0XCF,0XFF,0XFF,0XFE,0X01,0XF0,0X00,0XFF,0XFC,0XFF,0X3F,0XF0,0X01,0XF1,
0XFF,0XFF,0XFF,0XFF,0XE0,0X1F,0XFF,0XFF,0XFE,0X00,0X7E,0X00,0XFF,0XFC,0XFF,0X3F,
0XFF,0XF9,0XC3,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFE,0X00,0X1F,0X80,0XFF,
0XFC,0XFF,0X00,0X0F,0XF9,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,
0X0F,0X80,0XFF,0XFC,0XFF,0X00,0X0F,0XF8,0X1F,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,
0XFF,0XFE,0X00,0X7E,0X00,0XFF,0XFC,0XFF,0X3F,0XCF,0XF8,0X3F,0XFF,0XFF,0XFF,0XFF,
0XE0,0X1F,0XFF,0XFF,0XFE,0X01,0XF8,0X00,0XFF,0XFC,0XFF,0X3F,0XCF,0XF9,0X3F,0XFF,
0XFF,0XFF,0XFF,0XCF,0XCF,0XFF,0XFF,0XFE,0X07,0XC0,0X00,0XFF,0XFC,0XFF,0X20,0X0F,
0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,0XFE,0X0F,0XFF,0X80,0XFF,0XFC,
0XFF,0X20,0X0F,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,0XFE,0X0F,0XFF,
0X80,0XFF,0XFC,0XFF,0X20,0X0F,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,0XFF,
0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0X20,0X0F,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XCF,
0XCF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0X3F,0XCF,0XFF,0X3F,0XFF,0XFF,
0XFF,0XFF,0XE0,0X1F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,0X3F,0XCF,0XFF,
0X3F,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0XFF,0XFC,0XFF,
0X3F,0XCF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,
0XFF,0XFC,0XFF,0X3F,0XCF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,0XCF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XF6,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,0XCF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XE6,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,0XCF,0XFF,0X3F,
0XFF,0XFF,0XFF,0XFF,0XCE,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,
0XCF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XDE,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFC,0XFF,0X00,0X0F,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XDE,0XEF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,
0XCF,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X3F,0XFF,0XFF,0X3F,0XFF,
0XFF,0XFF,0XFF,0XE0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0X00,0X00,
0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XF0,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,
0XFF,0X00,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,};





/////////////////////////////////////////////

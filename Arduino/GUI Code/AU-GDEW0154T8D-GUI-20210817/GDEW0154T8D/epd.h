#ifndef epd_H
#define epd_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH      152
#define EPD_HEIGHT      152

class Epd : EpdIf
{
public:
	unsigned long width;
	unsigned long height;

	Epd();
	~Epd();
	void SendCommand(unsigned char command);
	void SendData(unsigned char data);
	void WaitUntilIdle(void);
	void Reset(void);
	void Clear(void);
	void Display(const unsigned char* frame_buffer);

	void DisplayFrame(void);
	void DisplayPartFrame(void);

	void Sleep(void);
  int Init(void);
  void PaintAllClear(void);
  void Display_XH(unsigned int x1,unsigned int y1,unsigned int H1,unsigned char* frame_buffer,unsigned char num);
void Epd::SetFrameMemory(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
);
 
private:
	unsigned int reset_pin;
	unsigned int dc_pin;
	unsigned int cs_pin;
	unsigned int busy_pin;

};

#endif /* EPD1IN54B_H */

/* END OF FILE */

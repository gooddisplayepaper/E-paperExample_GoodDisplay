#ifndef epd_H
#define epd_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH      128
#define EPD_HEIGHT      250

class Epd : EpdIf
{
public:
	unsigned long width;
	unsigned long height;

	Epd();
	~Epd();
	// int  Init(void);
	int LDirInit(void);
	int HDirInit(void);
	void SendCommand(unsigned char command);
	void SendData(unsigned char data);
	void WaitUntilIdle(void);
	void Reset(void);
	void Clear(void);
	void Display(const unsigned char* frame_buffer);
	void DisplayPartBaseImage(const unsigned char* frame_buffer);
	void DisplayPartBaseWhiteImage(void);
	void DisplayPart(const unsigned char* frame_buffer);
	void SetFrameMemory(
	        const unsigned char* image_buffer,
	        int x,
	        int y,
	        int image_width,
	        int image_height
	);
	void DisplayFrame(void);
	void DisplayPartFrame(void);

	void Sleep(void);
  void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
  int Init(void);
private:
	unsigned int reset_pin;
	unsigned int dc_pin;
	unsigned int cs_pin;
	unsigned int busy_pin;

	void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
	void SetMemoryPointer(int x, int y);
};

#endif /* EPD1IN54B_H */

/* END OF FILE */

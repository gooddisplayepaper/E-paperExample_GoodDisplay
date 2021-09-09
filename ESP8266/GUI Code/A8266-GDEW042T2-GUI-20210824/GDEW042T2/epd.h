#ifndef epd_H
#define epd_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH      400
#define EPD_HEIGHT      300

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

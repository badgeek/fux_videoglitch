#include "FreeImage.h"

class glitchWrapper{
private:
	FIMEMORY *GLITCH_MEM;
	FIBITMAP *GLITCH_FUCK;
    BYTE *GLITCH_DATA;
public:
	glitchWrapper();
	~glitchWrapper();
	void glitchEffect(int gWidth, int gHeight, unsigned char * gPixels, int gStart, int gAmount);
};
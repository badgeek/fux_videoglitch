#include "glitchWrapper.h"
#include "FreeImage.h"
#include <stdlib.h>

glitchWrapper::glitchWrapper()
{
	
}

glitchWrapper::~glitchWrapper()
{
	
}

void glitchWrapper::glitchEffect(int gWidth, int gHeight, unsigned char * gPixels, unsigned char * gTemp, int gStart, int gAmount)
{
 FIMEMORY *GLITCH_MEM;
 FIBITMAP *GLITCH_FUCK;
 FIBITMAP *GLITCH_SAVED;
 BYTE *GLITCH_DATA = NULL;
 DWORD GLITCH_SIZE;
 
 // Load image from ImageStruct to FreeImage Memory
 GLITCH_FUCK = FreeImage_ConvertFromRawBits((BYTE*)gTemp, gWidth, gHeight, 3 * gWidth, 24, 0, 0, 0, false);

 //reserve memory
 GLITCH_MEM  = FreeImage_OpenMemory();

 // Resave image as JPG to Memory
 FreeImage_SaveToMemory(FIF_JPEG, GLITCH_FUCK, GLITCH_MEM, 0);

 //this one causing error on linux hmm...
 FreeImage_AcquireMemory(GLITCH_MEM, &GLITCH_DATA, &GLITCH_SIZE);

if(gAmount > 0)
{
 //this is the glitching part
 for(int g=gStart; g < (gStart+gAmount); g++  )
 {
	GLITCH_DATA[g] = '\0'; 
 }
}


 //rewind to avoid blank image
 FreeImage_SeekMemory(GLITCH_MEM, 0L, SEEK_SET);

 //open glitched image
 GLITCH_SAVED = FreeImage_LoadFromMemory(FIF_JPEG, GLITCH_MEM, 0);  
 
 int fWidth = FreeImage_GetWidth(GLITCH_SAVED); 
 int fHeight = FreeImage_GetHeight(GLITCH_SAVED); 

 if ((BOOL)FreeImage_HasPixels(GLITCH_SAVED)){ 
 	int bytespp = FreeImage_GetLine(GLITCH_SAVED) / FreeImage_GetWidth(GLITCH_SAVED);
 	for(int y = 0; y < fHeight; y++) {
 		BYTE *bits = FreeImage_GetScanLine(GLITCH_SAVED, y);
 		for(int x = 0; x < fWidth; x++) {
			gPixels[0] = 255;
 			gPixels[1] = (unsigned char) bits[FI_RGBA_RED];
 			gPixels[2] = (unsigned char) bits[FI_RGBA_GREEN];
 			gPixels[3] = (unsigned char) bits[FI_RGBA_BLUE];
 			gPixels += 4;
 			bits += bytespp;
 		}
 	}
 }


 //lets experiment with this
 FreeImage_Unload(GLITCH_SAVED);	    
 FreeImage_Unload(GLITCH_FUCK);
 FreeImage_CloseMemory(GLITCH_MEM);
 //free(GLITCH_DATA);

}
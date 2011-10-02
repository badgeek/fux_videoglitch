#include "glitchWrapper.h"
#include "FreeImage.h"
#include <stdlib.h>

glitchWrapper::glitchWrapper()
{
	
}

glitchWrapper::~glitchWrapper()
{
	
}

void glitchWrapper::glitchEffect(int gWidth, int gHeight, unsigned char * gPixels, int gStart, int gAmount)
{
	FIMEMORY *GLITCH_MEM;
	FIBITMAP *GLITCH_FUCK;
    BYTE *GLITCH_DATA;


 int GLITCH_SIZE;
 // Load image from ImageStruct to FreeImage Memory
 GLITCH_FUCK = FreeImage_ConvertFromRawBits((BYTE*)gPixels, gWidth, gHeight, 3 * gWidth, 24, 0, 0, 0, false);
 GLITCH_MEM  = FreeImage_OpenMemory();
 // Resave image as JPG to Memory
 FreeImage_SaveToMemory(FIF_JPEG, GLITCH_FUCK, GLITCH_MEM, 0);
 FreeImage_AcquireMemory(GLITCH_MEM, &GLITCH_DATA, (DWORD*) &GLITCH_SIZE);
/*
 for(int g=gStart; g < (gStart+gAmount); g++  )
 {
	GLITCH_DATA[g] = '\0'; 
 }

 FreeImage_SeekMemory(GLITCH_MEM, 0L, SEEK_SET);
 
 FIBITMAP *GLITCH_SAVED = FreeImage_LoadFromMemory(FIF_JPEG, GLITCH_MEM, 0);  

 int fWidth = FreeImage_GetWidth(GLITCH_SAVED); 
 int fHeight = FreeImage_GetHeight(GLITCH_SAVED); 

 if (FreeImage_HasPixels(GLITCH_SAVED)){ 
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
 }else{
 	//post("FUX_GLITCH-> bitmap too fucked to be displayed...");
 }
*/

 //lets experiment with this
 FreeImage_Unload(GLITCH_FUCK);	    
// FreeImage_Unload(GLITCH_SAVED);	    
 FreeImage_CloseMemory(GLITCH_MEM);
 free(GLITCH_DATA);

}
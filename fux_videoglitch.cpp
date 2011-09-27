/*
 *  fux_videoglitch.cpp
 *  gem_darwin
 *
 *  Created by chris clepper on Mon Oct 07 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "fux_videoglitch.h"
CPPEXTERN_NEW(fux_videoglitch)

/////////////////////////////////////////////////////////
//
// fux_videoglitch
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
fux_videoglitch :: fux_videoglitch()
{	
	
long size,src,i;    
inletBlur = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("amount"));
inletLength = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("length"));

m_blur = 0;
m_blurH = 240;
m_blurW = 240;
m_blurBpp = 2;
size = 320 * 240 * 4;
m_glitchAmount = 20;
m_glitchLength = 10;

}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
fux_videoglitch :: ~fux_videoglitch()
{
  delete saved;
  //relocate this to on external deletion
}

/////////////////////////////////////////////////////////
// processImage
//
/////////////////////////////////////////////////////////
void fux_videoglitch :: processRGBAImage(imageStruct &image)
{
  int h,w,hlength;
  long src;
  int R,G,B;
  unsigned char *pixels=image.data;

  src = 0;

  if (m_blurH != image.ysize || m_blurW != image.xsize || m_blurBpp != image.csize) {
    m_blurH = image.ysize;
    m_blurW = image.xsize;
    m_blurBpp = image.csize;
    m_blurSize = m_blurH * m_blurW * m_blurBpp;
    delete saved;
    saved = new unsigned int [m_blurSize];
  }

  hlength = image.xsize;
	
  
  int GLITCH_SIZE;	
  // to avoid header corruption
  int GLITCH_START = 100;

  // Load image from ImageStruct to FreeImage Memory
  GLITCH_FUCK = FreeImage_ConvertFromRawBits((BYTE*)pixels, m_blurW, m_blurH, 3 * m_blurW, 24, 0, 0, 0, false);
  //FIMEMORY *GLITCH_MEM_FINAL  = FreeImage_OpenMemory();
  GLITCH_MEM  = FreeImage_OpenMemory();

  // Resave image as JPG to Memory
  FreeImage_SaveToMemory(FIF_JPEG, GLITCH_FUCK, GLITCH_MEM, 0);
  
  //FreeImage_Save(FIF_JPEG, GLITCH_FUCK, "/Volumes/xmanticorex/Users/xcorex/Public/Kinect/glitch.jpg", JPEG_QUALITYSUPERB);

  //FreeImage_Unload(GLITCH_FUCK);	    
  

  // Get Access to memory
  FreeImage_AcquireMemory(GLITCH_MEM, &GLITCH_DATA, (DWORD*) &GLITCH_SIZE);
  
  // Fuck the memory 
  //				 glitch amount

  for(int g=m_glitchAmount; g < (m_glitchAmount+m_glitchLength); g++  )
  {
	GLITCH_DATA[g] = '\0'; 
  }
  
  
  // Rewind to Start of mem or Blank image
  FreeImage_SeekMemory(GLITCH_MEM, 0L, SEEK_SET);
  
  //Reload GLITCHED image
  FIBITMAP *GLITCH_SAVED = FreeImage_LoadFromMemory(FIF_JPEG, GLITCH_MEM, 0);  

  int fwidth = FreeImage_GetWidth(GLITCH_SAVED); 
  int fheight = FreeImage_GetHeight(GLITCH_SAVED); 

  if (FreeImage_HasPixels(GLITCH_SAVED)){ 
  	int bytespp = FreeImage_GetLine(GLITCH_SAVED) / FreeImage_GetWidth(GLITCH_SAVED);
  	for(int y = 0; y < fheight; y++) {
  		BYTE *bits = FreeImage_GetScanLine(GLITCH_SAVED, y);
  		for(int x = 0; x < fwidth; x++) {
			pixels[0] = 255;
  			pixels[1] = (unsigned char) bits[FI_RGBA_RED];
  			pixels[2] = (unsigned char) bits[FI_RGBA_GREEN];
  			pixels[3] = (unsigned char) bits[FI_RGBA_BLUE];
  			pixels += 4;
  			bits += bytespp;
  		}
  	}
  }else{
  	post("FUX_GLITCH-> bitmap too fucked to be displayed...");
  }
 

  //lets experiment with this
  FreeImage_Unload(GLITCH_FUCK);	    
  FreeImage_Unload(GLITCH_SAVED);	    
  FreeImage_CloseMemory(GLITCH_MEM);
  free(GLITCH_DATA);
  

}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void fux_videoglitch :: obj_setupCallback(t_class *classPtr)
{

    class_addmethod(classPtr, (t_method)&fux_videoglitch::blurCallback,gensym("amount"), A_DEFFLOAT, A_NULL);
    class_addmethod(classPtr, (t_method)&fux_videoglitch::lengthCallback,gensym("length"), A_DEFFLOAT, A_NULL);

}

void fux_videoglitch :: blurCallback(void *data, t_floatarg value)
{
	GetMyClass(data)->m_glitchAmount=(value);
}

void fux_videoglitch :: lengthCallback(void *data, t_floatarg value)
{
	GetMyClass(data)->m_glitchLength=(value);
}

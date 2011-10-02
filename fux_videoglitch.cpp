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

  //glitcher.glitchEffect(m_blurW, m_blurH, pixels, m_glitchAmount, m_glitchLength);

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

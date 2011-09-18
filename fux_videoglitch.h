/*
 *  fux_videoglitch.h
 *  gem_darwin
 *
 *  Created by chris clepper on Mon Oct 07 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INCLUDE_fux_videoglitch_H_ 
#define INCLUDE_fux_videoglitch_H_ 

#include "Base/GemPixObj.h"
#include "FreeImage.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    fux_videoglitch
    
    

KEYWORDS
    pix
    yuv
    
DESCRIPTION

  old motion blur object.  soon to be an abstraction for pix_convolve ??
   
-----------------------------------------------------------------*/

class GEM_EXTERN fux_videoglitch : public GemPixObj
{
CPPEXTERN_HEADER(fux_videoglitch, GemPixObj)

    public:

	    //////////
	    // Constructor
    	fux_videoglitch();
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~fux_videoglitch();
    	virtual void processRGBAImage(imageStruct &image);
        
        unsigned int  *saved;
        int		m_blur;
        float	m_glitchAmount;
        int		m_blurH,m_blurW,m_blurSize,m_blurBpp;
        t_inlet         *inletBlur;

		FIMEMORY *GLITCH_MEM;
		FIBITMAP *GLITCH_FUCK;
        BYTE *GLITCH_DATA; 

    private:
    
    	//////////
    	// Static member functions
    	
        static void blurCallback       (void *data, t_floatarg value);


};

#endif


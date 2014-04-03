#include "stdafx.h"
#include "CSampleGrabber.h"


CSampleGrabberCB::CSampleGrabberCB( ){
		lHeight = 0;
		lWidth = 0;
		bSnapOneShot = false;
		pCapture = NULL;
		
	}   

	// fake out any COM ref counting
	//
	

	// fake out any COM QI'ing
	//
STDMETHODIMP CSampleGrabberCB::QueryInterface(REFIID riid, void ** ppv){
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown ) 
		{
			*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
			return NOERROR;
		}    
		return E_NOINTERFACE;
	}

	// we don't implement this interface for this example
	//
STDMETHODIMP CSampleGrabberCB::SampleCB( double SampleTime, IMediaSample * pSample ){
		return 0;
	}

	// The sample grabber is calling us back on its deliver thread.
	// This is NOT the main app thread!
	//
	//           !!!!! WARNING WARNING WARNING !!!!!
	//
	// On Windows 9x systems, you are not allowed to call most of the 
	// Windows API functions in this callback.  Why not?  Because the
	// video renderer might hold the global Win16 lock so that the video
	// surface can be locked while you copy its data.  This is not an
	// issue on Windows 2000, but is a limitation on Win95,98,98SE, and ME.
	// Calling a 16-bit legacy function could lock the system, because 
	// it would wait forever for the Win16 lock, which would be forever
	// held by the video renderer.
	//
	// As a workaround, copy the bitmap data during the callback,
	// post a message to our app, and write the data later.
	//
STDMETHODIMP CSampleGrabberCB::BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize ){
		
	
	if(!bSnapOneShot){
		return 0;
	}

	if(!pCapture){
		pCapture = new BYTE[lBufferSize];
	}
		
	memcpy(pCapture, pBuffer, lBufferSize);
	bSnapOneShot = false;
	return 0;
}



	


class CSampleGrabberCB : public ISampleGrabberCB 
{
public:
	// these will get set by the main thread below. We need to
	// know this in order to write out the bmp
	long lWidth;
	long lHeight;
	bool bSnapOneShot;
	BYTE *pCapture;
	

	CSampleGrabberCB( );   

	// fake out any COM ref counting
	//
	STDMETHODIMP_(ULONG) AddRef() { return 2; }
	STDMETHODIMP_(ULONG) Release() { return 1; }

	// fake out any COM QI'ing
	//
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);

	// we don't implement this interface for this example
	//
	STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample );

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
	STDMETHODIMP BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize );

};

#ifndef _DSCOMMENT_H
#define _DSCOMMENT_H

public ref class DSComment{
public:

		IGraphBuilder *pGraphManager;
		ICaptureGraphBuilder2 *pCapture;
		ISampleGrabber *pGrabber;
		IVideoWindow  *pVW;
		IMediaControl *pMC;
		IMediaEventEx *pME;
		IBaseFilter *pCaptureBaseFilter;
		IBaseFilter *pGrabberBaseFilter;
		IBaseFilter *pNullRenderFilter;

			
	HRESULT CreatFilterGraph();

	HRESULT CreatNullRender();
	
	HRESULT CreatGrabberFilter();
	
	HRESULT CreatCaptureFilter();

	

	HRESULT BuiltFilterGraph();

	void SetVideoWindows(HWND pWnd);

	void DestroyFilter();

	BYTE* SnapStillImage(long* size);

	BYTE* SampleStillImage(long &size);

};

#endif

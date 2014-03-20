
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

			
	HRESULT CreatFilterGraph();

	
	HRESULT CreatGrabberFilter();
	
	HRESULT CreatCaptureFilter();

	

	HRESULT BuiltFilterGraph();

	void SetVideoWindows(HWND pWnd);

	void DestroyFilter();

	BYTE* SnapStillImage(long* size);

};

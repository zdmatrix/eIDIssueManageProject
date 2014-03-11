
const char* CAPTUREDEVNAME = "USB  ”∆µ…Ë±∏";

public ref class CaptureVideoComment{
	public:
		IBaseFilter *pBaseFilter;
					 IVideoWindow  *pVW;
					 IMediaControl *pMC;
//					 IMediaEventEx *pME = NULL;
					 IFilterGraph2 *pGraph;
					 ICaptureGraphBuilder2 *pCapture;
					 IMoniker *pMoniker;

					 DWORD dwRegister;
					 BITMAPINFOHEADER *pbmi;

					 
	};
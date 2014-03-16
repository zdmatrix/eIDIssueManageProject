#ifndef _DIRECT_XCOMMENT_H
#define _DIRECT_XCOMMENT_H

using namespace System;
using namespace System::Windows::Forms;

//#define HED

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

public class CSampleGrabberCB : public ISampleGrabberCB 
{

public:

    // These will get set by the main thread below. We need to
    // know this in order to write out the bmp
    long Width;
    long Height;

    // Fake out any COM ref counting
    //
    STDMETHODIMP_(ULONG) AddRef() { return 2; }
    STDMETHODIMP_(ULONG) Release() { return 1; }

    // Fake out any COM QI'ing
    //
    STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
    {
		if(ppv == NULL){
			return E_POINTER;
		}
        
        if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown ) 
        {
            *ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
            return NOERROR;
        }    

        return E_NOINTERFACE;
    }


    // We don't implement this one
    //
    STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )
    {
        return 0;
    }


    // The sample grabber is calling us back on its deliver thread.
    // This is NOT the main app thread!
    //
    STDMETHODIMP BufferCB( double SampleTime, BYTE * pBuffer, long BufferSize )
    {
        //
        // Convert the buffer into a bitmap
        //
        TCHAR szFilename[MAX_PATH];
        wsprintf(szFilename, TEXT("Bitmap%5.5ld.bmp\0"), long( SampleTime * 1000 ) );

        // Create a file to hold the bitmap
        HANDLE hf = CreateFile(szFilename, GENERIC_WRITE, FILE_SHARE_READ, 
                               NULL, CREATE_ALWAYS, NULL, NULL );

        if( hf == INVALID_HANDLE_VALUE )
        {
            return 0;
        }

//        _tprintf(TEXT("Found a sample at time %ld ms\t[%s]\r\n"), 
//               long( SampleTime * 1000 ), szFilename );

        // Write out the file header
        //
        BITMAPFILEHEADER bfh;
        memset( &bfh, 0, sizeof( bfh ) );
        bfh.bfType = 'MB';
        bfh.bfSize = sizeof( bfh ) + BufferSize + sizeof( BITMAPINFOHEADER );
        bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );

        DWORD Written = 0;
        WriteFile( hf, &bfh, sizeof( bfh ), &Written, NULL );

        // Write the bitmap format
        //
        BITMAPINFOHEADER bih;
        memset( &bih, 0, sizeof( bih ) );
        bih.biSize = sizeof( bih );
        bih.biWidth = Width;
        bih.biHeight = Height;
        bih.biPlanes = 1;
        bih.biBitCount = 24;

        Written = 0;
        WriteFile( hf, &bih, sizeof( bih ), &Written, NULL );

        // Write the bitmap bits
        //
        Written = 0;
        WriteFile( hf, pBuffer, BufferSize, &Written, NULL );

        CloseHandle( hf );

        return 0;
    }
};


public ref class CaptureVideoComment{
	
	public:
		
		

		DWORD dwRegister;
		bool bCaptureDevConnect;

		String^ strCaptureDevName;

		BITMAPINFOHEADER *pbmi;
		
		IGraphBuilder *pGraphManager;
		ICaptureGraphBuilder2 *pCapture;
		ISampleGrabber *pGrabber;
		IVideoWindow  *pVW;
		IMediaControl *pMC;
		IMediaControl *pCaptureMC;
		IMediaEventEx *pME;
		IBaseFilter *pCaptureBaseFilter;
		IBaseFilter *pGrabberBaseFilter;
		IBaseFilter *pNullRender;
		IPin *pGrabberOutPin;

			
	HRESULT GreatFilterGraph(){
		
		HRESULT hr;
		cli::pin_ptr<IGraphBuilder *> ppGraphManager = &pGraphManager;
		cli::pin_ptr<ICaptureGraphBuilder2 *> ppCapture = &pCapture;
		
		if(!ppGraphManager || !ppCapture){
			return E_POINTER;
		}
		
		hr = CoCreateInstance (
			CLSID_FilterGraph, 
			NULL,
			CLSCTX_INPROC_SERVER,   //for add grephedit
            IID_IGraphBuilder, 
			(void **) ppGraphManager
			);
		if (FAILED(hr)){
			MessageBox::Show("Initial IFilterGraph2 failed!");
			return E_NOINTERFACE;
		}	
		


		// Create the capture graph builder
		 hr = CoCreateInstance (
			 CLSID_CaptureGraphBuilder2, 
			 NULL, 
			 CLSCTX_INPROC_SERVER,
             IID_ICaptureGraphBuilder2, 
			 (void **) ppCapture
			 );
		 if (FAILED(hr)){
			 MessageBox::Show("Initial ICaptureGraphBuilder2 failed!");
			 return E_NOINTERFACE;
		 }		 
		return S_OK;
	}

	
	HRESULT CreatGrabberFilter(){
		
		HRESULT hr;
		cli::pin_ptr<IBaseFilter *> ppGrabberBaseFilter = &pGrabberBaseFilter;
		
		hr = CoCreateInstance(
			CLSID_SampleGrabber, 
			NULL, 
			CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, 
			(void**)ppGrabberBaseFilter
			);
		

		if (FAILED(hr))
		{
			MessageBox::Show("Couldn't create sample grabber filter base!");
			return E_NOINTERFACE;
		} 
		

		cli::pin_ptr<ISampleGrabber *> ppGrabber = &pGrabber;
		
		pGrabberBaseFilter->QueryInterface(IID_ISampleGrabber, (void**)ppGrabber);
		
		AM_MEDIA_TYPE mt;
		ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
		mt.majortype = MEDIATYPE_Video;
		mt.subtype = MEDIASUBTYPE_RGB24;
		hr = pGrabber->SetMediaType(&mt);
		FreeMediaType(mt);

		return hr;
	}

	
	HRESULT CreatCaptureFilter(){
	    
		HRESULT hr;
		ULONG cFetched;
		const char* CAPTUREDEVNAME;
		

#ifdef HED
		CAPTUREDEVNAME = "USB  ”∆µ…Ë±∏";
#else
		CAPTUREDEVNAME = "Microsoft LifeCam HD-3000";
#endif

		cli::pin_ptr<IBaseFilter *> ppCaptureBaseFilter = &pCaptureBaseFilter;
	   
		// Create the system device enumerator
		ICreateDevEnum *pDevEnum =NULL;
		
		hr = CoCreateInstance (
			CLSID_SystemDeviceEnum, 
			NULL, 
			CLSCTX_INPROC,
			IID_ICreateDevEnum, 
			(void **) &pDevEnum
			);
		if (FAILED(hr)){
			MessageBox::Show("Couldn't create system enumerator!");
			return E_NOINTERFACE;
		}

		// Create an enumerator for the video capture devices
		IEnumMoniker *pClassEnum = NULL;

		hr = pDevEnum->CreateClassEnumerator(
			CLSID_VideoInputDeviceCategory, 
			&pClassEnum, 
			0
			);

		if (FAILED(hr)){
			MessageBox::Show("Couldn't create class enumerator!");
			return E_NOINTERFACE;
		}

		// If there are no enumerators for the requested type, then 
		// CreateClassEnumerator will succeed, but pClassEnum will be NULL.
		if (pClassEnum == NULL){
			MessageBox::Show("No video capture device was detected.\r\n\r\n	  \
					This sample requires a video capture device, such as a USB WebCam,\r\n \
					to be installed and working properly.  The sample will now close. \
					No Video Capture Hardware");
			return E_FAIL;
		}

		IMoniker *pMoniker = NULL;

		// Use the first video capture device on the device list.
		// Note that if the Next() call succeeds but there are no monikers,
		// it will return S_FALSE (which is not a failure).  Therefore, we
		// check that the return code is S_OK instead of using SUCCEEDED() macro.
		if (S_OK == (pClassEnum->Next (1, &pMoniker, &cFetched))){

			// Bind Moniker to a filter object
			hr = pMoniker->BindToObject(0,0,IID_IBaseFilter, (void**)ppCaptureBaseFilter);
			
			IPropertyBag *pPropBag = NULL;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
			if (FAILED(hr)){
				pMoniker->Release();
				return E_NOINTERFACE;  
			} 
			
			VARIANT var;
			VariantInit(&var);

			// Get description or friendly name.
			hr = pPropBag->Read(L"Description", &var, 0);
			if (FAILED(hr)){
				hr = pPropBag->Read(L"FriendlyName", &var, 0);
			}

			if (SUCCEEDED(hr)){
				strCaptureDevName = String(var.bstrVal).ToString();
				if(!strCaptureDevName->CompareTo(String(CAPTUREDEVNAME).ToString())){
					hr = S_OK;
				}else{
					hr = E_FAIL;
					return hr;
				}
			}
			pPropBag->Release();
		}else{
			MessageBox::Show("Unable to access video capture device!");   
			return E_FAIL;
		}

		
		pMoniker->Release();
		pClassEnum->Release();
		pDevEnum->Release();
		// Copy the found filter pointer to the output parameter.
		// Do NOT Release() the reference, since it will still be used
		// by the calling function.

		return hr;

	}

	HRESULT CreatNullReanderFilter(){

		HRESULT hr;
		cli::pin_ptr<IBaseFilter *> ppNullRender = &pNullRender;
		 hr = CoCreateInstance(
			 CLSID_NullRenderer,
			 NULL,
			 CLSCTX_INPROC_SERVER,
			 IID_IBaseFilter,
			 (void **)ppNullRender
			 );
		 if (FAILED(hr)){
			MessageBox::Show("Couldn't create Null Render!");
			return E_NOINTERFACE;
		 }
		 return hr;
	}

	HRESULT BuiltFilterGraph(){
		
		HRESULT hr;
		pGraphManager->AddFilter(pCaptureBaseFilter, L"HED eID Capture Device");
		pGraphManager->AddFilter(pGrabberBaseFilter, L"Sample Grabber Filter");
		pGraphManager->AddFilter(pNullRender, L"Null Render");

		pCapture->SetFiltergraph(pGraphManager);

		pCapture->RenderStream(
			&PIN_CATEGORY_PREVIEW,
			 &MEDIATYPE_Video,
			 pCaptureBaseFilter,
			 NULL,
			 NULL
			);

		pCapture->RenderStream(
			&PIN_CATEGORY_CAPTURE,
			 &MEDIATYPE_Video,
			 pCaptureBaseFilter,
			 NULL,
			 pGrabberBaseFilter
			);

		hr = ConnectFilters(pGraphManager, pGrabberBaseFilter, pNullRender);

		cli::pin_ptr<IVideoWindow *> ppVW = &pVW;
		cli::pin_ptr<IMediaControl *> ppMC = &pMC;
		cli::pin_ptr<IMediaEventEx *> ppME = &pME;

		hr = pGraphManager->QueryInterface(IID_IMediaControl,(LPVOID *) ppMC);
		 if (FAILED(hr)){
			MessageBox::Show("Initial IMediaControl failed!");
			return E_NOINTERFACE;
		 }
		 	 
		 hr = pGraphManager->QueryInterface(IID_IMediaEvent, (LPVOID *) ppME);
		 if (FAILED(hr)){
			MessageBox::Show("Initial IMediaEventEx failed!");
			return E_NOINTERFACE;
		 }
		 
		 hr = pGraphManager->QueryInterface(IID_IVideoWindow, (LPVOID *) ppVW);
		 if (FAILED(hr)){
			MessageBox::Show("Initial IVideoWindow failed!");
			return E_NOINTERFACE;
		 }	

	}

	
	HRESULT ConnectFilters(
		IGraphBuilder *pGraph, // Filter Graph Manager.
		IPin *pOut,            // Output pin on the upstream filter.
		IBaseFilter *pDest)    // Downstream filter.
	{
		IPin *pIn = NULL;
	        
		// Find an input pin on the downstream filter.
		HRESULT hr = FindUnconnectedPin(pDest, PINDIR_INPUT, &pIn);
		if (SUCCEEDED(hr))
		{
			// Try to connect them.
			hr = pGraph->Connect(pOut, pIn);
			pIn->Release();
		}
		return hr;
	}

	HRESULT ConnectFilters(IGraphBuilder *pGraph, IBaseFilter *pSrc, IPin *pIn)
	{
		IPin *pOut = NULL;
	        
		// Find an output pin on the upstream filter.
		HRESULT hr = FindUnconnectedPin(pSrc, PINDIR_OUTPUT, &pOut);
		if (SUCCEEDED(hr))
		{
			// Try to connect them.
			hr = pGraph->Connect(pOut, pIn);
			pOut->Release();
		}
		return hr;
	}

	HRESULT ConnectFilters(IGraphBuilder *pGraph, IBaseFilter *pSrc, IBaseFilter *pDest){
		IPin *pOut = NULL;

		// Find an output pin on the first filter.
		HRESULT hr = FindUnconnectedPin(pSrc, PINDIR_OUTPUT, &pOut);
		if (SUCCEEDED(hr))
		{
			hr = ConnectFilters(pGraph, pOut, pDest);
			pOut->Release();
		}
		return hr;
	}

		
	HRESULT FindUnconnectedPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin)
	{
		IEnumPins *pEnum = NULL;
		IPin *pPin = NULL;
		BOOL bFound = FALSE;

		HRESULT hr = pFilter->EnumPins(&pEnum);
		if (FAILED(hr))
		{
			goto done;
		}

		while (S_OK == pEnum->Next(1, &pPin, NULL))
		{
			hr = MatchPin(pPin, PinDir, FALSE, &bFound);
			if (FAILED(hr))
			{
				goto done;
			}
			if (bFound)
			{
				*ppPin = pPin;
				(*ppPin)->AddRef();
				break;
			}
			SafeRelease(&pPin);
		}

		if (!bFound)
		{
			hr = VFW_E_NOT_FOUND;
		}

	done:
		SafeRelease(&pPin);
		SafeRelease(&pEnum);
		return hr;
	}

	HRESULT MatchPin(IPin *pPin, PIN_DIRECTION direction, BOOL bShouldBeConnected, BOOL *pResult)
	{
		if(pResult == NULL){
			return -1;
		}

		BOOL bMatch = FALSE;
		BOOL bIsConnected = FALSE;

		HRESULT hr = IsPinConnected(pPin, &bIsConnected);
		if (SUCCEEDED(hr))
		{
			if (bIsConnected == bShouldBeConnected)
			{
				hr = IsPinDirection(pPin, direction, &bMatch);
			}
		}

		if (SUCCEEDED(hr))
		{
			*pResult = bMatch;
		}
		return hr;
	}

	HRESULT IsPinDirection(IPin *pPin, PIN_DIRECTION dir, BOOL *pResult)
	{
		PIN_DIRECTION pinDir;
		HRESULT hr = pPin->QueryDirection(&pinDir);
		if (SUCCEEDED(hr))
		{
			*pResult = (pinDir == dir);
		}
		return hr;
	}

	HRESULT IsPinConnected(IPin *pPin, BOOL *pResult)
	{
		IPin *pTmp = NULL;
		HRESULT hr = pPin->ConnectedTo(&pTmp);
		if (SUCCEEDED(hr))
		{
			*pResult = TRUE;
		}
		else if (hr == VFW_E_NOT_CONNECTED)
		{
			// The pin is not connected. This is not an error for our purposes.
			*pResult = FALSE;
			hr = S_OK;
		}

		SafeRelease(&pTmp);
		return hr;
	}

		
	HRESULT GetPin( IBaseFilter * pFilter, PIN_DIRECTION dirrequired, int iNum, IPin **ppPin){
		IEnumPins *pEnum;
		*ppPin = NULL;

		HRESULT hr = pFilter->EnumPins(&pEnum);
		if(FAILED(hr)) 
			return hr;

		ULONG ulFound;
		IPin *pPin;
		hr = E_FAIL;

		while(S_OK == pEnum->Next(1, &pPin, &ulFound))
		{
			PIN_DIRECTION pindir = (PIN_DIRECTION)3;

			pPin->QueryDirection(&pindir);
			if(pindir == dirrequired)
			{
				if(iNum == 0)
				{
					*ppPin = pPin;  // Return the pin's interface
					hr = S_OK;      // Found requested pin, so clear error
					break;
				}
				iNum--;
			} 

			pPin->Release();
		} 

		return hr;
	}


	IPin * GetInPin( IBaseFilter * pFilter, int nPin ){
		IPin *pComPin = NULL;
		GetPin(pFilter, PINDIR_INPUT, nPin, &pComPin);
		return pComPin;
	}


	IPin * GetOutPin( IBaseFilter * pFilter, int nPin ){
		IPin *pComPin = NULL;
		GetPin(pFilter, PINDIR_OUTPUT, nPin, &pComPin);
		return pComPin;
	}

	HRESULT WriteBitmap(LPCSTR pszFileName, BITMAPINFOHEADER *pBMI, size_t cbBMI,BYTE *pData, size_t cbData){
		HANDLE hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL, 
			CREATE_ALWAYS, 0, NULL);
		if (hFile == NULL)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		BITMAPFILEHEADER bmf = { };

		bmf.bfType = 'MB';
		bmf.bfSize = cbBMI+ cbData + sizeof(bmf); 
		bmf.bfOffBits = sizeof(bmf) + cbBMI; 

		DWORD cbWritten = 0;
		BOOL result = WriteFile(hFile, &bmf, sizeof(bmf), &cbWritten, NULL);
		if (result)
		{
			result = WriteFile(hFile, pBMI, cbBMI, &cbWritten, NULL);
		}
		if (result)
		{
			result = WriteFile(hFile, pData, cbData, &cbWritten, NULL);
		}

		HRESULT hr = result ? S_OK : HRESULT_FROM_WIN32(GetLastError());

		CloseHandle(hFile);

		return hr;
	}

	HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister){
		IMoniker * pMoniker = NULL;
		IRunningObjectTable *pROT = NULL;

		if (FAILED(GetRunningObjectTable(0, &pROT))) 
		{
			return E_FAIL;
		}
	    
		const size_t STRING_LENGTH = 256;

		WCHAR wsz[STRING_LENGTH];
	 
	   StringCchPrintfW(
			wsz, STRING_LENGTH, 
			L"FilterGraph %08x pid %08x", 
			(DWORD_PTR)pUnkGraph, 
			GetCurrentProcessId()
			);
	    
		HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
		if (SUCCEEDED(hr)) 
		{
			hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph,
				pMoniker, pdwRegister);
			pMoniker->Release();
		}
		pROT->Release();
	    
		return hr;
	}


	void RemoveFromRot(DWORD pdwRegister){
		IRunningObjectTable *pROT;
		if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
			pROT->Revoke(pdwRegister);
			pROT->Release();
		}
	}
};

#endif
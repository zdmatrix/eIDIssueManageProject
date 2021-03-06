#include "stdafx.h"
#include "DSComment.h"
#include "CSampleGrabber.h"

#define HED

using namespace System;
using namespace System::Windows::Forms;


	HRESULT DSComment::CreatNullRender(){
		HRESULT hr;
		cli::pin_ptr<IBaseFilter *> ppNullRenderFilter = &pNullRenderFilter;

		hr = CoCreateInstance(
			CLSID_NullRenderer,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IBaseFilter,
			(void **)ppNullRenderFilter
			);
		return hr;
	}

			
	HRESULT DSComment::CreatFilterGraph(){
		
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

	
	HRESULT DSComment::CreatGrabberFilter(){
		
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

	
	HRESULT DSComment::CreatCaptureFilter(){
	    
		HRESULT hr;
		ULONG cFetched;
		const char* CAPTUREDEVNAME;
		

#ifdef HED
		CAPTUREDEVNAME = "USB ��Ƶ�豸";
#else
		CAPTUREDEVNAME = "Microsoft LifeCam HD-3000";
#endif

		cli::pin_ptr<IBaseFilter *> ppCaptureBaseFilter = &pCaptureBaseFilter;
//		cli::interior_ptr<IBaseFilter *> ppCaptureBaseFilter = &pCaptureBaseFilter;
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
			
			pDevEnum->Release();
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
				String^ strCaptureDevName = String(var.bstrVal).ToString();
				if(!strCaptureDevName->CompareTo(String(CAPTUREDEVNAME).ToString())){
					hr = S_OK;
				}else{
					hr = E_FAIL;
					pMoniker->Release();
					pClassEnum->Release();
					pDevEnum->Release();
					
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

	

	HRESULT DSComment::BuiltFilterGraph(){
		
		HRESULT hr;
		pGraphManager->AddFilter(pCaptureBaseFilter, L"HED eID Capture Device");
		pGraphManager->AddFilter(pGrabberBaseFilter, L"HED eID Sample Grabber Filter");

//		pGraphManager->AddFilter(pNullRenderFilter, L"HED eID Null Render");

		pCapture->SetFiltergraph(pGraphManager);

		pCapture->RenderStream(
			&PIN_CATEGORY_CAPTURE,
//			&PIN_CATEGORY_PREVIEW,
			 &MEDIATYPE_Video,
			 pCaptureBaseFilter,
			 pGrabberBaseFilter,
			 NULL
//			 pNullRenderFilter
			);

		
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

	void DSComment::SetVideoWindows(HWND pWnd){
		
		RECT rc;

		pVW->put_Owner((OAHWND)pWnd);
		
		// Make the preview video fill our window
		GetClientRect((HWND)pWnd, &rc);
		pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);

		// Set video window style
		pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);

		// Make the video window visible, now that it is properly positioned
		pVW->put_Visible(OATRUE);
	}

	void DSComment::DestroyFilter(){
		
//		pMC->Stop();


		if(pGraphManager != nullptr){
		   pGraphManager->Release();
		}
		if(pCapture != nullptr){
			pCapture->Release();
		}
		if(pNullRenderFilter != nullptr){
			pNullRenderFilter->Release();
		}
		if(pGrabber != nullptr){
			pGrabber->Release();
		}
		if(pVW != nullptr){
			pVW->Release();
		}
		if(pMC != nullptr){
			pMC->Release();
		}
		if(pME != nullptr){
			pME->Release();
		}
		if(pCaptureBaseFilter != nullptr){
			pCaptureBaseFilter->Release();
		}
		if(pGrabberBaseFilter != nullptr){
			pGrabberBaseFilter->Release();
		}
		
	}


	BYTE* DSComment::SnapStillImage(long* size){
		
		HRESULT hr;

		pMC->Stop();

		hr = pGrabber->SetBufferSamples( TRUE );

			// Only grab one at a time, stop stream after
			// grabbing one sample
			//
		hr = pGrabber->SetOneShot( FALSE );

		pMC->Run();

		//for test 
/*
		long EvCode=0;
        hr = pME->WaitForCompletion( INFINITE, &EvCode );


		int *eve = new int[100];
		int i = 0;
		


		long evCode, param1, param2;

while (hr = pME->GetEvent(&evCode, &param1, &param2, 0), SUCCEEDED(hr))
{
    
	eve[i] = evCode;
	i ++;
	switch(evCode) 
    { 
        // Call application-defined functions for each 
        // type of event that you want to handle.
	case EC_BUFFERING_DATA:
		MessageBox::Show("Get one");
		break;
    } 
	
    hr = pME->FreeEventParams(evCode, param1, param2);
}
*/
		//test end

		Sleep(500);
		

		
		long cbBuffer;
		hr = pGrabber->GetCurrentBuffer(&cbBuffer, NULL);
		if (FAILED(hr))
		{
			MessageBox::Show("GetCurrentBuffer Fail!");	
		}

//		BYTE *pBuffer = (BYTE*)CoTaskMemAlloc(cbBuffer);
		BYTE *pBuffer = new BYTE(cbBuffer);
		if (!pBuffer) 
		{
			MessageBox::Show("CoTaskMemAlloc Fail!");
		}

		hr = pGrabber->GetCurrentBuffer(&cbBuffer, (long*)pBuffer);
		if (FAILED(hr))
		{
			MessageBox::Show("GetCurrentBuffer Fail!");
			
		}
		
		

		AM_MEDIA_TYPE mt;

		hr = pGrabber->GetConnectedMediaType(&mt);
		if (FAILED(hr))
		{
			MessageBox::Show("GetConnectedMediaType Fail!");
			
		}

		VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)mt.pbFormat;

		long cbBMI = mt.cbFormat - SIZE_PREHEADER;

		long captureSize = cbBMI + cbBuffer + sizeof(BITMAPFILEHEADER);
		*size = captureSize;
//		BYTE *pCaptrue = (BYTE*)CoTaskMemAlloc(captureSize);
		BYTE *pCaptrue = new BYTE(captureSize);

		BITMAPFILEHEADER bmf = { };
		

		bmf.bfType = 'MB';
		bmf.bfSize = captureSize; 
		bmf.bfOffBits = sizeof(bmf) + cbBMI; 

		memcpy(pCaptrue, &bmf, sizeof(bmf));
		
		memcpy((pCaptrue + sizeof(bmf)), &pVih->bmiHeader, cbBMI);
		memcpy((pCaptrue + sizeof(bmf) + cbBMI), pBuffer, cbBuffer);
	
		return pCaptrue;		

	}


	BYTE* DSComment::SampleStillImage(long &size){
		
		HRESULT hr;
		CSampleGrabberCB *CB = new CSampleGrabberCB;

		pMC->Stop();

		AM_MEDIA_TYPE mt;

		hr = pGrabber->GetConnectedMediaType(&mt);
		if (FAILED(hr))
		{
			MessageBox::Show("GetConnectedMediaType Fail!");

		}

		VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)mt.pbFormat;

		
		
		CB->lWidth = pVih->bmiHeader.biWidth;
		CB->lHeight = pVih->bmiHeader.biHeight;

		CB->bSnapOneShot = true;

		long captureSize = CB->lHeight * CB->lWidth * 3;		

		long cbBMI = mt.cbFormat - SIZE_PREHEADER;

		long imageSize = cbBMI + captureSize + sizeof(BITMAPFILEHEADER);

		size = imageSize;
			
		BITMAPFILEHEADER bmf = { };

		bmf.bfType = 'MB';
		bmf.bfSize = captureSize; 
		bmf.bfOffBits = sizeof(bmf) + cbBMI;


		BYTE *pImageTmp = new BYTE[imageSize];
		
		

		hr = pGrabber->SetBufferSamples( FALSE );

			// Only grab one at a time, stop stream after
			// grabbing one sample
			//
		hr = pGrabber->SetOneShot( FALSE );

		hr = pGrabber->SetCallback(CB, 1);

		pMC->Run();

		while(CB->bSnapOneShot){
			;	
		}

		memcpy(pImageTmp, &bmf, sizeof(bmf));

		memcpy((pImageTmp + sizeof(bmf)), &pVih->bmiHeader, cbBMI);
		memcpy((pImageTmp + sizeof(bmf) + cbBMI), CB->pCapture, imageSize);

		return pImageTmp;
				
	}


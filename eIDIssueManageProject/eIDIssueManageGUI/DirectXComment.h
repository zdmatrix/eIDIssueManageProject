#ifndef _DIRECT_XCOMMENT_H
#define _DIRECT_XCOMMENT_H


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

#endif
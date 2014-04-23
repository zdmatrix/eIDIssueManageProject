// PCSCReaderDriverDll.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PCSCReaderDriverDll.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif



#define MAX_USB_DEVICE 16



typedef struct tagPCSCReader_STATE 
{
	int data;
}PCSCReader_STATE, *PPCSCReader_STATE;

SCARD_IO_REQUEST	IO_Request;
SCARDCONTEXT		ContextHandle;

unsigned long		ret;
unsigned char		ReaderName[100][255];
unsigned long		ReaderID;
unsigned long		ReaderStatus[10][2];

DWORD ActiveProtocol;

PPCSCReader_STATE g_RefCount;




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}


void AddRef(void)
{

}

BOOL CanReleaseRef(void)
{
	
	return TRUE;
}


void DebugMessage(long ret)
{
#ifdef WRITE_DEBUG_MESSAGE

	char szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	PathRemoveFileSpec(szPath);

	strcat(szPath, "\\PCSCReaderDriverDll_DEBUGINFO.txt");
	FILE *f = fopen(szPath, "a+");
	GetErrorCode(ret);
	fprintf(f, "%x==%s", DevNo, message);
	fclose(f);
#endif
}

char* GetErrorCode(long ret)
{
	char MessageBuffer[255];

	switch (ret) {
		case SCARD_E_CANCELLED:
			sprintf(MessageBuffer,"The action was cancelled by an SCardCancel request.");
//			MessageBox(NULL,"The action was cancelled by an SCardCancel request.","Err",MB_OK);
			break;

		case SCARD_E_CANT_DISPOSE:
			sprintf(MessageBuffer,"The system could not dispose of the media in the requested manner.");
//			MessageBox(NULL,"The system could not dispose of the media in the requested manner.","Err",MB_OK);
			break;
		case SCARD_E_CARD_UNSUPPORTED:
			sprintf(MessageBuffer,"The smart card does not meet minimal requirements for support.");
//			MessageBox(NULL,"The smart card does not meet minimal requirements for support.","Err",MB_OK);
			break;
		case SCARD_E_DUPLICATE_READER:
			sprintf(MessageBuffer,"The reader driver didn't produce a unique reader name.");
//			MessageBox(NULL,"The reader driver didn't produce a unique reader name.","Err",MB_OK);
			break;
		case SCARD_E_INSUFFICIENT_BUFFER:
			sprintf(MessageBuffer,"The data buffer to receive returned data is too small for the returned data.");
//			MessageBox(NULL,"The data buffer to receive returned data is too small for the returned data.","Err",MB_OK);
			break;
		case SCARD_E_INVALID_ATR:
			sprintf(MessageBuffer,"An ATR obtained from the registry is not a valid ATR string.");
//			MessageBox(NULL,"An ATR obtained from the registry is not a valid ATR string.","Err",MB_OK);
			break;
		case SCARD_E_INVALID_HANDLE:
			sprintf(MessageBuffer,"The supplied handle was invalid.");
//			MessageBox(NULL,"The supplied handle was invalid.","Err",MB_OK);
			break;
		case SCARD_E_INVALID_PARAMETER:
			sprintf(MessageBuffer,"One or more of the supplied parameters could not be properly interpreted.");
//			MessageBox(NULL,"One or more of the supplied parameters could not be properly interpreted.","Err",MB_OK);
			break;
		case SCARD_E_INVALID_TARGET:
			sprintf(MessageBuffer,"Registry startup information is missing or invalid.");
//			MessageBox(NULL,"Registry startup information is missing or invalid.","Err",MB_OK);
			break;
		case SCARD_E_INVALID_VALUE:
			sprintf(MessageBuffer,"One or more of the supplied parameters?values could not be properly interpreted.");
//			MessageBox(NULL,"One or more of the supplied parameters?values could not be properly interpreted.","Err",MB_OK);
			break;
		case SCARD_E_NOT_READY:
			sprintf(MessageBuffer,"The reader or card is not ready to accept commands.");
//			MessageBox(NULL,"The reader or card is not ready to accept commands.","Err",MB_OK);
			break;
		case SCARD_E_NOT_TRANSACTED:
			sprintf(MessageBuffer,"An attempt was made to end a non-existent transaction.");
//			MessageBox(NULL,"An attempt was made to end a non-existent transaction.","Err",MB_OK);
			break;
		case SCARD_E_NO_MEMORY:
			sprintf(MessageBuffer,"Not enough memory available to complete this command.");
//			MessageBox(NULL,"Not enough memory available to complete this command.","Err",MB_OK);
			break;
		case SCARD_E_NO_SERVICE:
			sprintf(MessageBuffer,"The Smart card resource manager is not running.");
//			MessageBox(NULL,"The Smart card resource manager is not running.","Err",MB_OK);
			break;
		case SCARD_E_NO_SMARTCARD:
			sprintf(MessageBuffer,"The operation requires a smart card but no smart card is currently in the device.");
//			MessageBox(NULL,"The operation requires a smart card but no smart card is currently in the device.","Err",MB_OK);
			break;
		case SCARD_E_PCI_TOO_SMALL:
			sprintf(MessageBuffer,"The PCI Receive buffer was too small.");
//			MessageBox(NULL,"The PCI Receive buffer was too small.","Err",MB_OK);
			break;
		case SCARD_E_PROTO_MISMATCH:
			sprintf(MessageBuffer,"The requested protocols are incompatible with the protocol currently in use with the card.");
//			MessageBox(NULL,"The requested protocols are incompatible with the protocol currently in use with the card.","Err",MB_OK);
			break;
		case SCARD_E_READER_UNAVAILABLE:
			sprintf(MessageBuffer,"The specified reader is not currently available for use.");
//			MessageBox(NULL,"The specified reader is not currently available for use.","Err",MB_OK);
			break;
		case SCARD_E_READER_UNSUPPORTED:
			sprintf(MessageBuffer,"The reader driver does not meet minimal requirements for support.");
//			MessageBox(NULL,"The reader driver does not meet minimal requirements for support.","Err",MB_OK);
			break;
		case SCARD_E_SERVICE_STOPPED:
			sprintf(MessageBuffer,"The Smart card resource manager has shut down.");
//			MessageBox(NULL,"The Smart card resource manager has shut down.","Err",MB_OK);
			break;
		case SCARD_E_SHARING_VIOLATION:
			sprintf(MessageBuffer,"The card cannot be accessed because of other connections outstanding.");
//			MessageBox(NULL,"The card cannot be accessed because of other connections outstanding.","Err",MB_OK);
			break;
		case SCARD_E_SYSTEM_CANCELLED:
			sprintf(MessageBuffer,"The action was cancelled by the system presumably to log off or shut down.");
//			MessageBox(NULL,"The action was cancelled by the system presumably to log off or shut down.","Err",MB_OK);
			break;
		case SCARD_E_TIMEOUT:
			sprintf(MessageBuffer,"The user-specified timeout value has expired.");
//			MessageBox(NULL,"The user-specified timeout value has expired.","Err",MB_OK);
			break;
		case SCARD_E_UNKNOWN_CARD:
			sprintf(MessageBuffer,"The specified card name is not recognized.");
//			MessageBox(NULL,"The specified card name is not recognized.","Err",MB_OK);
			break;
		case SCARD_E_UNKNOWN_READER:
			sprintf(MessageBuffer,"The specified reader name is not recognized.");
//			MessageBox(NULL,"The specified reader name is not recognized.","Err",MB_OK);
			break;
		case SCARD_F_COMM_ERROR:
			sprintf(MessageBuffer,"An internal communications error has been detected.");
//			MessageBox(NULL,"An internal communications error has been detected.","Err",MB_OK);
			break;
		case SCARD_F_INTERNAL_ERROR:
			sprintf(MessageBuffer,"An internal consistency check failed.");
//			MessageBox(NULL,"An internal consistency check failed.","Err",MB_OK);
			break;
		case SCARD_F_UNKNOWN_ERROR:
			sprintf(MessageBuffer,"An internal error has been detected but the source is unknown.");
//			MessageBox(NULL,"An internal error has been detected but the source is unknown.","Err",MB_OK);
			break;
		case SCARD_F_WAITED_TOO_LONG:
			sprintf(MessageBuffer,"An internal consistency timer has expired.");
//			MessageBox(NULL,"An internal consistency timer has expired.","Err",MB_OK);
			break;
		case SCARD_S_SUCCESS:
			sprintf(MessageBuffer,"SCARD_S_SUCCESS.");
//			MessageBox(NULL,"SCARD_S_SUCCESS","OK",MB_OK);
			break;
		case SCARD_W_REMOVED_CARD:
			sprintf(MessageBuffer,"The card has been removed so that further communication is not possible.");
//			MessageBox(NULL,"The card has been removed so that further communication is not possible.","Err",MB_OK);
			break;
		case SCARD_W_RESET_CARD:
//			sprintf(MessageBuffer,"The card has been reset so any shared state information is invalid.");
			MessageBox(NULL,"The card has been reset so any shared state information is invalid.","Err",MB_OK);
			break;
		case SCARD_W_UNPOWERED_CARD:
			sprintf(MessageBuffer,"Power has been removed from the card so that further communication is not possible.");
//			MessageBox(NULL,"Power has been removed from the card so that further communication is not possible.","Err",MB_OK);
			break;
		case SCARD_W_UNRESPONSIVE_CARD:
			sprintf(MessageBuffer,"The card is not responding to a reset.");
//			MessageBox(NULL,"The card is not responding to a reset.","Err",MB_OK);
			break;
		case SCARD_W_UNSUPPORTED_CARD:
			sprintf(MessageBuffer,"The reader cannot communicate with the card due to ATR configuration conflicts.");
//			MessageBox(NULL,"The reader cannot communicate with the card due to ATR configuration conflicts.","Err",MB_OK);
			break;
		default:
			sprintf(MessageBuffer,"Function returned 0x%X error code.", ret);
//			MessageBox(NULL, MessageBuffer,"Err",MB_OK);
			break;
	}
	return MessageBuffer;
}



//��������
/**********************************************************************************************
1.HD_ContextInitialize
�����豸���������ͨ/USB KEY ͨѶǰ�����ȴ��豸��
unsigned short HD_ContextInitialize(
	HANDLE *ContextNo			//���ص�������

)

����˵��
ContextNo	���ص�������

����ֵ
��������0x9000��ʾ��ȷ����ʱdevNo��Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ContextInitialize(HANDLE *ContextNo)
{
	SCARDCONTEXT		ContextHandle;
	//
	//	Open a context which communication to the Resource Manager
	//
	ret = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ContextHandle);

	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return CER_PCSC_SCardEstablishContext ;
	}

	*ContextNo = (HANDLE)ContextHandle;

	return EXCUTE_SUC ;	

}

/**********************************************************************************************
2.HD_ContextRelease
�����豸���������ͨ/USB KEY ͨѶǰ�����ȴ��豸��
unsigned short HD_ContextRelease(
	HANDLE ContextNo				//������
)

����˵��
ContextNo			������

����ֵ
��������0x9000��ʾ��ȷ����ʱdevNo��Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ContextRelease(HANDLE ContextNo)
{
//	if( ContextHandle == NULL)
//		return EXCUTE_SUC ;	
	//
	//The SCardReleaseContext function closes an established resource manager context, 
	//freeing any resources allocated under that context, 
	//including SCARDHANDLE objects and memory allocated using the SCARD_AUTOALLOCATE 
	//length designator.
	//

	ret = SCardReleaseContext((SCARDCONTEXT) ContextNo);

	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return CER_PCSC_SCardReleaseContext;
	}

	//ContextNo = NULL;

	return EXCUTE_SUC ;	

}

/**********************************************************************************************
3.HD_GetReaderList
�����豸���������ͨ/USB KEY ͨѶǰ�����ȴ��豸��
unsigned short HD_GetReaderList(
	HANDLE ContextNo,				//������
	unsigned long * ReaderNo,		//����ֵ���豸��ʶ�б�
	unsigned long * ReaderCount		//����ֵ���豸����
)

����˵��
ContextNo		������
ReaderNo 		����ֵ���豸��ʶ�б�	
ReaderCount		����ֵ���豸������

����ֵ
��������0x9000��ʾ��ȷ����ʱdevNo��Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_GetReaderList(HANDLE ContextNo, int * ReaderNo, int * ReaderCount )
{
	SCARDHANDLE	CardHandle;
	unsigned char ResponseBuffer[4096];
	unsigned long ResponseLength;
	int i,j, StringLen;
	unsigned char ReaderNameTmp[255];

	//
	//The SCardListCards function searches the smart card database 
	//and provides a list of named cards previously introduced to the system by the user.
	//
	//The caller specifies an ATR string, a set of interface identifiers (GUIDs), or both. 
	//If both an ATR string and an identifier array are supplied, the cards returned 
	//will match the ATR string supplied and support the interfaces specified.
	//

	ret = SCardListReaders((SCARDCONTEXT)ContextNo, NULL, NULL, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return(CER_PCSC_SCardListReaders);
	}

	ret = SCardListReaders((SCARDCONTEXT)ContextNo, NULL, (char *)ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return(CER_PCSC_SCardListReaders);
	}

	j=0;
	ReaderID = 0;
	StringLen = 0;
	while ((unsigned long)StringLen<ResponseLength-1)
	{
		strcpy((char*)ReaderNameTmp,(char*)ResponseBuffer+StringLen);
		
		ret = SCardConnect((SCARDCONTEXT)ContextNo, (char *)ReaderNameTmp, SCARD_SHARE_DIRECT, 0, &CardHandle, &ActiveProtocol);
		if ((ret == SCARD_S_SUCCESS)||(ret == SCARD_W_REMOVED_CARD))
		{
			j++;
			ReaderStatus[j-1][0]=0;
			ReaderStatus[j-1][1]=0;
			SCardDisconnect(CardHandle, SCARD_EJECT_CARD);
		}
		StringLen = StringLen+strlen((char*)ReaderNameTmp);
		StringLen = StringLen+1;
	}

	*ReaderCount = j;
	ReaderID = j;

	for (i=0;i<j;i++)
		 ReaderNo[i] = i+1;
	
	return EXCUTE_SUC ;	

}


/**********************************************************************************************
4.HD_OpenPort
�����豸���������ͨ/USB KEY ͨѶǰ�����ȴ��豸��


����˵��

ivPortNo 		���ڱ��: Windows�п�����1��2��3��4��	
                USB �˿ڱ��: 21, 22, 23, 24
				PCSC�豸���: ����ReaderName��Ӧѡ��
devicename		����������,�ж��Ƿ���ָ���Ķ�����,
devNo			���ص��豸��

����ֵ
��������0x9000��ʾ��ȷ����ʱdevNo��Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/
unsigned short DecHstr( unsigned long ivDec, short ivNum, char *srHex )
{
	char str[20];
	int i, slen;

	srHex[0] = '\0';
	sprintf( str, "%X", ivDec);
	slen = strlen( str);
	if( ivNum == 0)
	{
		if( slen%2 == 1)
		{
			strcat( srHex, "0");
			strcat( srHex, str);
		}
		else
			strcat( srHex, str);
	}
	else if( slen < 2*ivNum)
	{
		for( i=slen; i<2*ivNum; i++)
			strcat(srHex, "0");
		strcat(srHex, str);
	}
	else 
		strcat( srHex, str+slen-2*ivNum);

	return 0;
}

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_OpenPort(short ivPortNo, const char* devicename, HANDLE* devNo)
{
	SCARDHANDLE	CardHandle=NULL;
//	unsigned long ActiveProtocol;

///////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Open a context which communication to the Resource Manager
	//
	ret = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ContextHandle);
	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return CER_PCSC_SCardEstablishContext ;
	}


	unsigned char ResponseBuffer[4096];
	unsigned long ResponseLength;
	int StringLen,port;
	unsigned char ReaderNameTmp[255];

	int slen;

	//
	//The SCardListCards function searches the smart card database 
	//and provides a list of named cards previously introduced to the system by the user.
	//
	//The caller specifies an ATR string, a set of interface identifiers (GUIDs), or both. 
	//If both an ATR string and an identifier array are supplied, the cards returned 
	//will match the ATR string supplied and support the interfaces specified.
	//

	ret = SCardListReaders(ContextHandle, NULL, NULL, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return(CER_PCSC_SCardListReaders);
	}

	ret = SCardListReaders(ContextHandle, NULL, (char *)ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);
		DebugMessage(ret);
		return(CER_PCSC_SCardListReaders);
	}

	StringLen = 0;
	
	if (ivPortNo>20)
	{
		port = ivPortNo-21;
	}
	else
	{
		port = ivPortNo-1;
	}

	//DecHstr( port, 1, strtmp );

	strcpy((char*)ReaderNameTmp,(char*)ResponseBuffer+StringLen);
	slen = strlen((char *)ReaderNameTmp);
	//�������ָ���Ķ�������

	if (memcmp((char *)ReaderNameTmp, (char*)devicename, slen) != 0)		
	{
		while (StringLen < ResponseLength) 
		{
			StringLen = StringLen+strlen((char*)ReaderNameTmp);
			StringLen = StringLen+1;
			strcpy((char*)ReaderNameTmp,(char*)ResponseBuffer+StringLen);
			if (memcmp((char *)ReaderNameTmp, (char*)devicename, slen) == 0)
				break;
		}
		DebugMessage(ERR_PCSC_READER_NOT_FOUND);
	}


		ret = SCardConnect(ContextHandle, (char *)ReaderNameTmp, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0, &CardHandle, &ActiveProtocol);
		//ActiveProtocol = SCARD_PROTOCOL_T0;
		if (ret != SCARD_S_SUCCESS)
		{
			
			DebugMessage(ret);
			if (CardHandle==NULL)
			{
				return CER_NOCARD;
			}
			return CER_PCSC_SCardConnect ;
		}

	*devNo =(HANDLE) CardHandle;
		
	return EXCUTE_SUC ;	

}

/**********************************************************************************************
5  HD_ResetCard 
�����ܿ������ϵ縴λ��ȡ�ø�λӦ����Ϣ��

unsigned short HD_ResetCard(		
	HANDLE 			devNo,
	char			*srATR,			
    short			*srATRLen,
	short 			ivCardSeat	//USB�ӿڲ�ʹ��
)

����˵��
devNo			    ��HD_OpenPort���ص��豸��
srATR            	����յ�������
srATRLen			��Ž��յ������ݵĳ���
ivCardSeat			�����š�1����������2:������

����ֵ
��������0x9000��ʾ��ȷ����ʱsrATR������Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ������ʱsrATR������Ч��

ע������
�ú��������󣬿���RST�ܽ�Ϊ�ߵ�ƽ�������빤��״̬�������صĸ�λӦ���ֽڴ���srATR�����С�
***********************************************************************************************/

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ResetCard( HANDLE devNo, unsigned char	*srATR, short	*srATRLen, short ivCardSeat)
{
//	DWORD ActiveProtocol;
	DWORD dwCardState=0;
	BYTE  AtrBuffer[32];
	DWORD AtrLen ;

//	LPTSTR cardname;
	char cardname[256];
	DWORD dw = 0;
	BYTE buf[32];

//	ret = SCardStatus((SCARDHANDLE)devNo, NULL, NULL, &dwCardState, &ActiveProtocol, NULL, &AtrLen);
	ret = SCardStatus((SCARDHANDLE)devNo, cardname, &dw, &dwCardState, &ActiveProtocol, buf, &AtrLen);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardStatus;
	}

	switch ( dwCardState )
	{
		case SCARD_ABSENT:
	//		printf("Card absent.\n");
			return CER_NOCARD;

		case SCARD_SWALLOWED:
	//        printf("Card swallowed.\n");

			//
			//The SCardReconnect function reestablishes an existing connection between 
			//the calling application and a smart card. 
			//This function moves a card handle from direct access to general access, 
			//or acknowledges and clears an error condition that is preventing further 
			//access to the card.
			//

			//SCARD_LEAVE_CARD  Don't do anything special on reconnect. 
			//SCARD_RESET_CARD  Reset the card (Warm Reset). 
			//SCARD_UNPOWER_CARD  Power down the card and reset it (Cold Reset).
			ret = SCardReconnect((SCARDHANDLE)devNo,SCARD_SHARE_SHARED , ActiveProtocol , SCARD_UNPOWER_CARD , &ActiveProtocol);
			if (ret != SCARD_S_SUCCESS)
			{
				GetErrorCode(ret);
				return CER_PCSC_SCardReconnect;
			}

			break;

		case SCARD_PRESENT:
	//        printf("Card present.\n");
		case SCARD_NEGOTIABLE:
	//        printf("Card reset and waiting PTS negotiation.\n");
		case SCARD_SPECIFIC:
	//        printf("Card has specific communication protocols set.\n");

			//
			//The SCardReconnect function reestablishes an existing connection between 
			//the calling application and a smart card. 
			//This function moves a card handle from direct access to general access, 
			//or acknowledges and clears an error condition that is preventing further 
			//access to the card.
			//

			//SCARD_LEAVE_CARD  Don't do anything special on reconnect. 
			//SCARD_RESET_CARD  Reset the card (Warm Reset). 
			//SCARD_UNPOWER_CARD  Power down the card and reset it (Cold Reset). 

			ret = SCardReconnect((SCARDHANDLE)devNo,SCARD_SHARE_SHARED , ActiveProtocol, SCARD_RESET_CARD , &ActiveProtocol);
			if (ret != SCARD_S_SUCCESS)
			{
				//GetErrorCode(ret);
				return CER_PCSC_SCardReconnect;
			}
			break;

		case SCARD_POWERED:
	//        printf("Card has power.\n");

			//
			//The SCardReconnect function reestablishes an existing connection between 
			//the calling application and a smart card. 
			//This function moves a card handle from direct access to general access, 
			//or acknowledges and clears an error condition that is preventing further 
			//access to the card.
			//

			//SCARD_LEAVE_CARD  Don't do anything special on reconnect. 
			//SCARD_RESET_CARD  Reset the card (Warm Reset). 
			//SCARD_UNPOWER_CARD  Power down the card and reset it (Cold Reset). 
/*
			ret = SCardReconnect((SCARDHANDLE)devNo,SCARD_SHARE_SHARED , SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1 , SCARD_RESET_CARD , &ActiveProtocol);
			if (ret != SCARD_S_SUCCESS)
			{
//				GetErrorCode(ret);
				return CER_PCSC_SCardReconnect;
			}
*/			break;

		default:
	//        printf("Unknown or unexpected card state.\n");
			return CER_UNKNOWN;
	}

	AtrLen = 0x20;		//Microsoft Define Atrlen<=0x20;
	ret = SCardStatus((SCARDHANDLE)devNo, NULL, NULL, &dwCardState, &ActiveProtocol, (LPBYTE)&AtrBuffer, &AtrLen);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardStatus;
	}

		
	*srATRLen = (short)AtrLen;
	memcpy(srATR, AtrBuffer, AtrLen);

	/*if ((memcmp(srATR+4,"\x00\x81",2)!=0)&&(memcmp(srATR+5,"\x00\x81",2)!=0)&&(memcmp(srATR+7,"\x00\x81",2)!=0)&&(memcmp(srATR+4,"\x86\x01",2)!=0)&&(memcmp(srATR+5,"\x86\x01",2)!=0)&&(memcmp(srATR+7,"\x86\x01",2)!=0))
	{
		return CER_NOCARD;
	}
*/
	return EXCUTE_SUC ;	

}

/**********************************************************************************************
6  HD_ClosePort
�ر��豸���ú����ر���HD_OpenPort�����򿪵��豸��
unsigned short HD_ClosePort(
	HANDLE devNo
)

����˵��
devNo				��HD_OpenPort���ص��豸��

����ֵ
��������0x9000��ʾ��ȷ�� ����ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/
//PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ClosePort(short ivPortNo, HANDLE devNo)
PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ClosePort(HANDLE devNo)
{
	
	if( ContextHandle == NULL)
		return EXCUTE_SUC ;	

	if (!CanReleaseRef())
	{
		if (g_RefCount)
			DebugMessage(1);
		else
			DebugMessage(1);
		return EXCUTE_SUC;
	}
	//
	//The SCardDisconnect function terminates a connection previously opened 
	//between the calling application and a smart card in the target reader.
	//

	//SCARD_LEAVE_CARD  Don't do anything special. 
	//SCARD_RESET_CARD  Reset the card. 
	//SCARD_UNPOWER_CARD  Power down the card. 
	//SCARD_EJECT_CARD  Eject the card. 

/*	ret = SCardDisconnect((SCARDHANDLE)devNo, SCARD_UNPOWER_CARD);
	if (ret != SCARD_S_SUCCESS)
	{
//	    MessageBox(NULL,"CER_PCSC_SCardDisconnect","Err",MB_OK);
//		GetErrorCode(ret);
		return CER_PCSC_SCardDisconnect ;	
	}
	
 
	ret = SCardCancel(ContextHandle);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardCancel;
	}*/


	//
	//The SCardReleaseContext function closes an established resource manager context, 
	//freeing any resources allocated under that context, 
	//including SCARDHANDLE objects and memory allocated using the SCARD_AUTOALLOCATE 
	//length designator.
	//

	ret = SCardReleaseContext(ContextHandle);
	if (ret != SCARD_S_SUCCESS)
	{
		GetErrorCode(ret);
		return CER_PCSC_SCardReleaseContext;
	}

	ContextHandle = NULL;

//	ReaderStatus[ivPortNo-1][1]=0;
	return EXCUTE_SUC ;	
}

/**********************************************************************************************
7  HD_PowerOn
�����ϵ硣�ϵ�����󣬿���Vcc�ܽ�Ϊ5V,CLK�ܽ��ṩһ��3.684MHz���ȶ�ʱ�ӣ�RST�ܽ�Ϊ�͵�ƽ��I/O�ܽ�Ϊ�ߵ�ƽ��

unsigned short  HD_PowerOn(
HANDLE 		devNo,
short  		ivCardSeat	//USB�ӿڲ�ʹ��
)

����˵��
devNo			    ��HD_OpenPort���ص��豸��
ivCardSeat		    �����š�1����������2:������

����ֵ
��������0x9000��ʾ��ȷ�� ����ֵ��ʾ����������Ϣ������ġ�������Ϣ����

ע������
�ú��������󣬿����ڸ�λ״̬����RST�ܽ�Ϊ�͵�ƽ��
***********************************************************************************************/

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_PowerOn(HANDLE devNo, short ivCardSeat)
{
//	DWORD ActiveProtocol;

	//
	//The SCardReconnect function reestablishes an existing connection between 
	//the calling application and a smart card. 
	//This function moves a card handle from direct access to general access, 
	//or acknowledges and clears an error condition that is preventing further 
	//access to the card.
	//

	//SCARD_LEAVE_CARD  Don't do anything special on reconnect. 
	//SCARD_RESET_CARD  Reset the card (Warm Reset). 
	//SCARD_UNPOWER_CARD  Power down the card and reset it (Cold Reset). 
	
//	ret = SCardReconnect((SCARDHANDLE)devNo,SCARD_SHARE_SHARED , SCARD_PROTOCOL_T0 , SCARD_UNPOWER_CARD , &ActiveProtocol);
	ret = SCardReconnect((SCARDHANDLE)devNo,SCARD_SHARE_SHARED , ActiveProtocol , SCARD_UNPOWER_CARD , &ActiveProtocol);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardReconnect;
	}

	return EXCUTE_SUC ;
}

/**********************************************************************************************
8  HD_PowerOff
�����ϵ硣�ú����ɹ���ɺ󣬿��ĸ��ܽ������������롣

unsigned short HD_PowerOff(
	HANDLE 		devNo,
	short 		ivCardSeat	//USB�ӿڲ�ʹ��
)

����˵��
devNo			��HD_OpenPort���ص��豸��
ivCardSeat		�����š�1����������2:������

����ֵ
��������0x9000��ʾ��ȷ�� ����ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_PowerOff(	HANDLE 	devNo,short	ivCardSeat)
{
	//
	//The SCardDisconnect function terminates a connection previously opened 
	//between the calling application and a smart card in the target reader.
	//

	//SCARD_LEAVE_CARD  Don't do anything special. 
	//SCARD_RESET_CARD  Reset the card. 
	//SCARD_UNPOWER_CARD  Power down the card. 
	//SCARD_EJECT_CARD  Eject the card. 

/*	ret = SCardDisconnect((SCARDHANDLE)devNo, SCARD_LEAVE_CARD);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardDisconnect;
	}
*/
	return EXCUTE_SUC ;
}

/**********************************************************************************************
3  HD_SetTimeout
���ó�ʱʱ�䡣���ڷ�ʽ����Ч��

unsigned short HD_SetTimeout(
    HANDLE 		devNo, 
	int 		ivTimeOut,	 // ʱ�䣬��msΪ��λ
	short 		type  		 // TimeOut����
)

����˵��
devNo		 	��HD_OpenPort���ص��豸��
ivTimeOut       ʱ��, ��msΪ��λ
type			TimeOut����(���궨��)��
				type = 0 ����PC�˿ڳ�ʱʱ��(�ȴ������������ݣ�
				type = 1 ���ö��������ڳ�ʱʱ�䣨�ȴ�PC�����ݣ�
				type = 2 ���ÿ���λӦ��ʱʱ�� (�������ȴ�3B��ʱ�䣩
				type = 3 ���ÿ���Ӧ��ʱʱ�� ���ȴ�����һ��״̬�ֽڵ�ʱ�䣩
				type = 4 ���ÿ��ּ�೬ʱʱ�� ���ȴ������������ֽڵ�ʱ�䣩
				��ivTimeOut = 0, PC�˿ڵȴ�ʱ�����޳���ϵͳȱʡֵΪ1s��

����ֵ
��������0x9000��ʾ��ȷ�� ����ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/
PCSCREADERDRIVERDLL_API unsigned short CCONV HD_SetTimeout( HANDLE devNo,	int ivTimeOut, short type )
{
	return EXCUTE_SUC ;
}

/**********************************************************************************************
9 HD_ProbeCard
̽�⿨�����Ƿ��п����ڡ�

unsigned short HD_ProbeCard(
HANDLE 		devNo,
short 		ivCardSeat	//USB�ӿڲ�ʹ��
)		

����˵��
devNo			 ��HD_OpenPort���ص��豸��
ivCardSeat	 	 �����š�1����������2:������

����ֵ
��������0x0000ֵ��ʾ�޿����룬0x9000��ʾ�п�������ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/
void byte2str( char *svHex, unsigned char ivByte )
{
	char subs[5];

	sprintf( subs, "%02X", ivByte);
	strcat( svHex, subs );
	return;
}

//PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ProbeCard(HANDLE ContextNo, HANDLE devNo, short ivPortNo, short ivCardSeat)	
//PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ProbeCard(HANDLE ContextNo,  short ivPortNo, short ivCardSeat)	
PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ProbeCard(HANDLE devNo,short	ivCardSeat)		
{
	SCARDCONTEXT		ContextNo=NULL;
	
	ret = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ContextNo);
	if (ret != SCARD_S_SUCCESS) 
	{
//		GetErrorCode(ret);			
		return CER_PCSC_SCardEstablishContext ;
	}

	SCARD_READERSTATE udtReaderState[2];
	DWORD EventStatetpm;
	char Reader[300];

	strcpy(Reader,"Gemplus GemPC430 0\0");
	udtReaderState[0].szReader=Reader;
	//udtReaderState[0].dwCurrentState = SCARD_STATE_UNAVAILABLE;
	//udtReaderState[0].dwCurrentState = SCARD_STATE_PRESENT;
	udtReaderState[0].dwCurrentState = SCARD_STATE_UNAWARE;
//	udtReaderState[0].dwEventState = SCARD_STATE_UNKNOWN |SCARD_STATE_CHANGED|SCARD_STATE_IGNORE;
//	udtReaderState[0].dwEventState = SCARD_STATE_PRESENT;
//	udtReaderState[0].dwEventState = SCARD_STATE_EMPTY;
	ret = SCardGetStatusChange(ContextNo, 0, udtReaderState, 1);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
//		EventStatetpm = udtReaderState[0].dwEventState;
//		WriteLog("SCardGetStatusChange1", ivPortNo,EventStatetpm);
		SCardReleaseContext(ContextNo);
		ContextHandle = NULL;
		return CER_PCSC_SCardGetStatusChange;
	}
	EventStatetpm = udtReaderState[0].dwEventState;

	if ((EventStatetpm & 0x00000010)==0x00000010)	//0x00000010 -->SCARD_STATE_EMPTY
	{
//		GetErrorCode(ret);
		SCardReleaseContext(ContextNo);
		ContextHandle = NULL;
		return CER_NOCARD;
	}

	ret = SCardReleaseContext(ContextNo);
	if (ret != SCARD_S_SUCCESS)
	{
		GetErrorCode(ret);
		return CER_PCSC_SCardReleaseContext;
	}
	ContextNo = NULL;


	return EXCUTE_SUC;
}
/**********************************************************************************************
10  HD_ApduT0
���������,���������APDU Case1 Case2 Case3 Case4��ʽ��ָ�

unsigned short HD_ApduT0(				
    HANDLE 				devNo,
	char 				*apduData,
	short				srAPDULen,
	char 				*respData,
	short				*respDataLen,
	short 				ivCardSeat	//USB�ӿڲ�ʹ��
)

����˵��
devNo				��HD_OpenPort���ص��豸��
apduData			APDU����(�ֽڴ�)��CLA��INS��P1��P2�Լ�һ���ɱ䳤�ȵ�����������ʾ��������Ķ���ΪLc��Data��Lc���ֽڣ���Le��
					����Lc��Leֵ�Ĳ�ͬ����������������������±���ʾ��
					���	�ṹ
					1	CLA INS P1 P2
					2	CLA INS P1 P2 Le
					3	CLA INS P1 P2 Lc Data
					4	CLA INS P1 P2 Lc Data Le
srAPDULen			��ŷ��͵�APDU���ݵĳ���
respData			����Ӧ����
respDataLen			����Ӧ���ݵĳ���
ivCardSeat	 		������

����ֵ
��������0xffXX��ʾ����δ�ɹ�ִ�У�������Ϣ������ġ�������Ϣ��������ֵΪ������Ӧ��
������Case1�� Case2ʱ��respData�����塣������Case3�� Case4ʱ����������0x9000��respData�����壻������Ӧ��respData�����塣
***********************************************************************************************/
unsigned short isobase2(HANDLE devNo,unsigned char *svAPDU,short svAPDULen,unsigned char *srResp,short *srRespLen, short ivCardSet)
{
	BYTE  ResponseBuffer[2000];
	DWORD ResponseLength ;

	WORD retval = CER_PCSC_SCardTransmit_Data_LOST;

	*srRespLen = 0 ;
	*srResp = '\0' ;

//	IO_Request.dwProtocol = SCARD_PROTOCOL_T0;
	IO_Request.dwProtocol = ActiveProtocol;
	IO_Request.cbPciLength = (DWORD) sizeof(SCARD_IO_REQUEST);


	ResponseLength=2000;

	ret = SCardTransmit((SCARDHANDLE)devNo, &IO_Request, svAPDU, svAPDULen, 0, (BYTE *)&ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS)
	{
		DebugMessage(ret);
		return CER_PCSC_SCardTransmit;
	}

	if ( ResponseLength >= 2 )
	{

		retval = ((BYTE)ResponseBuffer[ResponseLength-2]) * 256 + (BYTE)ResponseBuffer[ResponseLength-1] ;

		*srRespLen = (short)ResponseLength - 2;
		memcpy(srResp,ResponseBuffer,ResponseLength-2);

	}
	else
	{
		DebugMessage(1);
		retval =  CER_PCSC_SCardTransmit_Data_LOST;
	}

	return retval ;
}

unsigned short isobase3(HANDLE devNo,unsigned char *svAPDU,short svAPDULen,unsigned char *srResp,short *srRespLen, short ivCardSet)
{
	BYTE  ResponseBuffer[2000];
	DWORD ResponseLength ;

	WORD retval = CER_PCSC_SCardTransmit_Data_LOST;


//	IO_Request.dwProtocol = SCARD_PROTOCOL_T1;
	IO_Request.dwProtocol = ActiveProtocol;
	IO_Request.cbPciLength = (DWORD) sizeof(SCARD_IO_REQUEST);

	
	ResponseLength=2000;

	ret = SCardTransmit((SCARDHANDLE)devNo, &IO_Request, svAPDU, svAPDULen, 0, (BYTE *)&ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS)
	{
		DebugMessage(ret);
		return CER_PCSC_SCardTransmit;
	}


	if ( ResponseLength >= 2 )
	{
		retval = ((BYTE)ResponseBuffer[ResponseLength-2]) * 256 + (BYTE)ResponseBuffer[ResponseLength-1] ;

		//if rf
		if(retval==0x9000)
		{
			*srRespLen = (short)ResponseLength - 2;
			memcpy(srResp,ResponseBuffer,ResponseLength-2);
		}
	}
	else
	{
		DebugMessage(1);
		retval =  CER_PCSC_SCardTransmit_Data_LOST;
	}

	return retval ;

}

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ApduT0( HANDLE devNo,  unsigned char *svAPDU, short srAPDULen, unsigned char *respData, short *respDataLen, short ivCardSeat )
{
	unsigned short retv;
//	unsigned char getresp[12];
	unsigned char tmpTPDU[600];

	*respData = '\0';

	if( srAPDULen < 4 || srAPDULen > 261 )
		return CER_APDU;			// �Ƿ�APDU�ֽ���

	memcpy( tmpTPDU, svAPDU,srAPDULen);
	
    // begin transaction locking
    // check that handle to card is valid
//     ret = SCardBeginTransaction((SCARDHANDLE)devNo);
// 	if (ret != SCARD_S_SUCCESS)
// 	{
// //		GetErrorCode(ret);
// 		return CER_PCSC_SCardBeginTransaction;
// 	}

	if (srAPDULen == 4)
	{
		// isocase = 1
		tmpTPDU[4]=0x00;
		retv = isobase2(devNo,tmpTPDU,5, respData, respDataLen, ivCardSeat); 
/*
		if(  HIBYTE(retv) == 0x61)
		{
			memcpy(getresp, "\x00\xC0\x00\x00",4);
			getresp[4]= LOBYTE(retv);

			retv = isobase2(devNo,getresp,5, respData, respDataLen, ivCardSeat);
		}
		else if(  HIBYTE(retv) == 0x6C)
		{
			tmpTPDU[4]= LOBYTE(retv);	// �����µ�Le�ֽ�
			retv = isobase2(devNo,tmpTPDU,5, respData, respDataLen, ivCardSeat); 
		}*/
	}

	else if( srAPDULen == 5 )
	{
		// isocase = 2
		retv = isobase2(devNo,tmpTPDU, 5,respData, respDataLen,ivCardSeat); 
		/*if(  HIBYTE(retv) == 0x61)
		{
			memcpy(getresp, "\x00\xC0\x00\x00",4);
			getresp[4]= LOBYTE(retv);

			retv = isobase2(devNo,getresp,5, respData, respDataLen, ivCardSeat);
		}
		else if(  HIBYTE(retv) == 0x6C)
		{
			tmpTPDU[4]= LOBYTE(retv);	// �����µ�Le�ֽ�
			retv = isobase2(devNo,tmpTPDU,5, respData, respDataLen, ivCardSeat); 
		}*/
	}

	else if( srAPDULen-5 == (unsigned char)svAPDU[4] )
	{
		// isocase = 3
		retv = isobase3(devNo,tmpTPDU,srAPDULen,respData, respDataLen, ivCardSeat); 

		/*if(  HIBYTE(retv) == 0x61)
		{
			memcpy(getresp, "\x00\xC0\x00\x00",4);
			getresp[4]= LOBYTE(retv);
			retv = isobase2(devNo,getresp,5, respData, respDataLen, ivCardSeat);
		}*/
		
	}
	else if( srAPDULen-6 == (unsigned char)svAPDU[4] )
	{
		// isocase = 4;
		retv = isobase3(devNo,tmpTPDU,srAPDULen-1,respData, respDataLen, ivCardSeat); // ȥ��Le
	/*	if(  HIBYTE(retv) == 0x61)
		{
			memcpy(getresp, "\x00\xC0\x00\x00",4);
			getresp[4]= LOBYTE(retv);
			retv = isobase2(devNo,getresp,5, respData, respDataLen, ivCardSeat);
		}*/
	}
	else
	{
		//SCardEndTransaction((SCARDHANDLE)devNo, SCARD_LEAVE_CARD);
		return CER_APDU;			// �Ƿ�APDU Case�ṹ
	}

    //end transaction locking
//     ret = SCardEndTransaction((SCARDHANDLE)devNo, SCARD_LEAVE_CARD);
// 	if (ret != SCARD_S_SUCCESS)
// 	{
// 		GetErrorCode(ret);
// 		return CER_PCSC_SCardEndTransaction;
// 	}

	return retv;
}

/**********************************************************************************************
11 HD_GetDescriptor
��ȡ�����豸����
   
unsigned short HD_GetDescriptor(		
	HANDLE 		devNo,		
	char 		*descriptor
)

����˵��
devNo			��HD_OpenPort���ص��豸��
descriptor		�����豸��Ϣ,����CI-4��˫����������������Ϣ����Ϊ��CIDC CI-4-1.0-009600��(ʮ�����ƴ�)
				����USBKey��Ӳ�����к��Ƕ�CPU IC����FORMATʱд�뿨�ڵ���ʷ�ֽ�

����ֵ
��������0x9000��ʾ��ȷ����ʱdescriptor��Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ������ʱdescriptor������Ч��
***********************************************************************************************/

void byte2str_chen( char *svHex, unsigned char ivByte )
{
	char subs[5];

	sprintf( subs, "%02X", ivByte);
	strcat( svHex, subs );
	return;
}

/******************************************************
���ַ������ұ�ȡָ����Ŀ���ַ�
��������:
srcData: Դ����
length: ��ȡ�ַ�������
resData: �������
***********************************************************/
unsigned short  HD_RightChar(char *srcData,unsigned short length,char *resData)          
{
	unsigned short len;
	
	 len=strlen(srcData);

	if((length>len)||(length<0))

		return -1;
		
    int i=len-length;

	strcpy(resData,(srcData+i));
	
	return 1;
}

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_GetDescriptor( HANDLE devNo, char *descriptor )
{
//	unsigned char tmpstr[100] ;
//	unsigned long pcbAttrLen;
//	unsigned short i;

	//
	//The SCardGetAttrib function gets the current reader attributes for the given handle. 
	//It does not affect the state of the reader, driver, or card.
	//
	
//	DWORD ActiveProtocol;
	DWORD dwCardState=0;
	BYTE  AtrBuffer[32];
	DWORD AtrLen ;
	short i;
	char tmpstr[100];

	ret = SCardStatus((SCARDHANDLE)devNo, NULL, NULL, &dwCardState, &ActiveProtocol, NULL, &AtrLen);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardStatus;
	}
/*
	ret = SCardGetAttrib((SCARDHANDLE)devNo, SCARD_ATTR_DEVICE_FRIENDLY_NAME, NULL, &pcbAttrLen);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardGetAttrib;
	}

	ret = SCardGetAttrib((SCARDHANDLE)devNo, SCARD_ATTR_DEVICE_FRIENDLY_NAME, tmpstr, &pcbAttrLen);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardGetAttrib;
	}

*/
	AtrLen = 0x20;		//Microsoft Define Atrlen<=0x20;
	ret = SCardStatus((SCARDHANDLE)devNo, NULL, NULL, &dwCardState, &ActiveProtocol, (LPBYTE)&AtrBuffer, &AtrLen);
	if (ret != SCARD_S_SUCCESS)
	{
//		GetErrorCode(ret);
		return CER_PCSC_SCardStatus;
	}

	descriptor[0] = '\0' ;
	tmpstr[0] = '\0';

	for( i=0 ; i < (short)AtrLen ; i++) 
		byte2str_chen(tmpstr,AtrBuffer[i]) ;

	HD_RightChar(tmpstr,26,descriptor);
	descriptor[26] = '\0' ;

//	SCardFreeMemory((SCARDCONTEXT)ContextNo,&pcbAttrLen);

	return EXCUTE_SUC ;

}

//##########################################################################
///test
//##########################################################################
// ��������ת������
bool checkhexstr_chen( char *str )
{
	int i, len;

	len = strlen( str );
	if( len%2 != 0 )
		return false;

	for( i=0; i<len; i++)
	{
		if( (str[i]<48 || str[i]>57)			// 0...9
			&& (str[i]<65 || str[i]>70)			// A...F
			&& (str[i]<97 || str[i]>102) )		// a...f
			return false;
	}

	return true;
}

int getbyte_chen( char *svHex, short num )
{
	char stds[] = "0123456789ABCDEF";
	char c[2];
	int a, b;

	if( (unsigned int)num > strlen(svHex)/2)
		return 0;

	c[0] = toupper(svHex[2*num-2]);
	c[1] = '\0';
	a = strcspn( stds, c );
	c[0] = toupper(svHex[2*num-1]);
	c[1] = '\0';
	b = strcspn( stds, c );
	
	return (a*16+b);
}

unsigned short WINAPI HD_HstrCstr_chen( char *svHex, unsigned char *srChar )
{
	int bc, i;

	srChar[0] = '\0';
	if( !checkhexstr_chen( svHex ))
		return CER_HEXSTR;		// �Ƿ�ʮ�����ƴ�

	bc = strlen( svHex ) / 2;
	for( i=0; i<bc; i++)
		srChar[i] = getbyte_chen( svHex, i+1);
	srChar[i] = '\0';

	return EXCUTE_SUC;
}
/*
void byte2str( char *svHex, unsigned char ivByte )
{
	char subs[5];

	sprintf( subs, "%02X", ivByte);
	strcat( svHex, subs );
	return;
}
*/
unsigned short WINAPI HD_CstrHstr_chen( unsigned char *svChar, short ivNum, short slen, char *srHex )
{
	int  i;//, slen
	char tmpHex[600];

	tmpHex[0] = '\0';
	//slen = strlen( svChar);
	for(i=0; i<slen; i++)
		byte2str_chen( tmpHex, svChar[i]);

	srHex[0] = '\0';
	slen = strlen(tmpHex) / 2;
	if( ivNum == 0 )
		sprintf(srHex, "%s", tmpHex);
	else if( ivNum < slen )
	{
		sprintf(srHex, "%s", tmpHex);
		return CER_RESULT;
	}
	else
	{
		for(i=0; i<ivNum-slen; i++)
			strcat(srHex, "00");
		strcat(srHex, tmpHex);
		//sprintf(srHex1, "%s", srHex);
	}

	return EXCUTE_SUC;
}

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ApduVB( HANDLE devNo, char *apduData, char *respData, short ivCardSeat )
{
	unsigned short retval;
	unsigned short ret;
	unsigned char resData[500],comm[500];
	short commlen,reslen;

	ret = HD_HstrCstr_chen(apduData,comm);
	commlen=strlen(apduData)/2;
	if (ret != 0x9000)
		return ret;

	retval = HD_ApduT0( devNo, comm, commlen, resData, &reslen, 1 );
//	if (retval != 0x9000)
//		return retval;
	resData[reslen]=0x00;

	ret = HD_CstrHstr_chen(resData,0,reslen,respData);
	if (ret != 0x9000)
		return ret;

	return retval;

}

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_ResetCardVB( HANDLE devNo, char *srATR, short ivCardSeat)
{
	unsigned short retval;
	unsigned char resData[255];
	short reslen;

	retval = HD_ResetCard( devNo, resData, &reslen, 1 );
	if (retval != 0x9000)
		return retval;
	resData[reslen]=0x00;

	retval = HD_CstrHstr_chen(resData,0,reslen,srATR);
	if (retval != 0x9000)
		return retval;
	return EXCUTE_SUC;

}


PCSCREADERDRIVERDLL_API unsigned short CCONV HD_OpenPath(unsigned char* DPath,HANDLE *devNo)
{
	return EXCUTE_SUC;
}

PCSCREADERDRIVERDLL_API unsigned short CCONV HD_GetProtocolType(short *ProtocolType)
{
	*ProtocolType= (short)ActiveProtocol;

	return 0x9000;
}

/**********************************************************************************************
3.HD_GetReaderNames
�����豸���������ͨ/USB KEY ͨѶǰ�����ȴ��豸��
unsigned short HD_GetReaderNames(
	unsigned long * ReaderNo,		//����ֵ���豸��ʶ�б�
	unsigned char * ResponseBuffer,	//����ֵ���豸����
	unsigned long * ReaderCount		//����ֵ���豸����
)

����˵��
ContextNo		������
ReaderNo 		����ֵ���豸��ʶ�б�
ResponseBuffer  ����ֵ���豸���ơ�	
ReaderCount		����ֵ���豸������

����ֵ
��������0x9000��ʾ��ȷ����ʱdevNo��Ч������ֵ��ʾ����������Ϣ������ġ�������Ϣ����
***********************************************************************************************/
PCSCREADERDRIVERDLL_API unsigned short CCONV HD_GetReaderNames(char *ReaderNames, int *Count)
{

	SCARDHANDLE	CardHandle;
//	unsigned char ResponseBuffer[4096];
	unsigned long ResponseLength;
	int i, j, StringLen;
	unsigned char ReaderNameTmp[255];
	SCARDCONTEXT		ContextNo=NULL;
	unsigned long ReaderNo[10];
	unsigned long ReaderCount=0;
	unsigned char ResponseBuffer[255];

	ContextHandle = -1;
	ret = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ContextNo);
	if (ret != SCARD_S_SUCCESS)
	{
		return(CER_PCSC_SCardEstablishContext);
	}

	ret = SCardListReaders((SCARDCONTEXT)ContextNo, NULL, NULL, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{	
		return(CER_PCSC_SCardListReaders);
	}

	ret = SCardListReaders((SCARDCONTEXT)ContextNo, NULL, (char *)ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{		
		return(CER_PCSC_SCardListReaders);
	}

	memcpy(ReaderNames,ResponseBuffer, ResponseLength);//add by hp

	j=0;
	ReaderID = 0;
	StringLen = 0;
	while ((unsigned long)StringLen<ResponseLength-1)
	{
		strcpy((char*)ReaderNameTmp,(char*)ResponseBuffer+StringLen);
		
		ret = SCardConnect((SCARDCONTEXT)ContextNo, (char *)ReaderNameTmp, SCARD_SHARE_DIRECT, SCARD_PROTOCOL_T0, &CardHandle, &ActiveProtocol);
		if ((ret == SCARD_S_SUCCESS)||(ret == SCARD_W_REMOVED_CARD))
		{
			strcpy((char*)ReaderName[j], (char*)ReaderNameTmp);			

			j++;
			ReaderStatus[j-1][0]=0;
			ReaderStatus[j-1][1]=0;
			SCardDisconnect(CardHandle, SCARD_EJECT_CARD);
		}
		StringLen = StringLen+strlen((char*)ReaderNameTmp);
		StringLen = StringLen+1;
	}

	ReaderCount = j;
	ReaderID = j;

	for (i=0;i<j;i++)
		 ReaderNo[i] = i+1;
		
	ret = SCardReleaseContext(ContextNo);
	if (ret != SCARD_S_SUCCESS)
	{
		GetErrorCode(ret);
		return CER_PCSC_SCardReleaseContext;
	}
	ContextNo = NULL;
	*Count= (int)ReaderCount; 

	return EXCUTE_SUC ;	
}

//���ݻ�ȡ�Ķ�������ʶ�б�ѡ��һ����������������
/*
	ReaderID ��0����
*/
PCSCREADERDRIVERDLL_API unsigned short CCONV HD_OpenPort2(short ReaderID, unsigned long ivBaud, short ivParity, HANDLE *devNo)
{
	SCARDHANDLE	CardHandle=NULL;
//	unsigned long ActiveProtocol;

///////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Open a context which communication to the Resource Manager
	//
	ret = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ContextHandle);
	if (ret != SCARD_S_SUCCESS) 
	{		
		return CER_PCSC_SCardEstablishContext ;
	}


	unsigned char ResponseBuffer[4096];
	unsigned long ResponseLength;
	int StringLen;
//	int port;
	unsigned char ReaderNameTmp[255];
//	char strtmp[10];
	int slen;
	int j;

	ret = SCardListReaders(ContextHandle, NULL, NULL, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{		
		return(CER_PCSC_SCardListReaders);
	}

	ret = SCardListReaders(ContextHandle, NULL, (char *)ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS) 
	{			
		return(CER_PCSC_SCardListReaders);
	}

	StringLen = 0;
	j=0;
/*	
	if (ivPortNo>20)
	{
		port = ivPortNo-21;
	}
	else
	{
		port = ivPortNo-1;
	}

	DecHstr( port, 1, strtmp );
*/	
	
//	while ((unsigned long)StringLen<ResponseLength-1)
	int i=0;
	while(i<=ReaderID)
	{
		strcpy((char*)ReaderNameTmp,(char*)ResponseBuffer+StringLen);

//		if ((strncmp((char*)ReaderNameTmp,"CIDC SMART CARD READER ",23)==0)&&(strncmp((char*)ReaderNameTmp+23,strtmp,1)==0))
		slen = strlen((char *)ReaderNameTmp);
		
		if (ReaderID==j)
		{
			ret = SCardConnect(ContextHandle, (char *)ReaderNameTmp, SCARD_SHARE_DIRECT, SCARD_PROTOCOL_T0, &CardHandle, &ActiveProtocol);
			if (ret == SCARD_S_SUCCESS)
				break;
		}
		StringLen = StringLen+strlen((char*)ReaderNameTmp);
		StringLen = StringLen+1;

		j++;
	}

	*devNo =(HANDLE) CardHandle;

	if (CardHandle==NULL) 
		return CER_PCSC_SCardConnect;
		
	return EXCUTE_SUC ;	

}


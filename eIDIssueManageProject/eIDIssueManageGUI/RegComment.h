#ifndef _REGCOMMENT_H
#define _REGCOMMENT_H

#include "PCSCReaderDriverDll.h"

using namespace System;

using namespace System::IO;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace System::Text;

public ref class RegComment{

private:
	const static char* cContactReader = "SCM Microsystems Inc. SDI011G Smart Card Reader 0";
	const static char* cContactlessReader = "SCM Microsystems Inc. SDI011G Contactless Reader 0";
/*
	const static byte cSelectCardManager[] = {0x00, 0xA4, 0x04, 0x00, 0x07, 0xA0, 0x00, 0x00, 0x01, 0x51, 0x00, 0x00, 0x00};
	static array<const char>^ cSelectCardManager = gcnew array< char>{
		0x00, 0xA4, 0x04, 0x00, 0x07, 0xA0, 0x00, 0x00, 0x01, 0x51, 0x00, 0x00, 0x00
	};
	static array<const char>^ cVerifyISD1 = gcnew array< char>{
		0x80, 0x50, 0x20, 0x00, 0x08, 0x16, 0xC5, 0x83, 0x57, 0x47, 0x86, 0x98, 0xCD, 0x00
	};
	static array<const char>^ cVerifyISD2 = gcnew array< char>{
		0x84, 0x82, 0x01, 0x00, 0x10, 0xDB, 0x39, 0x33, 0x1F, 0x41, 0x02, 0x42, 
		0xD5, 0x1D, 0x37, 0x48, 0x18, 0x85, 0x7B, 0xE7, 0xA3
	};

	
	const static String^ JCSHELL = "C:\\Program Files\\NXP Semiconductors Germany GmbH\\JCShell Standalone 2.0.0.1\\JCShell.exe";
	const static String^ SCRIPTNAME = "pse_issue";
	const static String^ SCRIPTNAME = "pse_register";
	const static String^ TERM = "/term";
	const static String^ SETPATH = "/set-var path d:/test";
*/	
	const static String^ CMDSHELL = "cmd";
	const static String^ JCSHELLPATH = "cd C:\\Program Files\\NXP Semiconductors Germany GmbH\\JCShell Standalone 2.0.0.1";
	const static String^ JCSHELL = "JCShell.exe";
	const static String^ SCRIPT = "pse_issue";
	
    const static int SELECT_CARD_MANAGER = 0xF0;
	const static int ISD_VERIFY = 0xF1;
	const static int KEY_UPDATE = 0xF0;
	const static int FCSD_VERIFY = 0xF0;
	const static int FCSD_CREATE = 0xF0;
	const static int FCSD_INIT = 0xF0;

	

	Process^ myProcess;
	StreamReader^ myStreamReader;

	StreamWriter^ myStreamWriter;

	array<Byte>^ info;

	String^ inputText;

public:

//	long OpenReader();
//	long SeclectCardManager(unsigned char* respdata);
//	void CloseReader();
//	long VerifyISD(unsigned char* respdata);
	
	void ProcessInit();
	void ProcessRun(String^ script);
	StreamReader^ GetStreamReader() {return myStreamReader;};
};

#endif
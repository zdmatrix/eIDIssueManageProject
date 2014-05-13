#include "stdafx.h"
#include "RegComment.h"
#include "PCSCReaderDriverDll.h"

using namespace System;


/*
long RegComment::OpenReader(){
	cli::pin_ptr<HANDLE> hhReader = &hReader;
	ret = HD_OpenPort(PORT, (char*)cContactReader, (HANDLE *)hhReader);
	return ret;
}

void RegComment::CloseReader(){
	
	HD_ClosePort(hReader);
	
}

long RegComment::SeclectCardManager(unsigned char* respData){
	short resplen = 0;
	short cmdlen = 13;

	ret = HD_ResetCard(hReader, respData, &resplen, 0);
	if(ret != 0x9000){
		return ret;
	}else{
		cli::pin_ptr<const char> cmd = &cSelectCardManager[0];
		if(hReader == NULL){
			return 0;
		}
		ret = HD_ApduT0(hReader, (unsigned char*)cmd, cmdlen, respData, &resplen, 0);
		return ret;
	}
	
}

long RegComment::VerifyISD(unsigned char* respData){
	short resplen = 0;
	short cmdlen = 14;

	
	cli::pin_ptr<const char> cmd1 = &cVerifyISD1[0];
	cli::pin_ptr<const char> cmd2 = &cVerifyISD2[0];
	if(hReader == NULL)
		return 0;
	
	ret = HD_ApduT0(hReader, (unsigned char*)cmd1, cmdlen, respData, &resplen, 0);
	if(ret != 0x9000){
		return ret;
	}else{
		cmdlen = 0x15;
		ret = HD_ApduT0(hReader, (unsigned char*)cmd2, cmdlen, respData, &resplen, 0); 
		return ret;
	}
}
*/

	

void RegComment::ProcessInit(){

	
	
}


//String^ RegComment::ProcessRun(String^ script){
void RegComment::ProcessRun(String^ script){

	myProcess = gcnew Process;
	
	myProcess->StartInfo->FileName = (String^)CMDSHELL;
	myProcess->StartInfo->UseShellExecute = false;
	myProcess->StartInfo->CreateNoWindow = true;
	myProcess->StartInfo->WindowStyle = ProcessWindowStyle::Hidden;
	//	myProcess->StartInfo->StandardOutputEncoding = Text::Encoding::UTF8;
	myProcess->StartInfo->RedirectStandardInput = true;
	myProcess->StartInfo->RedirectStandardOutput = true;
	myProcess->StartInfo->RedirectStandardError = true;

	myProcess->Start();
	myStreamReader = myProcess->StandardOutput;
	myStreamWriter = myProcess->StandardInput;

	inputText = (String^)JCSHELLPATH;
	myStreamWriter->WriteLine( inputText );

	inputText = "c:";
	myStreamWriter->WriteLine( inputText );


	inputText = (String^)JCSHELL;
	myStreamWriter->WriteLine( inputText );

	

	

	inputText = script;
	myStreamWriter->WriteLine( inputText );

	myStreamWriter->Close();
/*
	String^ str = myProcess->StandardOutput->ReadToEnd();
	myProcess->WaitForExit();
	str = str->Replace("\n", "\r\n");
	myStreamReader->Close();

	return str;
*/
}	


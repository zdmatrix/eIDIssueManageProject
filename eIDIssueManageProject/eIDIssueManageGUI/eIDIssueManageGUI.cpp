// eIDIssueManageGUI.cpp: ����Ŀ�ļ���

#include "stdafx.h"
#include "Form1.h"

using namespace eIDIssueManageGUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �ڴ����κοؼ�֮ǰ���� Windows XP ���ӻ�Ч��
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// ���������ڲ�������
	Application::Run(gcnew Form1());
	return 0;
}

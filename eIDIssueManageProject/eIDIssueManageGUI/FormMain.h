#pragma once

#include "FormLogIn.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace eIDIssueManageGUI {

	/// <summary>
	/// FormMain ժҪ
	///
	/// ����: ������Ĵ�������ƣ�����Ҫ����
	///          ����������������� .resx �ļ��������й���Դ���������ߵ�
	///          ����Դ�ļ��������ԡ�����
	///          �������������˴���Ĺ���
	///          ���ػ���Դ��ȷ������
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:

		FormLogIn^ formLogIn;

		FormMain(void)
		{
			formLogIn = gcnew FormLogIn();
			
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnMainExit;
	protected: 

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
			this->btnMainExit = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnMainExit
			// 
			this->btnMainExit->Location = System::Drawing::Point(92, 203);
			this->btnMainExit->Name = L"btnMainExit";
			this->btnMainExit->Size = System::Drawing::Size(75, 23);
			this->btnMainExit->TabIndex = 0;
			this->btnMainExit->Text = L"�˳�����";
			this->btnMainExit->UseVisualStyleBackColor = true;
			this->btnMainExit->Click += gcnew System::EventHandler(this, &FormMain::btnMainExit_Click);
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->btnMainExit);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormMain";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"eID���й���Ӧ��";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->Hide();
				 formLogIn->Activate();
				 formLogIn->ShowDialog(this);

			 }
	private: System::Void btnMainExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	};
}

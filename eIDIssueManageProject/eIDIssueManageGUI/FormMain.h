#pragma once

#include "FormLogIn.h"
#include "FormRegActive.h"

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
		FormRegActive^ formRegActive;
		String^ strIDName;
		String^ strIDSex;
		String^ strIDNation;

		FormMain(void)
		{
			formLogIn = gcnew FormLogIn();
			formRegActive = gcnew FormRegActive();
			
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

	private: System::Windows::Forms::Button^  btnRegActive;



	private: System::Windows::Forms::Button^  btnMainExit;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button4;
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
			this->btnRegActive = (gcnew System::Windows::Forms::Button());
			this->btnMainExit = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnRegActive
			// 
			this->btnRegActive->Location = System::Drawing::Point(60, 50);
			this->btnRegActive->Name = L"btnRegActive";
			this->btnRegActive->Size = System::Drawing::Size(86, 94);
			this->btnRegActive->TabIndex = 1;
			this->btnRegActive->Text = L"ע�ἤ��";
			this->btnRegActive->UseVisualStyleBackColor = true;
			this->btnRegActive->Click += gcnew System::EventHandler(this, &FormMain::btnRegActive_Click);
			// 
			// btnMainExit
			// 
			this->btnMainExit->Location = System::Drawing::Point(320, 172);
			this->btnMainExit->Name = L"btnMainExit";
			this->btnMainExit->Size = System::Drawing::Size(86, 94);
			this->btnMainExit->TabIndex = 0;
			this->btnMainExit->Text = L"�˳�����";
			this->btnMainExit->UseVisualStyleBackColor = true;
			this->btnMainExit->Click += gcnew System::EventHandler(this, &FormMain::btnMainExit_Click);
			// 
			// button3
			// 
			this->button3->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button3->Location = System::Drawing::Point(60, 172);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(86, 94);
			this->button3->TabIndex = 6;
			this->button3->Text = L"button1";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button1->Location = System::Drawing::Point(189, 50);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(86, 94);
			this->button1->TabIndex = 7;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button2->Location = System::Drawing::Point(189, 172);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(86, 94);
			this->button2->TabIndex = 8;
			this->button2->Text = L"button1";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button4->Location = System::Drawing::Point(320, 50);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(86, 94);
			this->button4->TabIndex = 9;
			this->button4->Text = L"button1";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(472, 326);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->btnRegActive);
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
	private: System::Void btnRegActive_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Hide();
				 formRegActive->Activate();
				 formRegActive->ShowDialog(this);
			 }
};
}

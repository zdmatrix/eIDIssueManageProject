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
	/// FormMain 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
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
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
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
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
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
			this->btnMainExit->Text = L"退出程序";
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
			this->Text = L"eID发行管理应用";
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

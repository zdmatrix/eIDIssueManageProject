#pragma once

#include "FormMain.h"

namespace eIDIssueManageGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// FormLogIn 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class FormLogIn : public System::Windows::Forms::Form
	{
	public:

		bool bIDVerified;
		String^ strLogInName;
		String^ strLogInPassword;

		FormMain^ formMain;

		FormLogIn(void)
		{
			
			bIDVerified = false;
			strLogInName = "";
			strLogInPassword = "";
			
			formMain = gcnew FormMain();
			
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~FormLogIn()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textLogInName;
	private: System::Windows::Forms::TextBox^  textLogInPassword;
	private: System::Windows::Forms::Button^  btnLogIn;
	private: System::Windows::Forms::Button^  btnQuit;
	protected: 

	protected: 

	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormLogIn::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textLogInName = (gcnew System::Windows::Forms::TextBox());
			this->textLogInPassword = (gcnew System::Windows::Forms::TextBox());
			this->btnLogIn = (gcnew System::Windows::Forms::Button());
			this->btnQuit = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(97, 149);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 21);
			this->label1->TabIndex = 0;
			this->label1->Text = L"用户名";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(97, 197);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 21);
			this->label2->TabIndex = 1;
			this->label2->Text = L"登录密码";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"隶书", 26.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(37, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(378, 69);
			this->label3->TabIndex = 2;
			this->label3->Text = L"eID发行管理应用程序";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textLogInName
			// 
			this->textLogInName->Location = System::Drawing::Point(181, 149);
			this->textLogInName->Name = L"textLogInName";
			this->textLogInName->Size = System::Drawing::Size(152, 21);
			this->textLogInName->TabIndex = 3;
			// 
			// textLogInPassword
			// 
			this->textLogInPassword->Location = System::Drawing::Point(181, 197);
			this->textLogInPassword->Name = L"textLogInPassword";
			this->textLogInPassword->Size = System::Drawing::Size(152, 21);
			this->textLogInPassword->TabIndex = 4;
			this->textLogInPassword->UseSystemPasswordChar = true;
			// 
			// btnLogIn
			// 
			this->btnLogIn->Location = System::Drawing::Point(100, 261);
			this->btnLogIn->Name = L"btnLogIn";
			this->btnLogIn->Size = System::Drawing::Size(91, 23);
			this->btnLogIn->TabIndex = 5;
			this->btnLogIn->Text = L"登录系统";
			this->btnLogIn->UseVisualStyleBackColor = true;
			this->btnLogIn->Click += gcnew System::EventHandler(this, &FormLogIn::btnLogIn_Click);
			// 
			// btnQuit
			// 
			this->btnQuit->Location = System::Drawing::Point(242, 261);
			this->btnQuit->Name = L"btnQuit";
			this->btnQuit->Size = System::Drawing::Size(91, 23);
			this->btnQuit->TabIndex = 6;
			this->btnQuit->Text = L"退出系统";
			this->btnQuit->UseVisualStyleBackColor = true;
			this->btnQuit->Click += gcnew System::EventHandler(this, &FormLogIn::btnQuit_Click);
			// 
			// FormLogIn
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(472, 326);
			this->Controls->Add(this->btnQuit);
			this->Controls->Add(this->btnLogIn);
			this->Controls->Add(this->textLogInPassword);
			this->Controls->Add(this->textLogInName);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormLogIn";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"eID发行管理登录界面";
			this->ResumeLayout(false);
			this->PerformLayout();
			

		}
#pragma endregion
	
	private: System::Void btnLogIn_Click(System::Object^  sender, System::EventArgs^  e) {
				 bIDVerified = bVerifyBackground(strLogInName, strLogInPassword);
				 if(bIDVerified){
					 this->Hide();
					 formMain->Activate();
					 formMain->ShowDialog(this);
				 }else{
					 MessageBox::Show("用户名/密码错误，请重新输入");
				 }
			 }
	private: System::Boolean bVerifyBackground(String^ logName, String^ logPin){
				 /*
				 for(int i = 0; i < 60000; i ++){
					 for(int i = 0; i < 10000; i ++){
						;
					 }		
				 }
				 */
				 bIDVerified = true;
				 return bIDVerified;
			 }
private: System::Void btnQuit_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
			 
		 }
};
}


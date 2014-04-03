#pragma once

//#include <uuids.h>
//#include <strsafe.h>
//#include "DirectXComment.h"
#include "DSComment.h"


//#define HED


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace System::IO;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;




namespace eIDIssueManageGUI {


	/// <summary>
	/// FormRegActive 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>

	

	public ref class FormRegActive : public System::Windows::Forms::Form
	{
	public:

		bool bIDInfo;
		bool bIDHeadPic;
		bool bIDReaderConnect;
		bool bCameraConnect;

		bool bCaptureStill;
		
		bool bReturnUpForm;

		HRESULT hr;

		DWORD dwRegister;

		String^ strInfoMessage;
		String^ strCaptureDevName;
		
		DSComment^ DS;
		
		

	private: System::Windows::Forms::Button^  btnCaptureIDInfo;
	private: System::Windows::Forms::Button^  btnCaptureHeadPic;
	private: System::Windows::Forms::PictureBox^  picCapture;
	private: System::Windows::Forms::Label^  label10;

	private: System::Windows::Forms::Label^  label11;



	public: 

		

		FormRegActive(void)
		{
			bIDInfo = false;
			bIDHeadPic = false;
			bIDReaderConnect = false;
			bCameraConnect = false;
			bReturnUpForm = false;
			bCaptureStill = false;

			DS = gcnew DSComment();
			
			
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~FormRegActive()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  picPriview;
	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textIDName;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textIDSex;
	private: System::Windows::Forms::TextBox^  textIDNation;
	private: System::Windows::Forms::TextBox^  textIDYear;
	private: System::Windows::Forms::TextBox^  textIDMonth;
	private: System::Windows::Forms::TextBox^  textIDDay;
	private: System::Windows::Forms::TextBox^  textIDLocation;
	private: System::Windows::Forms::TextBox^  textIDNum;







	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  btnRegActive;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormRegActive::typeid));
			this->picPriview = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textIDName = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textIDSex = (gcnew System::Windows::Forms::TextBox());
			this->textIDNation = (gcnew System::Windows::Forms::TextBox());
			this->textIDYear = (gcnew System::Windows::Forms::TextBox());
			this->textIDMonth = (gcnew System::Windows::Forms::TextBox());
			this->textIDDay = (gcnew System::Windows::Forms::TextBox());
			this->textIDLocation = (gcnew System::Windows::Forms::TextBox());
			this->textIDNum = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->btnRegActive = (gcnew System::Windows::Forms::Button());
			this->btnCaptureIDInfo = (gcnew System::Windows::Forms::Button());
			this->btnCaptureHeadPic = (gcnew System::Windows::Forms::Button());
			this->picCapture = (gcnew System::Windows::Forms::PictureBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picPriview))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picCapture))->BeginInit();
			this->SuspendLayout();
			// 
			// picPriview
			// 
			this->picPriview->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->picPriview->BackColor = System::Drawing::SystemColors::Control;
			this->picPriview->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->picPriview->Location = System::Drawing::Point(380, 35);
			this->picPriview->Name = L"picPriview";
			this->picPriview->Size = System::Drawing::Size(240, 180);
			this->picPriview->TabIndex = 0;
			this->picPriview->TabStop = false;
			this->picPriview->Tag = L"";
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(16, 71);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 23);
			this->label1->TabIndex = 1;
			this->label1->Text = L"姓名";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textIDName
			// 
			this->textIDName->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDName->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDName->Location = System::Drawing::Point(67, 69);
			this->textIDName->Name = L"textIDName";
			this->textIDName->ReadOnly = true;
			this->textIDName->Size = System::Drawing::Size(277, 29);
			this->textIDName->TabIndex = 2;
			this->textIDName->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(16, 119);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(42, 23);
			this->label2->TabIndex = 3;
			this->label2->Text = L"性别";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(163, 119);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 23);
			this->label3->TabIndex = 4;
			this->label3->Text = L"民族";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textIDSex
			// 
			this->textIDSex->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDSex->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDSex->Location = System::Drawing::Point(67, 117);
			this->textIDSex->Name = L"textIDSex";
			this->textIDSex->ReadOnly = true;
			this->textIDSex->Size = System::Drawing::Size(90, 29);
			this->textIDSex->TabIndex = 5;
			this->textIDSex->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textIDNation
			// 
			this->textIDNation->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDNation->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDNation->Location = System::Drawing::Point(212, 117);
			this->textIDNation->Name = L"textIDNation";
			this->textIDNation->ReadOnly = true;
			this->textIDNation->Size = System::Drawing::Size(132, 29);
			this->textIDNation->TabIndex = 6;
			this->textIDNation->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textIDYear
			// 
			this->textIDYear->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDYear->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDYear->Location = System::Drawing::Point(67, 171);
			this->textIDYear->Name = L"textIDYear";
			this->textIDYear->ReadOnly = true;
			this->textIDYear->Size = System::Drawing::Size(80, 29);
			this->textIDYear->TabIndex = 7;
			this->textIDYear->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textIDMonth
			// 
			this->textIDMonth->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDMonth->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDMonth->Location = System::Drawing::Point(185, 171);
			this->textIDMonth->Name = L"textIDMonth";
			this->textIDMonth->ReadOnly = true;
			this->textIDMonth->Size = System::Drawing::Size(47, 29);
			this->textIDMonth->TabIndex = 8;
			this->textIDMonth->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textIDDay
			// 
			this->textIDDay->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDDay->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDDay->Location = System::Drawing::Point(269, 171);
			this->textIDDay->Name = L"textIDDay";
			this->textIDDay->ReadOnly = true;
			this->textIDDay->Size = System::Drawing::Size(47, 29);
			this->textIDDay->TabIndex = 9;
			// 
			// textIDLocation
			// 
			this->textIDLocation->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDLocation->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDLocation->Location = System::Drawing::Point(67, 223);
			this->textIDLocation->Multiline = true;
			this->textIDLocation->Name = L"textIDLocation";
			this->textIDLocation->ReadOnly = true;
			this->textIDLocation->Size = System::Drawing::Size(277, 29);
			this->textIDLocation->TabIndex = 10;
			// 
			// textIDNum
			// 
			this->textIDNum->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textIDNum->Font = (gcnew System::Drawing::Font(L"宋体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textIDNum->Location = System::Drawing::Point(127, 307);
			this->textIDNum->Name = L"textIDNum";
			this->textIDNum->ReadOnly = true;
			this->textIDNum->Size = System::Drawing::Size(217, 29);
			this->textIDNum->TabIndex = 11;
			this->textIDNum->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(16, 173);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 23);
			this->label4->TabIndex = 12;
			this->label4->Text = L"出生";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label5->Location = System::Drawing::Point(16, 225);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(42, 23);
			this->label5->TabIndex = 13;
			this->label5->Text = L"住址";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label6->Location = System::Drawing::Point(153, 173);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(26, 23);
			this->label6->TabIndex = 14;
			this->label6->Text = L"年";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label7->Location = System::Drawing::Point(238, 173);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(25, 23);
			this->label7->TabIndex = 15;
			this->label7->Text = L"月";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label8->Location = System::Drawing::Point(322, 173);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(22, 23);
			this->label8->TabIndex = 16;
			this->label8->Text = L"日";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label9->Location = System::Drawing::Point(16, 309);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(105, 23);
			this->label9->TabIndex = 17;
			this->label9->Text = L"公民身份号码";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnRegActive
			// 
			this->btnRegActive->Enabled = false;
			this->btnRegActive->Location = System::Drawing::Point(290, 422);
			this->btnRegActive->Name = L"btnRegActive";
			this->btnRegActive->Size = System::Drawing::Size(75, 23);
			this->btnRegActive->TabIndex = 18;
			this->btnRegActive->Text = L"注册激活";
			this->btnRegActive->UseVisualStyleBackColor = true;
			this->btnRegActive->Click += gcnew System::EventHandler(this, &FormRegActive::btnRegActive_Click);
			// 
			// btnCaptureIDInfo
			// 
			this->btnCaptureIDInfo->Enabled = false;
			this->btnCaptureIDInfo->Location = System::Drawing::Point(67, 422);
			this->btnCaptureIDInfo->Name = L"btnCaptureIDInfo";
			this->btnCaptureIDInfo->Size = System::Drawing::Size(128, 23);
			this->btnCaptureIDInfo->TabIndex = 19;
			this->btnCaptureIDInfo->Text = L"开始采集身份证信息";
			this->btnCaptureIDInfo->UseVisualStyleBackColor = true;
			this->btnCaptureIDInfo->Click += gcnew System::EventHandler(this, &FormRegActive::btnCaptureIDInfo_Click);
			// 
			// btnCaptureHeadPic
			// 
			this->btnCaptureHeadPic->Enabled = false;
			this->btnCaptureHeadPic->Location = System::Drawing::Point(440, 422);
			this->btnCaptureHeadPic->Name = L"btnCaptureHeadPic";
			this->btnCaptureHeadPic->Size = System::Drawing::Size(128, 23);
			this->btnCaptureHeadPic->TabIndex = 20;
			this->btnCaptureHeadPic->Text = L"开始采集头像图片";
			this->btnCaptureHeadPic->UseVisualStyleBackColor = true;
			this->btnCaptureHeadPic->Click += gcnew System::EventHandler(this, &FormRegActive::btnCaptureHeadPic_Click);
			// 
			// picCapture
			// 
			this->picCapture->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->picCapture->BackColor = System::Drawing::SystemColors::Control;
			this->picCapture->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->picCapture->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picCapture.InitialImage")));
			this->picCapture->Location = System::Drawing::Point(380, 223);
			this->picCapture->Name = L"picCapture";
			this->picCapture->Size = System::Drawing::Size(240, 180);
			this->picCapture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->picCapture->TabIndex = 21;
			this->picCapture->TabStop = false;
			this->picCapture->Tag = L"";
			// 
			// label11
			// 
			this->label11->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label11->Location = System::Drawing::Point(448, 9);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(84, 23);
			this->label11->TabIndex = 23;
			this->label11->Text = L"视频预览";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label10->Location = System::Drawing::Point(148, 9);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(84, 23);
			this->label10->TabIndex = 24;
			this->label10->Text = L"身份信息";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FormRegActive
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(632, 457);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->picCapture);
			this->Controls->Add(this->btnCaptureHeadPic);
			this->Controls->Add(this->btnCaptureIDInfo);
			this->Controls->Add(this->btnRegActive);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textIDNum);
			this->Controls->Add(this->textIDLocation);
			this->Controls->Add(this->textIDDay);
			this->Controls->Add(this->textIDMonth);
			this->Controls->Add(this->textIDYear);
			this->Controls->Add(this->textIDNation);
			this->Controls->Add(this->textIDSex);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->picPriview);
			this->Controls->Add(this->textIDName);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormRegActive";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"注册激活";
			this->Load += gcnew System::EventHandler(this, &FormRegActive::FormRegActive_Load);
			this->Closed += gcnew System::EventHandler(this, &FormRegActive::FormRegActive_Closed);
			this->Shown += gcnew System::EventHandler(this, &FormRegActive::FormRegActive_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picPriview))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picCapture))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		
		private: System::Void FormRegActive_Shown(System::Object^  sender, System::EventArgs^  e) {
				
					 ::DialogResult result;					 
	
					 DWORD dwRegister = 0;
					 
					 strInfoMessage = "单击“确定”开始连接视频采集设备\r\n单击'取消'返回上一级菜单";
					 while(1){
						
						 if((result = MessageBox::Show(this, strInfoMessage, "查找设备", MessageBoxButtons::OKCancel, MessageBoxIcon::Information)) == ::DialogResult::Cancel){
							bReturnUpForm = true;
							break;
						}else{
							bReturnUpForm = false;
							
							hr = DS->CreatCaptureFilter();
							
							if(FAILED(hr)){
								strInfoMessage = "没有找到设备,请确认设备连接正常\r\n单击'重试'重新查找\r\n\n单击'取消'返回上一级菜单";	
							}else{
								
								btnCaptureIDInfo->Enabled = true;
								btnCaptureHeadPic->Enabled = true;
								btnRegActive->Enabled = true;
								
								hr = DS->BuiltFilterGraph();		//init grabber filter for capture one video frame
								if(FAILED(hr)){
									MessageBox::Show("BuiltFilterGraph failed.");
									continue;
								}

								AddToRot(DS->pGraphManager, &dwRegister);

								DS->SetVideoWindows((HWND)picPriview->Handle.ToPointer());

								hr = DS->pMC->Run();
								
								break;					
								
							}
							
						}
					 }
					 if(bReturnUpForm){
						DS->DestroyFilter();
						this->Owner->Activate();
						this->Owner->Show();
						this->Close();
					 }
					 
				 }

		private: System::Void FormRegActive_Closed(System::Object^  sender, System::EventArgs^  e) {
					 DS->DestroyFilter();
			this->Owner->Activate();
			this->Owner->Show();
		}

		private: System::Void FormRegActive_Load(System::Object^  sender, System::EventArgs^  e) {

//					 picCapture->Image = Image::FromFile(String("noboy.PNG").ToString(), false);
					 
					 hr = DS->CreatFilterGraph();
					 if (FAILED(hr)){
						MessageBox::Show("Couldn't GreatFilterGraph!");
						this->Close();
					 }

					 hr = DS->CreatGrabberFilter();
					 if (FAILED(hr)){
						MessageBox::Show("Couldn't CreatGrabberFilter!");
						this->Close();
					 }

					 hr = DS->CreatNullRender();
					 if (FAILED(hr)){
						 MessageBox::Show("Couldn't CreatNullRender!");
						 this->Close();
					 }
			
			}

		private: System::Void FormRegActive_InitializeComponent() {
					 if(bIDReaderConnect){
						;
					 }else{
						 MessageBox::Show("请把二代身份证放在读卡器上");
					 }

			 }
	private: System::Void btnRegActive_Click(System::Object^  sender, System::EventArgs^  e) {
				  DS->pGrabber->SetOneShot( TRUE );

			 }
private: System::Void btnCaptureIDInfo_Click(System::Object^  sender, System::EventArgs^  e) {
				  DS->pGrabber->SetOneShot( FALSE );
			 
		 }

		 

private: System::Void btnCaptureHeadPic_Click(System::Object^  sender, System::EventArgs^  e) {

			 long size = 0;

//			 BYTE* pImage = DS->SnapStillImage(&size);
			 BYTE* pImage = DS->SampleStillImage(size);
			 MemoryStream^ ms = gcnew MemoryStream(size);
			array<Byte>^ b = gcnew array<Byte>(size);
			Marshal::Copy( (IntPtr)pImage, b, 0, size );
			ms->Write(b, 0, size);

			picCapture->Image = Image::FromStream(ms);	
							
		}


		 HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister){
			 IMoniker * pMoniker = NULL;
			 IRunningObjectTable *pROT = NULL;

			 if (FAILED(GetRunningObjectTable(0, &pROT))) 
			 {
				 return E_FAIL;
			 }

			 const size_t STRING_LENGTH = 256;

			 WCHAR wsz[STRING_LENGTH];

			 StringCchPrintfW(
				 wsz, STRING_LENGTH, 
				 L"FilterGraph %08x pid %08x", 
				 (DWORD_PTR)pUnkGraph, 
				 GetCurrentProcessId()
				 );

			 HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
			 if (SUCCEEDED(hr)) 
			 {
				 hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph,
					 pMoniker, pdwRegister);
				 pMoniker->Release();
			 }
			 pROT->Release();

			 return hr;
		 }


		 void RemoveFromRot(DWORD pdwRegister){
			 IRunningObjectTable *pROT;
			 if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
				 pROT->Revoke(pdwRegister);
				 pROT->Release();
			 }
		 }



};
}

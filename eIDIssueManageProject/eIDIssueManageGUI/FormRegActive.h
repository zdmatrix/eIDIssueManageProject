#pragma once

//#include <uuids.h>
//#include <strsafe.h>


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace System::Drawing::Imaging;



#define WM_VIDEOWINDOSW WM_APP+1

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

	public ref class CaptureVideoComment{
	public:
		IBaseFilter *pBaseFilter;
					 IVideoWindow  *pVW;
					 IMediaControl *pMC;
//					 IMediaEventEx *pME = NULL;
					 IFilterGraph2 *pGraph;
					 ICaptureGraphBuilder2 *pCapture;
					 IMoniker *pMoniker;

		

					 
	};

	public ref class FormRegActive : public System::Windows::Forms::Form
	{
	public:

		bool bIDInfo;
		bool bIDHeadPic;
		bool bIDReaderConnect;
		bool bCameraConnect;
		
		bool bReturnUpForm;
		HRESULT hr;

		DWORD dwRegister;

		String^ strInfoMessage;
		String^ strCaptureDevName;
		
		CaptureVideoComment^ CVComment;
    

	private: System::Windows::Forms::Button^  btnCaptureIDInfo;
	private: System::Windows::Forms::Button^  btnCaptureHeadPic;

	
		
		

		

	public: 

		const char* CAPTUREDEVNAME;

		FormRegActive(void)
		{
			bIDInfo = false;
			bIDHeadPic = false;
			bIDReaderConnect = false;
			bCameraConnect = false;
			bReturnUpForm = false;

			strInfoMessage = "";
//			CAPTUREDEVNAME = "USB 视频设备";
			CAPTUREDEVNAME = "Microsoft LifeCam HD-3000";

			CVComment = gcnew CaptureVideoComment(); 
			
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
	private: System::Windows::Forms::PictureBox^  picHead;
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
			this->picHead = (gcnew System::Windows::Forms::PictureBox());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picHead))->BeginInit();
			this->SuspendLayout();
			// 
			// picHead
			// 
			this->picHead->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->picHead->BackColor = System::Drawing::SystemColors::Control;
			this->picHead->Location = System::Drawing::Point(380, 12);
			this->picHead->Name = L"picHead";
			this->picHead->Size = System::Drawing::Size(240, 340);
			this->picHead->TabIndex = 0;
			this->picHead->TabStop = false;
			this->picHead->Tag = L"";
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(12, 14);
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
			this->textIDName->Location = System::Drawing::Point(63, 12);
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
			this->label2->Location = System::Drawing::Point(12, 62);
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
			this->label3->Location = System::Drawing::Point(159, 62);
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
			this->textIDSex->Location = System::Drawing::Point(63, 60);
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
			this->textIDNation->Location = System::Drawing::Point(208, 60);
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
			this->textIDYear->Location = System::Drawing::Point(63, 114);
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
			this->textIDMonth->Location = System::Drawing::Point(181, 114);
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
			this->textIDDay->Location = System::Drawing::Point(265, 114);
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
			this->textIDLocation->Location = System::Drawing::Point(63, 166);
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
			this->textIDNum->Location = System::Drawing::Point(123, 250);
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
			this->label4->Location = System::Drawing::Point(12, 116);
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
			this->label5->Location = System::Drawing::Point(12, 168);
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
			this->label6->Location = System::Drawing::Point(149, 116);
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
			this->label7->Location = System::Drawing::Point(234, 116);
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
			this->label8->Location = System::Drawing::Point(318, 116);
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
			this->label9->Location = System::Drawing::Point(12, 252);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(105, 23);
			this->label9->TabIndex = 17;
			this->label9->Text = L"公民身份号码";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnRegActive
			// 
			this->btnRegActive->Location = System::Drawing::Point(294, 411);
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
			this->btnCaptureIDInfo->Location = System::Drawing::Point(15, 341);
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
			this->btnCaptureHeadPic->Location = System::Drawing::Point(444, 374);
			this->btnCaptureHeadPic->Name = L"btnCaptureHeadPic";
			this->btnCaptureHeadPic->Size = System::Drawing::Size(128, 23);
			this->btnCaptureHeadPic->TabIndex = 20;
			this->btnCaptureHeadPic->Text = L"开始采集头像图片";
			this->btnCaptureHeadPic->UseVisualStyleBackColor = true;
			this->btnCaptureHeadPic->Click += gcnew System::EventHandler(this, &FormRegActive::btnCaptureHeadPic_Click);
			// 
			// FormRegActive
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(632, 446);
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
			this->Controls->Add(this->textIDName);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->picHead);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormRegActive";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"注册激活";
			this->Load += gcnew System::EventHandler(this, &FormRegActive::FormRegActive_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picHead))->EndInit();
			
			this->Closed += gcnew System::EventHandler(this, &FormRegActive::FormRegActive_Closed); 
			this->Shown += gcnew System::EventHandler(this, &FormRegActive::FormRegActive_Shown);

			this->ResumeLayout(false);
			this->PerformLayout();
			

		}
#pragma endregion
		
		
		private: System::Void FormRegActive_Shown(System::Object^  sender, System::EventArgs^  e) {
					 
					 ::DialogResult result;
					 
					 IBaseFilter *pBaseFilter = NULL;
//					 IVideoWindow  **ppVW = NULL;
//					 IMediaControl **ppMC = NULL;
//					 IMediaEventEx *pME = NULL;
//					 IFilterGraph2 *pGraph = NULL;
//					 ICaptureGraphBuilder2 *pCapture = NULL;
//					 IMoniker *pMoniker =NULL;
  
					 

					 
  
					 strInfoMessage = "单击'确定'开始设备查找\r\n单击'取消'返回上一级菜单";
					 while(1){
						
						if((result = MessageBox::Show(this, strInfoMessage, "查找设备", MessageBoxButtons::OKCancel, MessageBoxIcon::Information)) == ::DialogResult::Cancel){
							bReturnUpForm = true;
							break;
						}else{
							bReturnUpForm = false;
							hr = FindCaptureDevice();
							if(FAILED(hr)){
								strInfoMessage = "没有找到设备,请确认设备连接正常\r\n单击'确定'重新查找\r\n单击'取消'返回上一级菜单";	
							}else{
								if(bCameraConnect){
									btnCaptureIDInfo->Enabled = true;
									btnCaptureHeadPic->Enabled = true;
									hr = InitGraphFilterInstance();
									if(FAILED(hr)){
										strInfoMessage = "InitGraphFilterInstance failed!";
									}else{
										
										hr = InitPriviewVideoFilter();
										if(FAILED(hr)){
											MessageBox::Show("InitPriviewVideoFilter failed!");
										}
										
										SetVideoWindows();

										hr = CVComment->pMC->Run();
										
									

										break;

									}
										
								}
							}
						}
					 }
					 if(bReturnUpForm){
						this->Owner->Activate();
						this->Owner->Show();
						this->Close();
					 }
				 }

		private: System::Void FormRegActive_Closed(System::Object^  sender, System::EventArgs^  e) {
			this->Owner->Activate();
			this->Owner->Show();
		}

		private: System::Void FormRegActive_Load(System::Object^  sender, System::EventArgs^  e) {
			CVComment->pBaseFilter = NULL;
			CVComment->pCapture = NULL;
			CVComment->pGraph = NULL;
			CVComment->pMC = NULL;
			CVComment->pMoniker = NULL;
			CVComment->pVW = NULL;
		
					 
			}

		private: System::Void FormRegActive_InitializeComponent() {
					 if(bIDReaderConnect){
						;
					 }else{
						 MessageBox::Show("请把二代身份证放在读卡器上");
					 }

			 }
	private: System::Void btnRegActive_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void btnCaptureIDInfo_Click(System::Object^  sender, System::EventArgs^  e) {

		 }

		 

private: System::Void btnCaptureHeadPic_Click(System::Object^  sender, System::EventArgs^  e) {

/*			
			
			HRESULT hr;

			IVideoWindow  *pVW = NULL;
			IMediaControl *pMC = NULL;
			IMediaEventEx *pME = NULL;
			IFilterGraph2 *pGraph = NULL;
			ICaptureGraphBuilder2 *pCapture = NULL;
			IBaseFilter *pCapDevBaseFilter = NULL;
			IMoniker *pMoniker =NULL;
		

   
			IBaseFilter *pBaseFilter = NULL;

			// Get the display name of the moniker
			LPOLESTR strMonikerName=0;
			hr = pMoniker->GetDisplayName(NULL, NULL, &strMonikerName);
			if (FAILED(hr)){
				MessageBox::Show("GetDisplayName failed!");
			}


			// Create a bind context needed for working with the moniker
			IBindCtx *pContext = NULL;
			hr = CreateBindCtx(0, &pContext);
			if (FAILED(hr)){
				 MessageBox::Show("CreateBindCtx failed!");
			}
  
			hr = pGraph->AddSourceFilterForMoniker(pMoniker, pContext, 
                                             strMonikerName, &pBaseFilter);
			if (FAILED(hr)){
				MessageBox::Show("AddSourceFilterForMoniker failed!");
			}

			// Attach the filter graph to the capture graph
			hr = pCapture->SetFiltergraph(pGraph);
			if (FAILED(hr)){
				MessageBox::Show("SetFiltergraph failed!");
			}


			IBaseFilter *pMux;
hr = pCapture->SetOutputFileName(
    &MEDIASUBTYPE_Avi,  // Specifies AVI for the target file.
    L"e:\\Example.avi", // File name.
    &pMux,              // Receives a pointer to the mux.
    NULL); 

			// Render the preview pin on the video capture filter
			// Use this instead of g_pGraph->RenderFile
			hr = pCapture->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
                                   pBaseFilter, NULL, NULL);

			hr = pCapture->RenderStream(
    &PIN_CATEGORY_CAPTURE, // Pin category.
    &MEDIATYPE_Video,      // Media type.
    pBaseFilter,                  // Capture filter.
    NULL,                  // Intermediate filter (optional).
    pMux);                 // Mux or file sink filter.

// Release the mux filter.

			hr = pVW->put_Owner((OAHWND)picHead->Handle.ToPointer());
			
			RECT rc;
        
			// Make the preview video fill our window
			GetClientRect((HWND)picHead->Handle.ToPointer(), &rc);
			pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
//			pVW->SetWindowPosition(0, 0, 40, 40);
//			pVW->put_Top(40);
//			pVW->put_Width(40);
//			pVW->put_Height(40);
//			pVW->put_Left(40);
			// Set video window style
			hr = pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
   

			// Use helper function to position video window in client rect 
			// of main application window
   

			// Make the video window visible, now that it is properly positioned
			hr = pVW->put_Visible(OATRUE);

			hr = pMC->Run();

			for(int i = 0; i < 60000; i ++){
				for(int j = 0; j < 1000; j ++){
					;
				}
			}

			hr = pMC->Stop();
			*/

		}

		void SetVideoWindows(){
			
			RECT rc;

			hr = CVComment->pVW->put_Owner((OAHWND)picHead->Handle.ToPointer());
			
			// Make the preview video fill our window
			GetClientRect((HWND)picHead->Handle.ToPointer(), &rc);
			CVComment->pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);

			// Set video window style
			hr = CVComment->pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);

			// Make the video window visible, now that it is properly positioned
			hr = CVComment->pVW->put_Visible(OATRUE);
		}


		HRESULT InitPriviewVideoFilter(){
			
			IBaseFilter *pBaseFilter = NULL;
			IBindCtx *pContext = NULL;
//			IMoniker **ppMoniker = NULL; 
//			IFilterGraph2 **ppGraph = NULL; 
//			ICaptureGraphBuilder2 **ppCapture = NULL;

			cli::pin_ptr<IMoniker *> ppMoniker= &CVComment->pMoniker;
			cli::pin_ptr<IFilterGraph2 *> ppGraph= &CVComment->pGraph;
			cli::pin_ptr<ICaptureGraphBuilder2 *> ppCapture= &CVComment->pCapture;

			// Get the display name of the moniker
			LPOLESTR strMonikerName = 0;
			hr = CVComment->pMoniker->GetDisplayName(NULL, NULL, &strMonikerName);
			if (FAILED(hr)){
				MessageBox::Show("GetDisplayName failed!");
				return hr;
			}

			// Create a bind context needed for working with the moniker
			
			hr = CreateBindCtx(0, &pContext);
			if (FAILED(hr)){
				 MessageBox::Show("CreateBindCtx failed!");
				 return hr;
			}
  
			hr = CVComment->pGraph->AddSourceFilterForMoniker(
				*ppMoniker, 
				pContext, 
                strMonikerName, 
				&pBaseFilter);
			if (FAILED(hr)){
				MessageBox::Show("AddSourceFilterForMoniker failed!");
				return hr;
			}

			// Attach the filter graph to the capture graph
			hr = CVComment->pCapture->SetFiltergraph(*ppGraph);
			if (FAILED(hr)){
				MessageBox::Show("SetFiltergraph failed!");
				return hr;
			}

			// Render the preview pin on the video capture filter
			// Use this instead of g_pGraph->RenderFile
			hr = CVComment->pCapture->RenderStream (
				&PIN_CATEGORY_PREVIEW, 
				&MEDIATYPE_Video,
                pBaseFilter, 
				NULL, 
				NULL);
			hr = S_OK;
			return hr;
		}




		HRESULT InitGraphFilterInstance(){
			
			HRESULT hr;
			cli::pin_ptr<IFilterGraph2 *> ppGraph = &CVComment->pGraph;
			cli::pin_ptr<ICaptureGraphBuilder2 *> ppCapture = &CVComment->pCapture;
			cli::pin_ptr<IVideoWindow *> ppVW = &CVComment->pVW;
			cli::pin_ptr<IMediaControl *> ppMC = &CVComment->pMC;
			
			if(!ppGraph || !ppCapture){
				return E_POINTER;
			}
			hr = CoCreateInstance (
				CLSID_FilterGraph, 
				NULL, 
				CLSCTX_INPROC,
                IID_IFilterGraph2, 
				(void **) ppGraph
				);
			if (FAILED(hr)){
				MessageBox::Show("Initial IFilterGraph2 failed!");
				return E_NOINTERFACE;
			}	
			
	

			// Create the capture graph builder
			 hr = CoCreateInstance (
				 CLSID_CaptureGraphBuilder2, 
				 NULL, 
				 CLSCTX_INPROC,
                 IID_ICaptureGraphBuilder2, 
				 (void **) ppCapture
				 );
			 if (FAILED(hr)){
				 MessageBox::Show("Initial ICaptureGraphBuilder2 failed!");
				 return E_NOINTERFACE;
			 }

			 hr = CVComment->pGraph->QueryInterface(IID_IMediaControl,(LPVOID *) ppMC);
			 if (FAILED(hr)){
				MessageBox::Show("Initial IMediaControl failed!");
				return E_NOINTERFACE;
			 }
			 
			 hr = CVComment->pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *) ppVW);
			 if (FAILED(hr)){
				MessageBox::Show("Initial IVideoWindow failed!");
				return E_NOINTERFACE;
			 }						
			 /*
			 hr = pGraph->QueryInterface(IID_IMediaEvent, (LPVOID *) &pME);
			 if (FAILED(hr)){
				MessageBox::Show("Initial IMediaEventEx failed!");
				return E_NOINTERFACE;
			 }
			 */
			 
			 return S_OK;
		}
		




		HRESULT FindCaptureDevice(){
					HRESULT hr;
					
					ULONG cFetched;
	
					// Create the system device enumerator
					ICreateDevEnum *pDevEnum =NULL;

					hr = CoCreateInstance (
						CLSID_SystemDeviceEnum, 
						NULL, 
						CLSCTX_INPROC,
                        IID_ICreateDevEnum, 
						(void **) &pDevEnum
						);
					if (FAILED(hr)){
						MessageBox::Show("Couldn't create system enumerator!");
						return E_NOINTERFACE;
					}

					// Create an enumerator for the video capture devices
					IEnumMoniker *pClassEnum = NULL;

					hr = pDevEnum->CreateClassEnumerator(
						CLSID_VideoInputDeviceCategory, 
						&pClassEnum, 
						0
						);
					if (FAILED(hr)){
						MessageBox::Show("Couldn't create class enumerator!");
						return E_NOINTERFACE;
					}

					// If there are no enumerators for the requested type, then 
					// CreateClassEnumerator will succeed, but pClassEnum will be NULL.
					if (pClassEnum == NULL){
						MessageBox::Show("No video capture device was detected.\r\n\r\n	  \
								This sample requires a video capture device, such as a USB WebCam,\r\n \
								to be installed and working properly.  The sample will now close. \
								No Video Capture Hardware");
						return E_FAIL;
					}

					cli::pin_ptr<IMoniker *> ppMoniker = &CVComment->pMoniker;

					// Use the first video capture device on the device list.
					// Note that if the Next() call succeeds but there are no monikers,
					// it will return S_FALSE (which is not a failure).  Therefore, we
					// check that the return code is S_OK instead of using SUCCEEDED() macro.
					if (S_OK == (pClassEnum->Next (1, ppMoniker, &cFetched))){
						// Bind Moniker to a filter object
						IPropertyBag *pPropBag = NULL;
						hr = CVComment->pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
								if (FAILED(hr)){
									CVComment->pMoniker->Release();
									return E_NOINTERFACE;  
								} 
								
								VARIANT var;
								VariantInit(&var);

								// Get description or friendly name.
								hr = pPropBag->Read(L"Description", &var, 0);
								if (FAILED(hr)){
									hr = pPropBag->Read(L"FriendlyName", &var, 0);
								}
								if (SUCCEEDED(hr)){
									strCaptureDevName = String(var.bstrVal).ToString();
									if(!strCaptureDevName->CompareTo(String(CAPTUREDEVNAME).ToString())){
										bCameraConnect = true;
										hr = S_OK;
									}else{
										hr = E_FAIL;
										return hr;
									}

								}

//								hr = pPropBag->Read(L"DevicePath", &var, 0);
//								if (SUCCEEDED(hr)){
//									// The device path is not intended for display.
//									VariantClear(&var); 
//								}

								pPropBag->Release();

					}else{
						MessageBox::Show("Unable to access video capture device!");   
						return E_FAIL;
					}

					// Copy the found filter pointer to the output parameter.
					// Do NOT Release() the reference, since it will still be used
					// by the calling function.

					return hr;
			}



			

		 
									
				
};
}

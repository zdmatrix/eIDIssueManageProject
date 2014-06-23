#pragma once

#include "DSComment.h"
#include "RegComment.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace eIDIssueManageGUI {

	/// <summary>
	/// FormMessageDialog ժҪ
	///
	/// ����: ������Ĵ�������ƣ�����Ҫ����
	///          ����������������� .resx �ļ��������й���Դ���������ߵ�
	///          ����Դ�ļ��������ԡ�����
	///          �������������˴���Ĺ���
	///          ���ػ���Դ��ȷ������
	/// </summary>
	public ref class FormMessageDialog : public System::Windows::Forms::Form
	{
	public:

		DSComment^ DS;

		RegComment^ RC;

		HRESULT hr;

		String^ strInfoMessage;
		String^ strResault;
		bool bVideoDevConnect;
		bool bReaderConnect;
		bool bReturn;
		bool bRegActive;

		const static int RESAULTOFFSET = 0x0A;
		const static int RESAULTLEN = 0x05;
		const static int RETRYNUM = 0x03;

		const static String^ FCSDOK = "Status: FCSD Created";
		const static String^ REGISTEROK = "Status: Status: Register Done";

		int nRetryNum;
	private: System::Windows::Forms::Button^  btnOK;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	public: 
		

		

		FormMessageDialog(void)
		{
			
			DS = gcnew DSComment;
			RC = gcnew RegComment;

			bRegActive = false;

			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~FormMessageDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnRun;
	protected: 

	protected: 
	private: System::Windows::Forms::Button^  btnCancle;
	private: System::Windows::Forms::TextBox^  textBox1;


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
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->btnCancle = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// btnRun
			// 
			this->btnRun->Location = System::Drawing::Point(76, 238);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(75, 23);
			this->btnRun->TabIndex = 0;
			this->btnRun->Text = L"Start";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &FormMessageDialog::btnRun_Click);
			// 
			// btnCancle
			// 
			this->btnCancle->Location = System::Drawing::Point(191, 238);
			this->btnCancle->Name = L"btnCancle";
			this->btnCancle->Size = System::Drawing::Size(75, 23);
			this->btnCancle->TabIndex = 1;
			this->btnCancle->Text = L"Cancle";
			this->btnCancle->UseVisualStyleBackColor = true;
			this->btnCancle->Click += gcnew System::EventHandler(this, &FormMessageDialog::btnCancle_Click);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->BackColor = System::Drawing::SystemColors::Control;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(0, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(445, 221);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"Press \"Start\" to Register and Active";
			// 
			// btnOK
			// 
			this->btnOK->Location = System::Drawing::Point(306, 238);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(75, 23);
			this->btnOK->TabIndex = 3;
			this->btnOK->Text = L"OK";
			this->btnOK->UseVisualStyleBackColor = true;
			this->btnOK->Click += gcnew System::EventHandler(this, &FormMessageDialog::btnOK_Click);
			// 
			// FormMessageDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(445, 275);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btnCancle);
			this->Controls->Add(this->btnRun);
			this->Name = L"FormMessageDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"ע�ἤ��";
			this->Load += gcnew System::EventHandler(this, &FormMessageDialog::FormMessageDialog_Load);
			this->Closed += gcnew System::EventHandler(this, &FormMessageDialog::FormMessageDialog_Closed);
			this->Shown += gcnew System::EventHandler(this, &FormMessageDialog::FormMessageDialog_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnRun_Click(System::Object^  sender, System::EventArgs^  e) {
				 bool bStatusOK = false;
				 bool bProcessOK = false;
				 
				 
				 if(nRetryNum++ == RETRYNUM){
					 textBox1->Text = "\r\n\r\nPSE ISSUE Failed!\r\nPress \"Cancle\" Return.";
					 btnRun->Text = "Start";
				 }else{
					 btnRun->Text = "Retry";
					 textBox1->Text = "Start the " + nRetryNum.ToString() + " times process : \r\n\r\n";

				 RC->ProcessRun("register");
				 textBox1->Text += strInfoMessage;
				 if(bStatusOK = strInfoMessage->Contains((String^)REGISTEROK)){
					 textBox1->Text += "\r\n\r\nRegister Sucess!";
					 btnRun->Text = "Start";
				 }

				 RC->ProcessRun("fcsd_verify");
				 ViewResault();
				 if(!(bStatusOK = this->textBox1->Text->Contains((String^)FCSDOK))){
					 RC->ProcessRun("fcsd_create");
					 ViewResault();
					 if(bStatusOK = this->textBox1->Text->Contains((String^)FCSDOK)){
						 textBox1->Text += "\r\n\r\nFCSD Created Sucess!";
					 }
				 }else{
					 textBox1->Text += "\r\n\r\nFCSD Created Sucess!";
				 }

				 
				 }

			 }

	private: System::Void FormMessageDialog_Load(System::Object^ sender, System::EventArgs^ e){
/*				 
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
*/
				 RC->ProcessInit();
			 }

	 private: System::Void FormMessageDialog_Shown(System::Object^ sender, System::EventArgs^ e){
/*				  
				  bVideoDevConnect = false;

				  strInfoMessage = "��ʼ������Ƶ�ɼ��豸\r\n����'ȡ��'������һ���˵�";
				  
				  textBox1->Text = strInfoMessage;

				  hr = DS->CreatCaptureFilter();

				  if(FAILED(hr)){
					  strInfoMessage = "û���ҵ��豸,��ȷ���豸��������\r\n����'����'���²���\r\n\n����'ȡ��'������һ���˵�";
					  textBox1->Text = strInfoMessage;
				  }else{

					  hr = DS->BuiltFilterGraph();		//init grabber filter for capture one video frame
					  if(FAILED(hr)){
						  
						  strInfoMessage = "BuiltFilterGraph failed\r\n����'����'���²���\r\n\n����'ȡ��'������һ���˵�";
						  textBox1->Text = strInfoMessage;
					  }

					  bVideoDevConnect = true;

				  }

				  if(bVideoDevConnect){
						FormMessageDialog_Closed(sender, e);
				  }
*/
				  

//				  MessageBox::Show("Write done!");
				  btnRun->Text = "Start";
				  
				  textBox1->Text = "Press the \"Start\" Button Starting Register and Active";
				  
				  nRetryNum = 0;
					  
				  
				  
				  

			}

	  private: System::Void FormMessageDialog_Closed(System::Object^ sender, System::EventArgs^ e){
				   this->Close();
				   
			   }

private: System::Void btnCancle_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void btnOK_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

		 private: System::Void ViewResault(){
					  String^ str = "";
					  while((str = RC->GetStreamReader()->ReadLine()) != nullptr){
						  this->textBox1->AppendText(str + Environment::NewLine);
						  this->textBox1->ScrollToCaret();
						  Application::DoEvents();
					  }
				  }


};

	

	
}

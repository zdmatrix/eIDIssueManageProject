#pragma once

#include "DSComment.h"

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

		HRESULT hr;

		String^ strInfoMessage;
		bool bVideoDevConnect;
		bool bReaderConnect;
		bool bReturn;

		FormMessageDialog(void)
		{
			DS = gcnew DSComment;
			
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
	private: System::Windows::Forms::Button^  btnRetry;
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
			this->btnRetry = (gcnew System::Windows::Forms::Button());
			this->btnCancle = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// btnRetry
			// 
			this->btnRetry->Location = System::Drawing::Point(50, 115);
			this->btnRetry->Name = L"btnRetry";
			this->btnRetry->Size = System::Drawing::Size(75, 23);
			this->btnRetry->TabIndex = 0;
			this->btnRetry->Text = L"����";
			this->btnRetry->UseVisualStyleBackColor = true;
			this->btnRetry->Click += gcnew System::EventHandler(this, &FormMessageDialog::btnRetry_Click);
			// 
			// btnCancle
			// 
			this->btnCancle->Location = System::Drawing::Point(177, 115);
			this->btnCancle->Name = L"btnCancle";
			this->btnCancle->Size = System::Drawing::Size(75, 23);
			this->btnCancle->TabIndex = 1;
			this->btnCancle->Text = L"ȡ��";
			this->btnCancle->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->BackColor = System::Drawing::SystemColors::Control;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(0, 32);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(283, 58);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// FormMessageDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(283, 148);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btnCancle);
			this->Controls->Add(this->btnRetry);
			this->Name = L"FormMessageDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"�豸����";

			this->Load += gcnew System::EventHandler(this, &FormMessageDialog::FormMessageDialog_Load);
			this->Shown += gcnew System::EventHandler(this, &FormMessageDialog::FormMessageDialog_Shown);
			this->Closed += gcnew System::EventHandler(this, &FormMessageDialog::FormMessageDialog_Closed);

			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnRetry_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	private: System::Void FormMessageDialog_Load(System::Object^ sender, System::EventArgs^ e){
				 
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

	 private: System::Void FormMessageDialog_Shown(System::Object^ sender, System::EventArgs^ e){
				  
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

//					  AddToRot(DS->pGraphManager, &dwRegister);

//					  DS->SetVideoWindows((HWND)picPriview->Handle.ToPointer());

//					  hr = DS->pMC->Run();
					  bVideoDevConnect = true;

				  }

				  if(bVideoDevConnect){
						FormMessageDialog_Closed(sender, e);
				  }
			  }

	  private: System::Void FormMessageDialog_Closed(System::Object^ sender, System::EventArgs^ e){
				   this->Close();
				   
			   }

};

	

	
}

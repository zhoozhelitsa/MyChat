#pragma once
#include"CClient.h"
namespace UIClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelStatus;
	private: System::Windows::Forms::TextBox^ txtBoxChat;
	private: System::Windows::Forms::TextBox^ txtBoxMessage;
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: CClient^ cclient;
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labelStatus = (gcnew System::Windows::Forms::Label());
			this->txtBoxChat = (gcnew System::Windows::Forms::TextBox());
			this->txtBoxMessage = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->cclient = (gcnew CClient());
			this->SuspendLayout();
			// 
			// labelStatus
			// 
			this->labelStatus->AutoSize = true;
			this->labelStatus->ForeColor = System::Drawing::Color::IndianRed;
			this->labelStatus->Location = System::Drawing::Point(22, 407);
			this->labelStatus->Name = L"labelStatus";
			this->labelStatus->Size = System::Drawing::Size(90, 16);
			this->labelStatus->TabIndex = 0;
			this->labelStatus->Text = L"Disconnected";
			// 
			// txtBoxChat
			// 
			this->txtBoxChat->BackColor = System::Drawing::Color::AliceBlue;
			this->txtBoxChat->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtBoxChat->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtBoxChat->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->txtBoxChat->Location = System::Drawing::Point(16, 12);
			this->txtBoxChat->Multiline = true;
			this->txtBoxChat->Name = L"txtBoxChat";
			this->txtBoxChat->ReadOnly = true;
			this->txtBoxChat->Size = System::Drawing::Size(522, 298);
			this->txtBoxChat->TabIndex = 1;
			// 
			// txtBoxMessage
			// 
			this->txtBoxMessage->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtBoxMessage->Location = System::Drawing::Point(16, 331);
			this->txtBoxMessage->Multiline = true;
			this->txtBoxMessage->Name = L"txtBoxMessage";
			this->txtBoxMessage->Size = System::Drawing::Size(522, 63);
			this->txtBoxMessage->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LightGray;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Location = System::Drawing::Point(463, 400);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Send";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->ClientSize = System::Drawing::Size(550, 435);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->txtBoxMessage);
			this->Controls->Add(this->txtBoxChat);
			this->Controls->Add(this->labelStatus);
			this->Name = L"MyForm";
			this->Text = L"MyChat";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
		}
#pragma endregion

private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	if (cclient->connectClient()) {
		labelStatus->Text = "Connected";
		labelStatus->ForeColor = System::Drawing::Color::Green;
		this->backgroundWorker1->RunWorkerAsync();
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	cclient->sendMessage(txtBoxMessage->Text);
	txtBoxChat->Text += "You: " + txtBoxMessage->Text + "\r\n";
	txtBoxMessage->Text = "";
}
private: System::Void MyForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	cclient->disconnectClient();
	Close();
}
private: System::Void MessageReciver() {
	while (!cclient->getMessageArrayPtr()->empty()) {
		txtBoxChat->Text += gcnew System::String(cclient->getMessageArrayPtr()->at(0).c_str());
		cclient->getMessageArrayPtr()->erase(cclient->getMessageArrayPtr()->begin(), cclient->getMessageArrayPtr()->begin() + 1);
		}
	   }
private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	CClient::messageHandler();
}
};
}

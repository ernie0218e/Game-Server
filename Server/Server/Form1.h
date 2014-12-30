#pragma once
#include <Windows.h>
#include "TCPServer.h"
namespace Server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			String ^iparr;
			int i = 0, spt;
			InitializeComponent();
			test = gcnew TCPServer();
			iparr = test->getIParray();
			
			while(i < iparr->Length){
				spt = i;
				i = iparr->IndexOf("\n", i);
				comboBox1->Items->Add(iparr->Substring(spt, i - spt));
				i++;
			}
			comboBox1->SelectedIndex = 0;
			//
			//TODO: 在此加入建?函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{

				delete components;
			}
			test->~TCPServer();
		}
	private: System::Windows::Forms::Label^  IPlabel;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// 設?工具所需的?數。
		/// </summary>

	private: System::Windows::Forms::Button^  Start_server;
	private: System::Windows::Forms::Label^  connection_count;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: TCPServer ^test;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設?工具支援所需的方法 - ?勿使用程式碼??器
		/// 修改這?方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->IPlabel = (gcnew System::Windows::Forms::Label());
			this->Start_server = (gcnew System::Windows::Forms::Button());
			this->connection_count = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// IPlabel
			// 
			this->IPlabel->AutoSize = true;
			this->IPlabel->Location = System::Drawing::Point(12, 138);
			this->IPlabel->Name = L"IPlabel";
			this->IPlabel->Size = System::Drawing::Size(14, 15);
			this->IPlabel->TabIndex = 0;
			this->IPlabel->Text = L"0";
			// 
			// Start_server
			// 
			this->Start_server->Font = (gcnew System::Drawing::Font(L"稬硁タ堵砰", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->Start_server->Location = System::Drawing::Point(12, 68);
			this->Start_server->Name = L"Start_server";
			this->Start_server->Size = System::Drawing::Size(103, 32);
			this->Start_server->TabIndex = 1;
			this->Start_server->Text = L"Sever Start";
			this->Start_server->UseVisualStyleBackColor = true;
			this->Start_server->Click += gcnew System::EventHandler(this, &Form1::Start_server_Click);
			// 
			// connection_count
			// 
			this->connection_count->AutoSize = true;
			this->connection_count->Font = (gcnew System::Drawing::Font(L"稬硁タ堵砰", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->connection_count->Location = System::Drawing::Point(157, 162);
			this->connection_count->Name = L"connection_count";
			this->connection_count->Size = System::Drawing::Size(20, 22);
			this->connection_count->TabIndex = 2;
			this->connection_count->Text = L"0";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"稬硁タ堵砰", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(8, 162);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 22);
			this->label1->TabIndex = 3;
			this->label1->Text = L"member count:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"稬硁タ堵砰", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(8, 116);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 22);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Current IP:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 24);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(213, 23);
			this->comboBox1->TabIndex = 5;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(564, 428);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->connection_count);
			this->Controls->Add(this->Start_server);
			this->Controls->Add(this->IPlabel);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Start_server_Click(System::Object^  sender, System::EventArgs^  e) {
				 test->setIP(comboBox1->Text);
				 test->Start();
				 IPlabel->Text = test->serverIP();
				 timer1->Start();
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 connection_count->Text = test->serverCount();
			 }
	};
}


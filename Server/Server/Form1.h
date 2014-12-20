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
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
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
		/// 設計工具所需的變數。
		/// </summary>

	private: System::Windows::Forms::Button^  Start_server;
	private: System::Windows::Forms::Label^  connection_count;
	private: System::Windows::Forms::Timer^  timer1;
			 TCPServer ^test;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->IPlabel = (gcnew System::Windows::Forms::Label());
			this->Start_server = (gcnew System::Windows::Forms::Button());
			this->connection_count = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// IPlabel
			// 
			this->IPlabel->AutoSize = true;
			this->IPlabel->Location = System::Drawing::Point(13, 13);
			this->IPlabel->Name = L"IPlabel";
			this->IPlabel->Size = System::Drawing::Size(41, 15);
			this->IPlabel->TabIndex = 0;
			this->IPlabel->Text = L"label1";
			// 
			// Start_server
			// 
			this->Start_server->Location = System::Drawing::Point(13, 41);
			this->Start_server->Name = L"Start_server";
			this->Start_server->Size = System::Drawing::Size(75, 23);
			this->Start_server->TabIndex = 1;
			this->Start_server->Text = L"Start";
			this->Start_server->UseVisualStyleBackColor = true;
			this->Start_server->Click += gcnew System::EventHandler(this, &Form1::Start_server_Click);
			// 
			// connection_count
			// 
			this->connection_count->AutoSize = true;
			this->connection_count->Location = System::Drawing::Point(10, 89);
			this->connection_count->Name = L"connection_count";
			this->connection_count->Size = System::Drawing::Size(41, 15);
			this->connection_count->TabIndex = 2;
			this->connection_count->Text = L"label1";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(564, 428);
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
				 test = gcnew TCPServer();
				 IPlabel->Text = test->serverIP();
				 timer1->Start();
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 connection_count->Text = test->serverCount();
			 }
	};
}


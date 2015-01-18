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
	using namespace System::Text;
	/// <summary>
	/// Form1 腔晡猁
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
			//TODO: 婓森樓膘?滲宒最宒徨
			//
			pre_ai_num = 0;
		}

	protected:
		/// <summary>
		/// 壺睡妏蚚笢腔揃埭﹝
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
		/// 偞?馱撿垀剒腔?﹝
		/// </summary>
		int pre_ai_num;
	private: System::Windows::Forms::Button^  Start_server;
	private: System::Windows::Forms::Label^  connection_count;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::RichTextBox^  Log;
	private: System::Windows::Forms::Button^  Stop_server;



	private: TCPServer ^test;
	private: System::String^ err_msg;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::NumericUpDown^  player_num;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label4;
	private: System::String^ msg;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 森偞?馱撿盓堔垀剒腔源楊 - ?昦妏蚚最宒徨??
		/// 党蜊稛?源楊腔﹝
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
			this->Log = (gcnew System::Windows::Forms::RichTextBox());
			this->Stop_server = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->player_num = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->player_num))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// IPlabel
			// 
			this->IPlabel->AutoSize = true;
			this->IPlabel->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->IPlabel->Location = System::Drawing::Point(12, 169);
			this->IPlabel->Name = L"IPlabel";
			this->IPlabel->Size = System::Drawing::Size(14, 15);
			this->IPlabel->TabIndex = 0;
			this->IPlabel->Text = L"0";
			// 
			// Start_server
			// 
			this->Start_server->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Start_server->Location = System::Drawing::Point(12, 99);
			this->Start_server->Name = L"Start_server";
			this->Start_server->Size = System::Drawing::Size(99, 29);
			this->Start_server->TabIndex = 1;
			this->Start_server->Text = L"Start";
			this->Start_server->UseVisualStyleBackColor = true;
			this->Start_server->Click += gcnew System::EventHandler(this, &Form1::Start_server_Click);
			// 
			// connection_count
			// 
			this->connection_count->AutoSize = true;
			this->connection_count->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->connection_count->Location = System::Drawing::Point(157, 193);
			this->connection_count->Name = L"connection_count";
			this->connection_count->Size = System::Drawing::Size(20, 22);
			this->connection_count->TabIndex = 2;
			this->connection_count->Text = L"0";
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(8, 193);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 22);
			this->label1->TabIndex = 3;
			this->label1->Text = L"member count:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(8, 147);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 22);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Current IP:";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 24);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(213, 23);
			this->comboBox1->TabIndex = 5;
			// 
			// Log
			// 
			this->Log->Location = System::Drawing::Point(251, 24);
			this->Log->Name = L"Log";
			this->Log->ReadOnly = true;
			this->Log->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedBoth;
			this->Log->Size = System::Drawing::Size(301, 392);
			this->Log->TabIndex = 6;
			this->Log->Text = L"";
			// 
			// Stop_server
			// 
			this->Stop_server->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Stop_server->Location = System::Drawing::Point(127, 99);
			this->Stop_server->Name = L"Stop_server";
			this->Stop_server->Size = System::Drawing::Size(98, 29);
			this->Stop_server->TabIndex = 7;
			this->Stop_server->Text = L"Stop";
			this->Stop_server->UseVisualStyleBackColor = true;
			this->Stop_server->Click += gcnew System::EventHandler(this, &Form1::Stop_server_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(13, 53);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(98, 30);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Refresh IP";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// player_num
			// 
			this->player_num->Location = System::Drawing::Point(12, 265);
			this->player_num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->player_num->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->player_num->Name = L"player_num";
			this->player_num->Size = System::Drawing::Size(120, 25);
			this->player_num->TabIndex = 9;
			this->player_num->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(8, 243);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(117, 19);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Player Number:";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(12, 344);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 25);
			this->numericUpDown1->TabIndex = 11;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(9, 322);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(88, 19);
			this->label4->TabIndex = 12;
			this->label4->Text = L"AI Number:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(564, 428);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->player_num);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Stop_server);
			this->Controls->Add(this->Log);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->connection_count);
			this->Controls->Add(this->Start_server);
			this->Controls->Add(this->IPlabel);
			this->Name = L"Form1";
			this->Text = L"Server";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->player_num))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Start_server_Click(System::Object^  sender, System::EventArgs^  e) {
				 test->setIP(comboBox1->Text);
				 test->Start(Convert::ToInt32(player_num->Text) + Convert::ToInt32(numericUpDown1->Text));
				 test->setAINum(Convert::ToInt32(numericUpDown1->Text));
				 IPlabel->Text = test->serverIP();
				 Log->Text += "Server Start!!\n";
				 Log->Text += "The required player number is:" + player_num->Text + "\n";
				 timer1->Start();
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 connection_count->Text = test->serverCount();
				 err_msg = test->getError();
				 msg = test->getMessage();
				 if(err_msg != nullptr){
					Log->Text += err_msg;
				 }
				 if(msg != nullptr){
					 Log->Text += msg;
				 }
			 }
	private: System::Void Stop_server_Click(System::Object^  sender, System::EventArgs^  e) {
				 test->Stop();
				 IPlabel->Text = "0";
				 Log->Text += "Server Stop!!\n";
				 timer1->Stop();
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 comboBox1->Items->Clear();
			 String ^iparr;
			 int i = 0, spt;
			 iparr = test->getIParray();

			 while(i < iparr->Length){
				 spt = i;
				 i = iparr->IndexOf("\n", i);
				 comboBox1->Items->Add(iparr->Substring(spt, i - spt));
				 i++;
			 }
			 comboBox1->SelectedIndex = 0;
		 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

			 if(Convert::ToInt32(numericUpDown1->Value) > pre_ai_num){
				 if(player_num->Value > player_num->Minimum){
					player_num->Value = player_num->Value - 1;
				 }
				 player_num->Maximum = player_num->Maximum - 1;
				 player_num->Minimum = 1;
			 }else if(Convert::ToInt32(numericUpDown1->Value) < pre_ai_num){
				 player_num->Maximum = player_num->Maximum + 1;
				 player_num->Value = player_num->Value + 1;
			 }
			 if(Convert::ToInt32(numericUpDown1->Value) == 0)
				 player_num->Minimum = 2;
			 pre_ai_num = Convert::ToInt32(numericUpDown1->Value);
		 }
};
}


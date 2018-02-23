#pragma once
#include "File.h"
#include <string>
#include "Allocator.h"
#include "Interpreter.h"

namespace BrainfuckInterpreter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum textmode { Output, Memory, Input };

	//globals
	textmode mode = Output;


	void FillTextBox(System::Windows::Forms::TextBox^  textBox, std::ifstream *Loaded)
	{
		std::string line;
		String ^systemstring;
		if (Loaded->is_open())
		{
			textBox->Clear();
			while (std::getline(*Loaded, line))
			{
				systemstring = gcnew String(line.c_str());
				textBox->AppendText(systemstring);			///https://msdn.microsoft.com/en-us/library/ms235631.aspx

			}
			Loaded->close();
		}
	}
	std::string SysToChar(System::String ^sys) {
		
		char* str2 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sys);
		std::string str3(str2);
		return str3;
		

	}

	void FillFile(System::Windows::Forms::TextBox^ textBox, std::ofstream *Saved) {
		std::string filecontent = SysToChar(textBox->Text);
		*Saved << filecontent;
		Saved->close();
	}

	void ManageMode(System::Windows::Forms::TextBox^ textBox) {
		switch (mode)
		{
		case Output:
			textBox->ReadOnly = true;
			break;

		case Memory:
			textBox->ReadOnly = true;
			break;

		case Input:
			textBox->ReadOnly = false;
			break;
		}
	}

	/// <summary>
	/// Summary for IDE Window
	/// </summary>
	public ref class IDEWindow : public System::Windows::Forms::Form
	{
	public:
		IDEWindow(void)
		{

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			

		}
;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~IDEWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(IDEWindow::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->AllowDrop = true;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->textBox1->Location = System::Drawing::Point(13, 97);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->textBox1->Size = System::Drawing::Size(1426, 625);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->textBox2->Location = System::Drawing::Point(12, 813);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(1141, 86);
			this->textBox2->TabIndex = 1;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &IDEWindow::textBox2_TextChanged);
			// 
			// button1
			// 
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(13, 728);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(79, 79);
			this->button1->TabIndex = 2;
			this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &IDEWindow::button1_Click);
			// 
			// button2
			// 
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(98, 728);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(79, 79);
			this->button2->TabIndex = 3;
			this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &IDEWindow::button2_Click);
			// 
			// button3
			// 
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.Image")));
			this->button3->Location = System::Drawing::Point(183, 728);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(79, 79);
			this->button3->TabIndex = 4;
			this->button3->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &IDEWindow::button3_Click);
			// 
			// button4
			// 
			this->button4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button4.Image")));
			this->button4->Location = System::Drawing::Point(268, 728);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(79, 79);
			this->button4->TabIndex = 5;
			this->button4->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button5.Image")));
			this->button5->Location = System::Drawing::Point(353, 728);
			this->button5->Name = L"button5";
			this->button5->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button5->Size = System::Drawing::Size(79, 79);
			this->button5->TabIndex = 6;
			this->button5->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.Image")));
			this->button6->Location = System::Drawing::Point(1359, 728);
			this->button6->Name = L"button6";
			this->button6->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button6->Size = System::Drawing::Size(79, 79);
			this->button6->TabIndex = 7;
			this->button6->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &IDEWindow::button6_Click);
			// 
			// button7
			// 
			this->button7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button7.Image")));
			this->button7->Location = System::Drawing::Point(13, 12);
			this->button7->Name = L"button7";
			this->button7->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button7->Size = System::Drawing::Size(79, 79);
			this->button7->TabIndex = 8;
			this->button7->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &IDEWindow::button7_Click);
			// 
			// button8
			// 
			this->button8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button8.Image")));
			this->button8->Location = System::Drawing::Point(511, 728);
			this->button8->Name = L"button8";
			this->button8->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button8->Size = System::Drawing::Size(79, 79);
			this->button8->TabIndex = 9;
			this->button8->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &IDEWindow::button8_Click);
			// 
			// button9
			// 
			this->button9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button9.Image")));
			this->button9->Location = System::Drawing::Point(596, 728);
			this->button9->Name = L"button9";
			this->button9->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button9->Size = System::Drawing::Size(79, 79);
			this->button9->TabIndex = 10;
			this->button9->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &IDEWindow::button9_Click);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->textBox3->Location = System::Drawing::Point(1172, 813);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(266, 186);
			this->textBox3->TabIndex = 12;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->textBox4->Location = System::Drawing::Point(12, 905);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(1141, 94);
			this->textBox4->TabIndex = 13;
			// 
			// IDEWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1450, 1011);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"IDEWindow";
			this->Text = L"Interpreter";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	}



	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		std::ifstream *Loaded = LoadFile();
		if (Loaded != nullptr)
			FillTextBox(textBox1, Loaded);
	}

	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {

		std::ofstream *Saved = SaveFile();
		if (Saved != nullptr)
			FillFile(textBox1, Saved);
		
	}





private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {

	mode = Output;
	ManageMode(textBox2);
}
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
	mode = Memory;
	ManageMode(textBox2);
}
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
	mode = Input;
	ManageMode(textBox2);
	
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	
	Allocator *memAllocator = new Allocator;

	Interpreter *bfInterpreter = new Interpreter(memAllocator);
	bfInterpreter->fillInputBuffer(&SysToChar(textBox3->Text));
	bfInterpreter->runtime(&SysToChar(textBox1->Text));

	int max = memAllocator->returnMax()+1;
	
	
	std::string memory;
	textBox2->Clear();
	int memorychar;
	
	for (int i = 0; i < max; i++)
	{
		memorychar = memAllocator->getMemory(i);
		System::String ^sysMem = System::Convert::ToString(memorychar);
		textBox2->AppendText(sysMem);
		textBox2->AppendText(L" ");
	}
	System::String ^sysOut =gcnew String((bfInterpreter->getOutput()->c_str()));
	textBox4->Clear();
	textBox4->AppendText(sysOut);



}
		 Allocator * debugAlloc;
		 Interpreter* debugInter;
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	static Allocator memAllocator;
	debugAlloc = &memAllocator;

	static Interpreter bfInterpreter(&memAllocator);
	debugInter = &bfInterpreter;
	bfInterpreter.fillInputBuffer(&SysToChar(textBox3->Text));

	bfInterpreter.runMainStep(&SysToChar(textBox1->Text));

	int max = memAllocator.returnMax() + 1;


	std::string memory;
	textBox2->Clear();
	int memorychar;

	for (int i = 0; i < max; i++)
	{
		memorychar = memAllocator.getMemory(i);
		System::String ^sysMem = System::Convert::ToString(memorychar);
		textBox2->AppendText(sysMem);
		textBox2->AppendText(L" ");
	}
	System::String ^sysOut = gcnew String((bfInterpreter.getOutput()->c_str()));
	textBox4->Clear();
	textBox4->AppendText(sysOut);


}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	debugAlloc->terminate();
	debugInter->terminate();
	textBox3->Clear();
	textBox2->Clear();
}
};
}

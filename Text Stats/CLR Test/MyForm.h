#pragma once
#include <iostream>
#include <Windows.h>
#include <Shobjidl.h>
#include <fstream>

struct characterstr {
	wchar_t ch;
	unsigned long int times;
};

void Bubble_Sort(struct characterstr arr[], int size)
{

	bool sorted = false;
	while (sorted == false)
	{
		sorted = true;
		for (int i = 0; i < size - 1; ++i)
		{

			if (arr[i].times < arr[i + 1].times)
			{
				sorted = false;
				std::swap(arr[i], arr[i + 1]);
			}
		}
	}

}

namespace CLRTest {



	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			Series^ seri = this->chart1->Series[0];
			seri->Name = L"Concurrences";
			seri->Points->Clear();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected:

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 455);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(145, 67);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Load a File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 33);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(145, 416);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(13, 5);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(357, 22);
			this->textBox2->TabIndex = 2;
			// 
			// chart1
			// 
			chartArea1->AxisX->Interval = 1;
			chartArea1->AxisX->LabelAutoFitMaxFontSize = 6;
			chartArea1->AxisX->MajorGrid->Interval = 1;
			chartArea1->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->AxisY->LabelAutoFitMaxFontSize = 6;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->chart1->ImeMode = System::Windows::Forms::ImeMode::AlphaFull;
			legend1->Alignment = System::Drawing::StringAlignment::Center;
			legend1->DockedToChartArea = L"ChartArea1";
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(163, 33);
			this->chart1->Name = L"chart1";
			series1->BorderWidth = 5;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Area;
			series1->IsXValueIndexed = true;
			series1->Legend = L"Legend1";
			series1->MarkerBorderWidth = 5;
			series1->Name = L"Series1";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::String;
			series1->YValuesPerPoint = 25;
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Int32;
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(846, 736);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"Concurrences";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1030, 809);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Text Analysis";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			unsigned long int sentences = 0, words = 0;
			float wps;
			struct characterstr stats[50];
			for (int i = 0; i<50; i++)
			{
				stats[i].ch = 65 + i;
				stats[i].times = 0;
			}
			char letter;
			std::ifstream file;
			HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
				COINIT_DISABLE_OLE1DDE);
			PWSTR pszFilePath = NULL;
			LPOPENFILENAME filename = NULL;
			IFileOpenDialog *pFile;
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFile));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFile->Show(NULL);
			}
			
			if (SUCCEEDED(hr))
			{
			IShellItem *pItem;
			hr = pFile->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{

			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

			pItem->Release();
			}
			}
			file.open(pszFilePath);
			
			String ^title = gcnew String(pszFilePath);

			while (file.peek() != EOF)
			{
				file.read(&letter, 1);
				if (letter > 64 && letter < 91)
				{
					stats[letter - 65].times++;
				}
				if (letter > 96 && letter < 123)
				{
					stats[letter - 97].times++;
				}
				if (letter == ' ' || letter == '\n') words++;
				if (letter == '.') sentences++;

			}

			Bubble_Sort(stats, 26);
			wps = (float)words / (float)sentences;
			textBox2->ResetText();
			textBox2->AppendText(title);
			textBox1->ResetText();


			for (int i = 0; i < 26; i++)
			{
				
				textBox1->Text += stats[i].times;
				textBox1->Text += "\r\t";
				textBox1->Text += " times ";
				textBox1->Text += stats[i].ch;
				textBox1->Text += "\r\n";
				
				Char ^tempch = gcnew Char(stats[i].ch);
				String ^tempstr;
				tempstr += tempch;
				Series^ seri = this->chart1->Series[0];
				seri->Points->AddXY(tempstr, stats[i].times);
			}
		//	cout << "Total of " << words << " words, and " << sentences << " sentences.\n";
		//	cout << "Average of " << wps << " words per sentence\n";
			//chart1->AlignDataPointsByAxisLabel();
			pFile->Release();
			CoUninitialize();
			
		}
	



};
}

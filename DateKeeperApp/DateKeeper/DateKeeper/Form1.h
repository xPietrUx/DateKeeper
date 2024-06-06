#pragma once
#include <ctime>
#include <iostream>
#include <string>



namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Stuktura dla informacji o obcenej dacie
	struct CurrentDate {
		int day;
		int month;
		int year;
	};

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			if (currentDate == nullptr) {
				currentDate = getCurrentDate();
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: 
		// Tablica obecnej daty
		CurrentDate* currentDate;
		// Zmienne pomocnicze
		int currentYear;
		int currentMonth;
		int currentDay;
		// Pobranie obecnej daty
		CurrentDate* getCurrentDate();
		// Funkcja tworzenia dni miesi¹ca
		void CreateDays();
	private: System::Windows::Forms::FlowLayoutPanel^ DaysContainer;
	private: System::Windows::Forms::Button^ PreviousBtn;
	private: System::Windows::Forms::Button^ NextBtn;
	private: System::Windows::Forms::Label^ MonthHandler;
	private: System::Windows::Forms::Label^ YearHandler;
	private: System::Windows::Forms::Label^ DayHandler;



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
			this->DaysContainer = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->PreviousBtn = (gcnew System::Windows::Forms::Button());
			this->NextBtn = (gcnew System::Windows::Forms::Button());
			this->MonthHandler = (gcnew System::Windows::Forms::Label());
			this->YearHandler = (gcnew System::Windows::Forms::Label());
			this->DayHandler = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// DaysContainer
			// 
			this->DaysContainer->Location = System::Drawing::Point(12, 214);
			this->DaysContainer->Name = L"DaysContainer";
			this->DaysContainer->Size = System::Drawing::Size(745, 659);
			this->DaysContainer->TabIndex = 0;
			// 
			// PreviousBtn
			// 
			this->PreviousBtn->Location = System::Drawing::Point(12, 12);
			this->PreviousBtn->Name = L"PreviousBtn";
			this->PreviousBtn->Size = System::Drawing::Size(75, 23);
			this->PreviousBtn->TabIndex = 1;
			this->PreviousBtn->Text = L"Previous";
			this->PreviousBtn->UseVisualStyleBackColor = true;
			this->PreviousBtn->Click += gcnew System::EventHandler(this, &Form1::PreviousBtn_Click);
			// 
			// NextBtn
			// 
			this->NextBtn->Location = System::Drawing::Point(682, 12);
			this->NextBtn->Name = L"NextBtn";
			this->NextBtn->Size = System::Drawing::Size(75, 23);
			this->NextBtn->TabIndex = 2;
			this->NextBtn->Text = L"Next";
			this->NextBtn->UseVisualStyleBackColor = true;
			this->NextBtn->Click += gcnew System::EventHandler(this, &Form1::NextBtn_Click);
			// 
			// MonthHandler
			// 
			this->MonthHandler->AutoSize = true;
			this->MonthHandler->Location = System::Drawing::Point(342, 100);
			this->MonthHandler->Name = L"MonthHandler";
			this->MonthHandler->Size = System::Drawing::Size(74, 13);
			this->MonthHandler->TabIndex = 3;
			this->MonthHandler->Text = L"MonthHandler";
			// 
			// YearHandler
			// 
			this->YearHandler->AutoSize = true;
			this->YearHandler->Location = System::Drawing::Point(342, 113);
			this->YearHandler->Name = L"YearHandler";
			this->YearHandler->Size = System::Drawing::Size(66, 13);
			this->YearHandler->TabIndex = 4;
			this->YearHandler->Text = L"YearHandler";
			// 
			// DayHandler
			// 
			this->DayHandler->AutoSize = true;
			this->DayHandler->Location = System::Drawing::Point(342, 87);
			this->DayHandler->Name = L"DayHandler";
			this->DayHandler->Size = System::Drawing::Size(63, 13);
			this->DayHandler->TabIndex = 6;
			this->DayHandler->Text = L"DayHandler";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1109, 885);
			this->Controls->Add(this->DayHandler);
			this->Controls->Add(this->YearHandler);
			this->Controls->Add(this->MonthHandler);
			this->Controls->Add(this->NextBtn);
			this->Controls->Add(this->PreviousBtn);
			this->Controls->Add(this->DaysContainer);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Za³adowanie Fromsa
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		CreateDays();
		Label^ DayHandler = this->DayHandler;
		DayHandler->Text = (currentDate->day-1).ToString();
	}

	// Przejœcie do poprzedniego miesi¹ca
	void handlePrevMonth() {
		currentDate->month--;
		currentDate->day = 0;
		if (currentDate->month < 1) {
			currentDate->month = 12;
			currentDate->year--;
		}
	}

	private: System::Void PreviousBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		handlePrevMonth();
		CreateDays();
	}

	// Przejœcie do nastêpnego miesi¹ca
	void handleNextMonth() {
		currentDate->month++;
		currentDate->day = 0;
		if (currentDate->month > 12) {
			currentDate->month = 1;
			currentDate->year++;
		}
	}

	private: System::Void NextBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		handleNextMonth();
		CreateDays();
	}

	// Klikniecie na dzieñ
	void PanelClick(Object^ sender, EventArgs^ e) {

		// Przywrócenie oryginalnego koloru wszystkich paneli
		for each (Control ^ control in this->DaysContainer->Controls) {
			Panel^ panel = dynamic_cast<Panel^>(control);
			if (panel != nullptr) {
				panel->BackColor = System::Drawing::Color::White;
			}
		}

		Panel^ clickedPanel = dynamic_cast<Panel^>(sender);
		clickedPanel->BackColor = System::Drawing::Color::Gray;
		if (clickedPanel != nullptr) {
			// Pobranie zawartoœci panelu
			String^ labelText = nullptr;
			for each (Control ^ control in clickedPanel->Controls) {
				Label^ label = dynamic_cast<Label^>(control);
				if (label != nullptr) {
					labelText = label->Text;
					break;
				}
			}
			Label^ DayHandler = this->DayHandler;
			DayHandler->Text = labelText;
			currentDate->day = System::Convert::ToInt32(labelText);
		}
	}

	// Najechanie myszk¹ na dni bie¿¹cego miesi¹ca
	void PanelMouseEnterCrntMon(Object^ sender, EventArgs^ e) {
        Panel^ hoveredPanel = dynamic_cast<Panel^>(sender);
        if (hoveredPanel != nullptr) {
            this->Cursor = Cursors::Hand;
        }
    }

	// Najechanie myszk¹ na dni innego miesi¹ca
	void PanelMouseEnterOthMon(Object^ sender, EventArgs^ e) {
		Panel^ hoveredPanel = dynamic_cast<Panel^>(sender);
		if (hoveredPanel != nullptr) {
			this->Cursor = Cursors::No;
		}
	}

    // Wyjœcie myszki z obszaru panelu
    void PanelMouseLeave(Object^ sender, EventArgs^ e) {
        Panel^ leftPanel = dynamic_cast<Panel^>(sender);
        if (leftPanel != nullptr) {
            this->Cursor = Cursors::Default; 
        }
    }	
};
}

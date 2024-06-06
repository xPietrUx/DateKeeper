#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include "DateKeeperLib.h"
#include "CurrentDate.h"


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	//// Stuktura dla informacji o obcenej dacie
	//struct CurrentDate {
	//	int day;
	//	int month;
	//	int year;
	//};

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
				currentDate = new CurrentDate(CurrentDate::getCurrentDate());
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
		// Obecna data
		CurrentDate* currentDate;
		// Funkcja tworzenia dni miesi¹ca
		void CreateDays();
		// Zmienne pomocnicze
		int currentYear;
		int currentMonth;
		int currentDay;
		Panel^ panelListner;

		/*--- DateKeeperLib ---*/

		/*--- Funkcje przycisków ---*/

		// Dodawanie elementów do listBox i bazy danych
		void AddItemToListBox(String^ stringEvent);
		// Czyszczenie eventów z listBox
		void ClearEvents();
		// Przejœcie do poprzedniego miesi¹ca
		void handlePrevMonth();
		// Przejœcie do nastêpnego miesi¹ca
		void handleNextMonth();
		// Pokazanie eventów w listBox na zanzaonczy panel z bazy danych
		void ShowEvents();
		// Sprawdzanie czy dzieñ mo¿e byæ oznaczony
		bool dayHasEvent(std::tm timeToCheck);
		// Dodawanie kropki
		void addDot(Panel^ panel);
		// Dodawanie kropki jaœniejszej
		void addDotLighter(Panel^ panel);
		// Usuwanie kropki
		void Form1::removeDot(Panel^ panel);
		void makePictureBoxRound(PictureBox^ pictureBox);

		/*--- Koniec ---*/
	private: System::Windows::Forms::Label^ Monday;
	private: System::Windows::Forms::Label^ Tuesday;
	private: System::Windows::Forms::Label^ Wednesday;
	private: System::Windows::Forms::Label^ Thursday;
	private: System::Windows::Forms::Label^ Friday;
	private: System::Windows::Forms::Label^ Saturday;
	private: System::Windows::Forms::Label^ Sunday;
	private: System::Windows::Forms::ListBox^ listBox;
	private: System::Windows::Forms::TextBox^ textBoxAddEvent;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ AddButtonText;
	private: System::Windows::Forms::Button^ DeleteButtonText;
	private: System::Windows::Forms::Label^ ErrorDisplay;
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
			this->listBox = (gcnew System::Windows::Forms::ListBox());
			this->textBoxAddEvent = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->AddButtonText = (gcnew System::Windows::Forms::Button());
			this->DeleteButtonText = (gcnew System::Windows::Forms::Button());
			this->ErrorDisplay = (gcnew System::Windows::Forms::Label());
			this->Monday = (gcnew System::Windows::Forms::Label());
			this->Tuesday = (gcnew System::Windows::Forms::Label());
			this->Wednesday = (gcnew System::Windows::Forms::Label());
			this->Thursday = (gcnew System::Windows::Forms::Label());
			this->Friday = (gcnew System::Windows::Forms::Label());
			this->Saturday = (gcnew System::Windows::Forms::Label());
			this->Sunday = (gcnew System::Windows::Forms::Label());
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
			this->PreviousBtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->PreviousBtn->FlatStyle = System::Windows::Forms::FlatStyle::System;
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
			this->NextBtn->Cursor = System::Windows::Forms::Cursors::Hand;
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
			this->MonthHandler->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->MonthHandler->Location = System::Drawing::Point(252, 53);
			this->MonthHandler->Name = L"MonthHandler";
			this->MonthHandler->Size = System::Drawing::Size(271, 46);
			this->MonthHandler->TabIndex = 3;
			this->MonthHandler->Text = L"MonthHandler";
			this->MonthHandler->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// YearHandler
			// 
			this->YearHandler->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->YearHandler->Location = System::Drawing::Point(260, 99);
			this->YearHandler->Name = L"YearHandler";
			this->YearHandler->Size = System::Drawing::Size(263, 45);
			this->YearHandler->TabIndex = 4;
			this->YearHandler->Text = L"YearHandler";
			this->YearHandler->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// DayHandler
			// 
			this->DayHandler->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->DayHandler->Location = System::Drawing::Point(260, 12);
			this->DayHandler->Name = L"DayHandler";
			this->DayHandler->Size = System::Drawing::Size(263, 41);
			this->DayHandler->TabIndex = 6;
			this->DayHandler->Text = L"DayHandler";
			this->DayHandler->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// listBox
			// 
			this->listBox->Cursor = System::Windows::Forms::Cursors::Hand;
			this->listBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->listBox->FormattingEnabled = true;
			this->listBox->ItemHeight = 20;
			this->listBox->Location = System::Drawing::Point(808, 214);
			this->listBox->Name = L"listBox";
			this->listBox->Size = System::Drawing::Size(370, 644);
			this->listBox->TabIndex = 7;
			// 
			// textBoxAddEvent
			// 
			this->textBoxAddEvent->Location = System::Drawing::Point(808, 87);
			this->textBoxAddEvent->MaxLength = 1000;
			this->textBoxAddEvent->Name = L"textBoxAddEvent";
			this->textBoxAddEvent->Size = System::Drawing::Size(156, 20);
			this->textBoxAddEvent->TabIndex = 8;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(802, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(139, 31);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Add Event";
			// 
			// AddButtonText
			// 
			this->AddButtonText->Cursor = System::Windows::Forms::Cursors::Hand;
			this->AddButtonText->Location = System::Drawing::Point(808, 113);
			this->AddButtonText->Name = L"AddButtonText";
			this->AddButtonText->Size = System::Drawing::Size(75, 23);
			this->AddButtonText->TabIndex = 10;
			this->AddButtonText->Text = L"Add";
			this->AddButtonText->UseVisualStyleBackColor = true;
			this->AddButtonText->Click += gcnew System::EventHandler(this, &Form1::AddButtonText_Click);
			// 
			// DeleteButtonText
			// 
			this->DeleteButtonText->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DeleteButtonText->Location = System::Drawing::Point(889, 113);
			this->DeleteButtonText->Name = L"DeleteButtonText";
			this->DeleteButtonText->Size = System::Drawing::Size(75, 23);
			this->DeleteButtonText->TabIndex = 11;
			this->DeleteButtonText->Text = L"Delete";
			this->DeleteButtonText->UseVisualStyleBackColor = true;
			this->DeleteButtonText->Click += gcnew System::EventHandler(this, &Form1::DeleteButtonText_Click);
			// 
			// ErrorDisplay
			// 
			this->ErrorDisplay->AutoSize = true;
			this->ErrorDisplay->Location = System::Drawing::Point(805, 198);
			this->ErrorDisplay->Name = L"ErrorDisplay";
			this->ErrorDisplay->Size = System::Drawing::Size(0, 13);
			this->ErrorDisplay->TabIndex = 14;
			// 
			// Monday
			// 
			this->Monday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Monday->Location = System::Drawing::Point(12, 186);
			this->Monday->Name = L"Monday";
			this->Monday->Size = System::Drawing::Size(100, 25);
			this->Monday->TabIndex = 15;
			this->Monday->Text = L"Mon";
			this->Monday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Tuesday
			// 
			this->Tuesday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Tuesday->Location = System::Drawing::Point(118, 186);
			this->Tuesday->Name = L"Tuesday";
			this->Tuesday->Size = System::Drawing::Size(100, 25);
			this->Tuesday->TabIndex = 16;
			this->Tuesday->Text = L"Tue";
			this->Tuesday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Wednesday
			// 
			this->Wednesday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Wednesday->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
			this->Wednesday->Location = System::Drawing::Point(224, 186);
			this->Wednesday->Name = L"Wednesday";
			this->Wednesday->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->Wednesday->Size = System::Drawing::Size(100, 25);
			this->Wednesday->TabIndex = 17;
			this->Wednesday->Text = L"Wed";
			this->Wednesday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Thursday
			// 
			this->Thursday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Thursday->Location = System::Drawing::Point(330, 186);
			this->Thursday->Name = L"Thursday";
			this->Thursday->Size = System::Drawing::Size(100, 25);
			this->Thursday->TabIndex = 18;
			this->Thursday->Text = L"Thu";
			this->Thursday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Friday
			// 
			this->Friday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Friday->Location = System::Drawing::Point(436, 186);
			this->Friday->Name = L"Friday";
			this->Friday->Size = System::Drawing::Size(100, 25);
			this->Friday->TabIndex = 19;
			this->Friday->Text = L"Fri";
			this->Friday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Saturday
			// 
			this->Saturday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Saturday->Location = System::Drawing::Point(542, 186);
			this->Saturday->Name = L"Saturday";
			this->Saturday->Size = System::Drawing::Size(100, 25);
			this->Saturday->TabIndex = 20;
			this->Saturday->Text = L"Sat";
			this->Saturday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Sunday
			// 
			this->Sunday->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->Sunday->Location = System::Drawing::Point(648, 186);
			this->Sunday->Name = L"Sunday";
			this->Sunday->Size = System::Drawing::Size(100, 25);
			this->Sunday->TabIndex = 21;
			this->Sunday->Text = L"Sun";
			this->Sunday->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1190, 885);
			this->Controls->Add(this->Sunday);
			this->Controls->Add(this->Saturday);
			this->Controls->Add(this->Friday);
			this->Controls->Add(this->Thursday);
			this->Controls->Add(this->Wednesday);
			this->Controls->Add(this->Tuesday);
			this->Controls->Add(this->Monday);
			this->Controls->Add(this->ErrorDisplay);
			this->Controls->Add(this->DeleteButtonText);
			this->Controls->Add(this->AddButtonText);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxAddEvent);
			this->Controls->Add(this->listBox);
			this->Controls->Add(this->DayHandler);
			this->Controls->Add(this->YearHandler);
			this->Controls->Add(this->MonthHandler);
			this->Controls->Add(this->NextBtn);
			this->Controls->Add(this->PreviousBtn);
			this->Controls->Add(this->DaysContainer);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DateKeeper";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Za³adowanie From
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		CreateDays();
		Label^ DayHandler = this->DayHandler;
		DayHandler->Text = (currentDate->day).ToString();
		ClearEvents();
		ShowEvents();
	}

	// Przejœcie do poprzedniego miesi¹ca
	private: System::Void PreviousBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		ErrorDisplay->Text = nullptr;
		ClearEvents();
		handlePrevMonth();
		CreateDays();
		if (currentDate->day == 0) {
			DayHandler->Text = nullptr;
		}
	}

	// Przejœcie do nastêpnego miesi¹ca
	private: System::Void NextBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		ErrorDisplay->Text = nullptr;
		ClearEvents();
		handleNextMonth();
		CreateDays();
		if (currentDate->day == 0) {
			DayHandler->Text = nullptr;
		}
	}

	// Klikniecie na dzieñ
	void PanelClick(Object^ sender, EventArgs^ e) {
		ErrorDisplay->Text = nullptr;

		// Wyczyszczenie listBox
		ClearEvents();

		// Przywrócenie oryginalnego koloru wszystkich paneli
		for each (Control ^ control in this->DaysContainer->Controls) {
			Panel^ panel = dynamic_cast<Panel^>(control);
			if (panel != nullptr) {
				panel->BackColor = System::Drawing::Color::White;
			}
		}

		// Wybranie klikniêtego panelu
		Panel^ clickedPanel = dynamic_cast<Panel^>(sender);
		clickedPanel->BackColor = System::Drawing::Color::Gray;
		panelListner = clickedPanel;
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
			ShowEvents();
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

	// Dodawanie Eventów do listBox
	private: System::Void AddButtonText_Click(System::Object^ sender, System::EventArgs^ e) {
		ErrorDisplay->Text = nullptr;
		String^ eventString = this->textBoxAddEvent->Text;
		Panel^ panel = panelListner;

		if (eventString != "" && currentDate->day != 0) {
			// String do ³¹czenia siê baz¹
			String^ connectionString = "Server=localhost;Database=DateKeeper;Trusted_Connection=True;";

			// Tworzenie po³¹czenia z baz¹ danych
			SqlConnection^ connection = gcnew SqlConnection(connectionString);

			// Komenda do dodawania
			SqlCommand^ command = gcnew SqlCommand("INSERT INTO date_event (date_event, event) VALUES('" + currentDate->year + "-" + currentDate->month + "-" + currentDate->day + "', '" + eventString + "');", connection);

			try {
				connection->Open();
				command->ExecuteNonQuery();
			}
			catch (Exception^ ex) {
				ErrorDisplay->Text = ex->Message;
			}
			finally {
				connection->Close();
			}
			textBoxAddEvent->Text = "";
			ClearEvents();
			ShowEvents();
			addDot(panelListner);
		}
		else {
			ErrorDisplay->Text = "Make sure that event is not empty and the appropriate date is selected";
		}
	}

	// Usuwanie elementu z bazy
	private: System::Void DeleteButtonText_Click(System::Object^ sender, System::EventArgs^ e) {
		ErrorDisplay->Text = nullptr;
		if (listBox->SelectedItem != nullptr && currentDate->day != 0) {

			// Pobranie elementu wybranego z listBox
			String^ selectedItem = listBox->SelectedItem->ToString();

			// String do ³¹czenia siê baz¹
			String^ connectionString = "Server=localhost;Database=DateKeeper;Trusted_Connection=True;";

			// Tworzenie po³¹czenia z baz¹ danych
			SqlConnection^ connection = gcnew SqlConnection(connectionString);

			// Komenda do usuwania
			SqlCommand^ command = gcnew SqlCommand("DELETE FROM date_event WHERE date_event.event = '" + selectedItem + "'", connection);

			try {
				connection->Open();
				command->ExecuteNonQuery();

			}
			catch (Exception^ ex) {
				ErrorDisplay->Text = ex->Message;
			}
			finally {
				connection->Close();
			}
			removeDot(panelListner);
			ClearEvents();
			ShowEvents();
		}
		else {
			ErrorDisplay->Text = "Make sure that element is selected and the appropriate date is choosed";
		}
	}
};
}

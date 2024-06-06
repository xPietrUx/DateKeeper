#include "pch.h"
#include "Form1.h"

using namespace CppCLRWinFormsProject;

// Pobranie obecnej daty
CurrentDate* Form1::getCurrentDate() {
	std::time_t now = std::time(nullptr);

	std::tm localTime;

	if (localtime_s(&localTime, &now) != 0) {
		std::cerr << "B³¹d podczas pobierania lokalnego czasu!" << std::endl;
		return nullptr;
	}

	int day = localTime.tm_mday + 1;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;

	CurrentDate* date = new CurrentDate;
	date->day = day;
	date->month = month;
	date->year = year;

	return date;
}

// Funkcja tworzenia dni miesi¹ca
void Form1::CreateDays() {

	// Tablica z dat¹ nie mo¿e byæ pusta
	if (currentDate == nullptr) {
		return;
	}

	std::time_t now = std::time(nullptr);

	std::tm localTime;

	if (localtime_s(&localTime, &now) != 0) {
		std::cerr << "B³¹d podczas pobierania lokalnego czasu!" << std::endl;
	}

	// Zmienne pomocnicze
	currentMonth = currentDate->month;
	currentYear = currentDate->year;
	currentDay = currentDate->day;

	Label^ DayHandler = this->DayHandler;
	DayHandler->Text = currentDay.ToString();

	// Wyœwietlanie miesi¹ca
	Label^ MonthHandler = this->MonthHandler;
	array<String^>^ monthNames = gcnew array<String^>{
		"January", "February", "March", "April", "May",
			"June", "July", "August", "September", "October", "November", "December"
	};
	MonthHandler->Text = monthNames[currentMonth - 1];

	// Wyœwietlanie roku
	Label^ YearHandler = this->YearHandler;
	YearHandler->Text = currentDate->year.ToString();

	//Czyszczenie przed tworzeniem dni
	FlowLayoutPanel^ flowLayoutPanel1 = this->DaysContainer;
	flowLayoutPanel1->Controls->Clear();

	// Dekklaracja pierwszego i ostatniego dnia miesi¹ca
	std::tm firstDayOfMonth = newDate(currentYear, currentMonth, 1);
	std::tm lastDayOfMonth = newDate(currentYear, currentMonth + 1, 0);

	// Dni poprzedniego miesi¹ca
	for (int i = 0; i < firstDayOfMonth.tm_wday; i++) {
		std::tm previousMonthDate = newDate(currentYear, currentMonth - 1, -i);

		Label^ label = gcnew Label();
		label->Size = System::Drawing::Size(20, 20);
		label->Text = previousMonthDate.tm_mday.ToString();

		Panel^ panel = gcnew Panel();
		panel->MouseEnter += gcnew System::EventHandler(this, &Form1::PanelMouseEnterOthMon);
		panel->MouseLeave += gcnew System::EventHandler(this, &Form1::PanelMouseLeave);
		panel->BorderStyle = BorderStyle::FixedSingle;
		panel->BackColor = System::Drawing::Color::White;
		panel->Size = System::Drawing::Size(100, 100);
		panel->Controls->Add(label);

		flowLayoutPanel1->Controls->Add(panel);
	}

	// Dni bie¿¹cego miesi¹ca
	for (int i = 1; i <= lastDayOfMonth.tm_mday + 1; i++) {
		Label^ label = gcnew Label();
		label->Size = System::Drawing::Size(20, 20);
		label->Text = i.ToString();
		if (i == localTime.tm_mday && currentMonth == localTime.tm_mon + 1) {
			label->ForeColor = System::Drawing::Color::Red;
		}

		Panel^ panel = gcnew Panel();
		panel->MouseEnter += gcnew System::EventHandler(this, &Form1::PanelMouseEnterCrntMon);
		panel->MouseLeave += gcnew System::EventHandler(this, &Form1::PanelMouseLeave);
		panel->BorderStyle = BorderStyle::FixedSingle;
		panel->Size = System::Drawing::Size(100, 100);
		panel->BackColor = System::Drawing::Color::White;
		panel->Click += gcnew System::EventHandler(this, &Form1::PanelClick);
		panel->Controls->Add(label);

		flowLayoutPanel1->Controls->Add(panel);
	}

	// Dni nastêpnego miesi¹ca
	for (int i = 1; flowLayoutPanel1->Controls->Count < 42; i++) {
		std::tm nextMonthDate = newDate(currentYear, currentMonth + 1, i + 1);

		Label^ label = gcnew Label();
		label->Size = System::Drawing::Size(20, 20);
		label->Text = nextMonthDate.tm_mday.ToString();

		Panel^ panel = gcnew Panel();
		panel->MouseEnter += gcnew System::EventHandler(this, &Form1::PanelMouseEnterOthMon);
		panel->MouseLeave += gcnew System::EventHandler(this, &Form1::PanelMouseLeave);
		panel->BorderStyle = BorderStyle::FixedSingle;
		panel->BackColor = System::Drawing::Color::White;
		panel->Size = System::Drawing::Size(100, 100);
		panel->Controls->Add(label);

		flowLayoutPanel1->Controls->Add(panel);
	}

	delete monthNames;
}
#include "pch.h"
#include "Form1.h"

using namespace CppCLRWinFormsProject;

// Funkcja tworzenia dni miesi�ca
void Form1::CreateDays() {

	// Tablica z dat� nie mo�e by� pusta
	if (currentDate == nullptr) {
		return;
	}

	CurrentDate* currentDateToCheck = new CurrentDate(CurrentDate::getCurrentDate());

	// Zmienne pomocnicze
	currentMonth = currentDate->month;
	currentYear = currentDate->year;
	currentDay = currentDate->day;

	Label^ DayHandler = this->DayHandler;
	DayHandler->Text = currentDay.ToString();

	// Wy�wietlanie miesi�ca
	Label^ MonthHandler = this->MonthHandler;
	array<String^>^ monthNames = gcnew array<String^>{
		"January", "February", "March", "April", "May",
			"June", "July", "August", "September", "October", "November", "December"
	};
	MonthHandler->Text = monthNames[currentMonth - 1];

	// Wy�wietlanie roku
	Label^ YearHandler = this->YearHandler;
	YearHandler->Text = currentDate->year.ToString();

	//Czyszczenie przed tworzeniem dni
	FlowLayoutPanel^ flowLayoutPanel1 = this->DaysContainer;
	flowLayoutPanel1->Controls->Clear();

	// Dekklaracja pierwszego dnia miesi�ca
	std::tm firstDayOfMonth = newDate(currentYear, currentMonth, 1);
	// Deklaracja ostatniego dnia miesi�ca
	std::tm lastDayOfMonth = newDate(currentYear, currentMonth + 1, 0);

	// Dni poprzedniego miesi�ca
	for (int i = firstDayOfMonth.tm_wday; i > 0; i--) {
		// Zmienna do zaznaczania czy dzie� ma event i odpowiedniej iteracji dni
		std::tm previousMonthDate = newDate(currentYear, currentMonth, -i + 2);

		Label^ label = gcnew Label();
		label->Size = System::Drawing::Size(30, 30);
		label->ForeColor = System::Drawing::Color::LightGray;
		label->Text = previousMonthDate.tm_mday.ToString();

		Panel^ panel = gcnew Panel();
		panel->MouseEnter += gcnew System::EventHandler(this, &Form1::PanelMouseEnterOthMon);
		panel->MouseLeave += gcnew System::EventHandler(this, &Form1::PanelMouseLeave);
		panel->BorderStyle = BorderStyle::FixedSingle;
		panel->BackColor = System::Drawing::Color::White;
		panel->Size = System::Drawing::Size(100, 100);
		panel->Controls->Add(label);

		bool hasEvent = dayHasEvent(previousMonthDate);

		// Dodawanie obrazka je�li jest w bazie danych
		if (hasEvent) {
			addDotLighter(panel);
		}

		flowLayoutPanel1->Controls->Add(panel);
	}

	// Dni bie��cego miesi�ca
	for (int i = 1; i <= lastDayOfMonth.tm_mday + 1; i++) {
		// Zmienna do zaznaczania czy dzie� ma event
		std::tm currentMonthDate = newDate(currentYear, currentMonth, i + 1);

		Label^ label = gcnew Label();
		label->Size = System::Drawing::Size(20, 20);
		label->Text = i.ToString();

		if (i == currentDateToCheck->day && currentMonth == currentDateToCheck->month && currentDateToCheck->year == currentDate->year) {
			label->ForeColor = System::Drawing::Color::Red;
			currentDate->day = currentDateToCheck->day;
			DayHandler->Text = currentDateToCheck->day.ToString();
			ShowEvents();
		}

		Panel^ panel = gcnew Panel();
		panel->MouseEnter += gcnew System::EventHandler(this, &Form1::PanelMouseEnterCrntMon);
		panel->MouseLeave += gcnew System::EventHandler(this, &Form1::PanelMouseLeave);
		panel->BorderStyle = BorderStyle::FixedSingle;
		panel->Size = System::Drawing::Size(100, 100);
		panel->BackColor = System::Drawing::Color::White;
		if (i == currentDateToCheck->day && currentMonth == currentDateToCheck->month  && currentDateToCheck->year == currentDate->year) {
			panel->BackColor = System::Drawing::Color::Gray;
		}
		panel->Click += gcnew System::EventHandler(this, &Form1::PanelClick);
		panel->Controls->Add(label);

		bool hasEvent = dayHasEvent(currentMonthDate);

		// Dodawanie obrazka je�li jest w bazie danych event
		if (hasEvent) {
			addDot(panel);
		}

		flowLayoutPanel1->Controls->Add(panel);
	}

	// Dni nast�pnego miesi�ca
	for (int i = 1; flowLayoutPanel1->Controls->Count < 42; i++) {
		// Zmienna do zaznaczania czy dzie� ma event i odpowiedniej iteracji dni
		std::tm nextMonthDate = newDate(currentYear, currentMonth + 1, i + 1);

		Label^ label = gcnew Label();
		label->Size = System::Drawing::Size(20, 20);
		label->ForeColor = System::Drawing::Color::LightGray;
		label->Text = nextMonthDate.tm_mday.ToString();

		Panel^ panel = gcnew Panel();
		panel->MouseEnter += gcnew System::EventHandler(this, &Form1::PanelMouseEnterOthMon);
		panel->MouseLeave += gcnew System::EventHandler(this, &Form1::PanelMouseLeave);
		panel->BorderStyle = BorderStyle::FixedSingle;
		panel->BackColor = System::Drawing::Color::White;
		panel->Size = System::Drawing::Size(100, 100);
		panel->Controls->Add(label);

		bool hasEvent = dayHasEvent(nextMonthDate);

		// Dodawanie obrazka je�li jest w bazie danych
		if (hasEvent) {
			addDotLighter(panel);
		}

		flowLayoutPanel1->Controls->Add(panel);
	}

	delete monthNames;
}

// Przej�cie do nast�pnego miesi�ca
void Form1::handleNextMonth() {
	currentDate->month++;
	currentDate->day = 0;
	if (currentDate->month > 12) {
		currentDate->month = 1;
		currentDate->year++;
	}
}

// Przej�cie do poprzedniego miesi�ca
void Form1::handlePrevMonth() {
	currentDate->month--;
	currentDate->day = 0;
	if (currentDate->month < 1) {
		currentDate->month = 12;
		currentDate->year--;
	}
}

// Dodawanie element�w do listBox
void Form1::AddItemToListBox(String^ stringEvent) {
		String^ itemText = stringEvent->ToString();

		listBox->Items->Add(itemText);
	}

// Pokazanie event�w w listBox na zanzaonczy panel
void Form1::ShowEvents() {
	// String do ��czenia si� baz�
	String^ connectionString = "Server=localhost;Database=DateKeeper;Trusted_Connection=True;";

	// Tworzenie po��czenia z baz� danych
	SqlConnection^ connection = gcnew SqlConnection(connectionString);

	try {
		// Otwarcie po��czenia
		connection->Open();

		// Tworzenie zapytania SQL
		String^ query = "SELECT * FROM date_event WHERE date_event.date_event = '" + currentDate->year + "-" + currentDate->month + "-" + currentDate->day + "'";

		// Tworzenie obiektu SqlCommand
		SqlCommand^ command = gcnew SqlCommand(query, connection);

		// Tworzenie obiektu SqlDataReader do odczytu danych
		SqlDataReader^ reader = command->ExecuteReader();

		// Odczytywanie danych
		while (reader->Read()) {
			DateTime date = reader->GetDateTime(0);
			String^ dateEvent = reader->GetString(1);
			AddItemToListBox(dateEvent);
		}

		// Zamkni�cie czytnika
		reader->Close();
	}
	catch (Exception^ ex) {
		ErrorDisplay->Text = ex->Message;
	}
	finally {
		// Zamkni�cie po��czenia
		connection->Close();
	}

};

// Czyszczenie event�w z listBox
void Form1::ClearEvents() {
	listBox->Items->Clear();
}

bool Form1::dayHasEvent(std::tm timeToCheck) {
	// String do ��czenia si� baz�
	String^ connectionString = "Server=localhost;Database=DateKeeper;Trusted_Connection=True;";

	// Tworzenie po��czenia z baz� danych
	SqlConnection^ connection = gcnew SqlConnection(connectionString);

	// Flaga sprawdzaj�ca czy dzie� jest w bazie danych
	bool hasEvent = false;

	try {
		// Otwarcie po��czenia
		connection->Open();

		// Tworzenie zapytania SQL
		String^ query = "SELECT * FROM date_event WHERE date_event.date_event = '" +
			(timeToCheck.tm_year + 1900) + "-" +
			(timeToCheck.tm_mon + 1) + "-" +
			timeToCheck.tm_mday + "'";

		// Tworzenie obiektu SqlCommand
		SqlCommand^ command = gcnew SqlCommand(query, connection);

		// Tworzenie obiektu SqlDataReader do odczytu danych
		SqlDataReader^ reader = command->ExecuteReader();

		// Odczytywanie danych
		hasEvent = reader->HasRows;

		// Zamkni�cie czytnika
		reader->Close();
	}
	catch (Exception^ ex) {
		ErrorDisplay->Text = ex->Message;
	}
	finally {
		// Zamkni�cie po��czenia
		connection->Close();
	}

	return hasEvent;
}

// Dodawanie kropki
void Form1::addDot(Panel^ panel) {
	PictureBox^ pictureBox = gcnew PictureBox();
	//pictureBox->ImageLocation = "../img/currentMonthDot.png";
	pictureBox->Size = System::Drawing::Size(10, 10);
	pictureBox->Location = System::Drawing::Point((panel->Width - pictureBox->Width) / 2, (panel->Height - pictureBox->Height) / 2);
	pictureBox->BackColor = System::Drawing::Color::Blue;
	makePictureBoxRound(pictureBox);
	panel->Controls->Add(pictureBox);
}

// Dodawanie kropki
void Form1::addDotLighter(Panel^ panel) {
	PictureBox^ pictureBox = gcnew PictureBox();
	pictureBox->Size = System::Drawing::Size(10, 10);
	pictureBox->Location = System::Drawing::Point((panel->Width - pictureBox->Width) / 2, (panel->Height - pictureBox->Height) / 2);
	pictureBox->BackColor = System::Drawing::Color::LightBlue;
	makePictureBoxRound(pictureBox);
	panel->Controls->Add(pictureBox);
}

// Usuwanie kropki
void Form1::removeDot(Panel^ panel) {
	for each (Control ^ control in panel->Controls) {
		PictureBox^ pictureBox = dynamic_cast<PictureBox^>(control);
		panel->Controls->Remove(pictureBox);
	}
}

// Stworzenie kropki
void Form1::makePictureBoxRound(PictureBox^ pictureBox) {
	System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
	path->AddEllipse(0, 0, pictureBox->Width, pictureBox->Height);
	pictureBox->Region = gcnew System::Drawing::Region(path);
}
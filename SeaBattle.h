#pragma once
#include "Game.h"

namespace CourseWork {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для SeaBattle
	/// </summary>
	public ref class SeaBattle : public System::Windows::Forms::Form
	{
	private:
		int DXY = 60, H = 30;
		Drawing::Rectangle ship1, ship2, ship3, ship4;
		int s1, s2, s3, s4;
		bool selectS1, selectS2, selectS3, selectS4;
		bool vert, rasstanovka;
		Game^ game;
		Image ^wound, ^kill, ^deck, ^miss;
	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ PlayMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ PVEMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AutoPlacementMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ UserPlacementMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SpravkaMenuItem;
	private: System::Windows::Forms::Button^ orientation_button;
	private: System::Windows::Forms::Label^ Placelabel;


	private: System::Windows::Forms::Timer^ timer;
	public:
		SeaBattle(void)
		{
			System::ComponentModel::ComponentResourceManager^ resourses = gcnew System::ComponentModel::ComponentResourceManager(SeaBattle::typeid);
			InitializeComponent();
			game = gcnew Game();
			deck = Image::FromFile("deck.png");
			kill = Image::FromFile("kill.png");
			wound = Image::FromFile("wound.png");
			miss = Image::FromFile("miss.png");
			/*try {
				deck = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("deck"));
				kill = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("kill"));
				wound = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("wound"));
				miss = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("miss"));
			}
			catch (...)
			{
			}*/
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~SeaBattle()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->PlayMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PVEMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AutoPlacementMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UserPlacementMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SpravkaMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->orientation_button = (gcnew System::Windows::Forms::Button());
			this->Placelabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer
			// 
			this->timer->Interval = 1;
			this->timer->Tick += gcnew System::EventHandler(this, &SeaBattle::timer_Tick);
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(0, 27);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1100, 572);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SeaBattle::pictureBox_Paint);
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &SeaBattle::pictureBox_MouseClick);
			// 
			// menuStrip
			// 
			this->menuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->PlayMenuItem, this->SpravkaMenuItem });
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1082, 28);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// PlayMenuItem
			// 
			this->PlayMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->PVEMenuItem });
			this->PlayMenuItem->Name = L"PlayMenuItem";
			this->PlayMenuItem->Size = System::Drawing::Size(71, 24);
			this->PlayMenuItem->Text = L"Играть";
			// 
			// PVEMenuItem
			// 
			this->PVEMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->AutoPlacementMenuItem,
					this->UserPlacementMenuItem
			});
			this->PVEMenuItem->Name = L"PVEMenuItem";
			this->PVEMenuItem->Size = System::Drawing::Size(279, 26);
			this->PVEMenuItem->Text = L"Игрок против компьютера";
			// 
			// AutoPlacementMenuItem
			// 
			this->AutoPlacementMenuItem->Name = L"AutoPlacementMenuItem";
			this->AutoPlacementMenuItem->Size = System::Drawing::Size(230, 26);
			this->AutoPlacementMenuItem->Text = L"Авторасстановка";
			this->AutoPlacementMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::AutoPlacementMenuItem_Click);
			// 
			// UserPlacementMenuItem
			// 
			this->UserPlacementMenuItem->Name = L"UserPlacementMenuItem";
			this->UserPlacementMenuItem->Size = System::Drawing::Size(230, 26);
			this->UserPlacementMenuItem->Text = L"Ручная расстановка";
			this->UserPlacementMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::UserPlacementMenuItem_Click);
			// 
			// SpravkaMenuItem
			// 
			this->SpravkaMenuItem->Name = L"SpravkaMenuItem";
			this->SpravkaMenuItem->Size = System::Drawing::Size(81, 24);
			this->SpravkaMenuItem->Text = L"Справка";
			// 
			// orientation_button
			// 
			this->orientation_button->BackColor = System::Drawing::Color::White;
			this->orientation_button->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->orientation_button->Location = System::Drawing::Point(820, 340);
			this->orientation_button->Name = L"orientation_button";
			this->orientation_button->Size = System::Drawing::Size(208, 34);
			this->orientation_button->TabIndex = 2;
			this->orientation_button->Text = L"Повернуть корабли";
			this->orientation_button->UseVisualStyleBackColor = false;
			this->orientation_button->Visible = false;
			this->orientation_button->Click += gcnew System::EventHandler(this, &SeaBattle::orientation_button_Click);
			// 
			// Placelabel
			// 
			this->Placelabel->BackColor = System::Drawing::Color::White;
			this->Placelabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Placelabel->Location = System::Drawing::Point(815, 51);
			this->Placelabel->Name = L"Placelabel";
			this->Placelabel->Size = System::Drawing::Size(215, 25);
			this->Placelabel->TabIndex = 3;
			this->Placelabel->Text = L"Расставьте корабли";
			this->Placelabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Placelabel->Visible = false;
			// 
			// SeaBattle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1082, 553);
			this->Controls->Add(this->Placelabel);
			this->Controls->Add(this->orientation_button);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"SeaBattle";
			this->Text = L"SeaBattle";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: void DrawFields(Graphics^ g);

	private: void DrawShips(Graphics^ g);

	private: void DrawPlacementShips(Graphics^ g);

	private: void SelectShip(MouseEventArgs^ e);

	private: void PlaceShip(MouseEventArgs^ e);
	

private: System::Void pictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;
	g->Clear(Color::White);
	DrawFields(g);
	DrawShips(g);
	if (rasstanovka)
		DrawPlacementShips(g);
}

private: System::Void pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (game->IsEndGame()==0 && !rasstanovka)
	{
		int MX = e->X;
		int MY = e->Y;
		if (MX > DXY + 13 * H && MY > DXY && MX < DXY + 23 * H && MY < DXY + 10 * H && game->IsEndGame() == 0) {
			int i = (MX - (DXY + 13 * H)) / H;
			int j = (MY - DXY) / H;
			if (game->CompField.GetValue(i, j) >= -1 && game->CompField.GetValue(i, j) <= 4) {
				game->PlayerMove(i, j);
			}
		}
	}
	if (rasstanovka) {
		SelectShip(e);
		PlaceShip(e);
	}
}

private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
	this->pictureBox->Invalidate();
}
private: System::Void AutoPlacementMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	rasstanovka = 0;
	timer->Start();
	game->Start(rasstanovka);
}
private: System::Void UserPlacementMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	rasstanovka = 1;
	vert = 1;
	s4 = 1;
	s3 = 2;
	s2 = 3;
	s1 = 4;
	game->Start(rasstanovka);
	timer->Start();
}
private: System::Void orientation_button_Click(System::Object^ sender, System::EventArgs^ e) {
	vert = !vert;
}
};
}

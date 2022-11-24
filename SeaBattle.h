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
		int DXY = 80, H = 30;
		Drawing::Rectangle ship1, ship2, ship3, ship4, field1, field2;
		int s1, s2, s3, s4;
		bool selectS1, selectS2, selectS3, selectS4;
		bool vert, rasstanovka;
		Game^ game;
		Image^ wound, ^ kill, ^ deck, ^ miss;
		static const cli::array<String^>^ symbols = gcnew cli::array<String^> { "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К" };
		static const cli::array<String^>^ numbers = gcnew cli::array<String^> { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ PlayMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ PVEMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AutoPlacementMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ UserPlacementMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SpravkaMenuItem;
	private: System::Windows::Forms::Button^ orientation_button;
	private: System::Windows::Forms::Label^ Placelabel;
	private: System::Windows::Forms::Label^ playerFieldlabel;
	private: System::Windows::Forms::Label^ compFieldlabel;
	private: System::Windows::Forms::Label^ Countlabel;
	private: System::Windows::Forms::Timer^ timer;
	public:
		SeaBattle(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = gcnew System::ComponentModel::ComponentResourceManager(SeaBattle::typeid);
			InitializeComponent();
			game = gcnew Game();
			deck = Image::FromFile("deck.png");
			kill = Image::FromFile("kill.png");
			wound = Image::FromFile("wound.png");
			miss = Image::FromFile("miss.png");
			/*try
			{
			deck = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("deck"));
			kill = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("kill"));
			wound = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("wound"));
			miss = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("miss"));
			}
			catch (...)
			{
				MessageBox::Show("Ошибка при загрузке изображений");
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SeaBattle::typeid));
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
			this->playerFieldlabel = (gcnew System::Windows::Forms::Label());
			this->compFieldlabel = (gcnew System::Windows::Forms::Label());
			this->Countlabel = (gcnew System::Windows::Forms::Label());
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
			this->pictureBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->pictureBox->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox.BackgroundImage")));
			this->pictureBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox->Location = System::Drawing::Point(0, 30);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1083, 623);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
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
			this->menuStrip->Size = System::Drawing::Size(1083, 28);
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
			this->orientation_button->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->orientation_button->Location = System::Drawing::Point(820, 347);
			this->orientation_button->Name = L"orientation_button";
			this->orientation_button->Size = System::Drawing::Size(208, 38);
			this->orientation_button->TabIndex = 2;
			this->orientation_button->Text = L"Повернуть корабли";
			this->orientation_button->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->orientation_button->UseVisualStyleBackColor = false;
			this->orientation_button->Visible = false;
			this->orientation_button->Click += gcnew System::EventHandler(this, &SeaBattle::orientation_button_Click);
			// 
			// Placelabel
			// 
			this->Placelabel->BackColor = System::Drawing::Color::White;
			this->Placelabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Placelabel->Location = System::Drawing::Point(815, 51);
			this->Placelabel->Name = L"Placelabel";
			this->Placelabel->Size = System::Drawing::Size(215, 32);
			this->Placelabel->TabIndex = 3;
			this->Placelabel->Text = L"Расставьте корабли";
			this->Placelabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->Placelabel->Visible = false;
			// 
			// playerFieldlabel
			// 
			this->playerFieldlabel->BackColor = System::Drawing::Color::White;
			this->playerFieldlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->playerFieldlabel->Location = System::Drawing::Point(128, 43);
			this->playerFieldlabel->Name = L"playerFieldlabel";
			this->playerFieldlabel->Size = System::Drawing::Size(212, 33);
			this->playerFieldlabel->TabIndex = 4;
			this->playerFieldlabel->Text = L"Игрок";
			this->playerFieldlabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// compFieldlabel
			// 
			this->compFieldlabel->BackColor = System::Drawing::Color::White;
			this->compFieldlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->compFieldlabel->Location = System::Drawing::Point(508, 43);
			this->compFieldlabel->Name = L"compFieldlabel";
			this->compFieldlabel->Size = System::Drawing::Size(212, 33);
			this->compFieldlabel->TabIndex = 5;
			this->compFieldlabel->Text = L"Компьютер";
			this->compFieldlabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Countlabel
			// 
			this->Countlabel->BackColor = System::Drawing::Color::White;
			this->Countlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Countlabel->Location = System::Drawing::Point(820, 442);
			this->Countlabel->Name = L"Countlabel";
			this->Countlabel->Size = System::Drawing::Size(208, 95);
			this->Countlabel->TabIndex = 6;
			// 
			// SeaBattle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1083, 653);
			this->Controls->Add(this->Countlabel);
			this->Controls->Add(this->compFieldlabel);
			this->Controls->Add(this->playerFieldlabel);
			this->Controls->Add(this->Placelabel);
			this->Controls->Add(this->orientation_button);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->MaximumSize = System::Drawing::Size(1101, 700);
			this->MinimumSize = System::Drawing::Size(1101, 700);
			this->Name = L"SeaBattle";
			this->Text = L"Морской бой";
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

	private: void DrawRemainingShips(Graphics^ g);


	private: System::Void pictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		DrawFields(g);
		DrawRemainingShips(g);
		DrawShips(g);
		DrawPlacementShips(g);
	}

	private: System::Void pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (game->IsEndGame() == 0 && !rasstanovka)
		{
			if (field2.Contains(e->Location) && game->IsEndGame() == 0) {
				int mX = e->X;
				int mY = e->Y;
				int i = (mX - (DXY + 13 * H)) / H;
				int j = (mY - DXY) / H;
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
		timer->Start();
		game->Start(rasstanovka);
	}

	private: System::Void orientation_button_Click(System::Object^ sender, System::EventArgs^ e) {
		vert = !vert;
	}
	};
}

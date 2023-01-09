#pragma once
#include "Game.h"
#include "GamePVE.h"
#include "GamePVP.h"

namespace CourseWork {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::Serialization::Formatters::Binary;
	using namespace System::IO;

	/// <summary>
	/// Сводка для SeaBattle
	/// </summary>
	public ref class SeaBattle : public System::Windows::Forms::Form
	{
	private:
		Game^ game; //переменная абстрактного класса игра, с помощью которой будет реализован процесс игры
		GamePVE^ gamePVE; //переменная класса игры в режиме игрок против пк
		GamePVP^ gamePVP; //переменная класса игры в режиме игрок против игрока
		int gameMode; //режим игры: 1 - игрок против пк, 2 - игрок против игрока
		int DXY = 80; //смещение по X и Y при отрисовке элементов
		int H = 30; //коэффициент масштаба при отрисовке
		Drawing::Rectangle field1, field2; //прямогульники, образующие контур игровых полей
		Drawing::Rectangle ship1, ship2, ship3, ship4; //корабли в области расстановки
		int s1, s2, s3, s4; //число кораблей каждого типа, которые осталось расставить
		bool selectS1, selectS2, selectS3, selectS4; //флажки выбора корабля при расстановке
		bool rasstanovka; //логическая переменная, проверяющая выбран ли режим ручной расстановки
		bool vert; //логическая переменная определяющая положение кораблей в ручной расстановке
		Image^ wound, ^ kill, ^ deck, ^ miss; //изображения для отрисовки ранения, унчитожения палубы, самой палубы, промаха
		static const cli::array<String^>^ symbols = gcnew cli::array<String^> { "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К" }; //массив подписей столбцов полей
		static const cli::array<String^>^ numbers = gcnew cli::array<String^> { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }; //массив подписей строк полей
	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ PlayMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ PVEMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AutoPlacementMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ UserPlacementMenuItem;

	private: System::Windows::Forms::Button^ orientation_button;
	private: System::Windows::Forms::Label^ Placelabel;
	private: System::Windows::Forms::Label^ player1Fieldlabel;
	private: System::Windows::Forms::Label^ player2Fieldlabel;
	private: System::Windows::Forms::Label^ Countlabel;
	private: System::Windows::Forms::ToolStripMenuItem^ ProgramMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ FileMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SaveMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ LoadMenuItem;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::Button^ Clearbutton;
	private: System::Windows::Forms::ToolStripMenuItem^ PVPMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SpravkaMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AuthorMenuItem;


	private: System::Windows::Forms::Timer^ timer;
	public:
		SeaBattle(void)
		{
			InitializeComponent();
			gameMode = 0;
			player1Fieldlabel->Visible = false;
			player2Fieldlabel->Visible = false;
			Countlabel->Visible = false;
			/*deck = Image::FromFile("deck.png");
			kill = Image::FromFile("kill.png");
			wound = Image::FromFile("wound.png");
			miss = Image::FromFile("miss.png");*/
			System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(SeaBattle::typeid);
			try
			{
			deck = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("deck"));
			kill = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("kill"));
			wound = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("wound"));
			miss = cli::safe_cast<System::Drawing::Image^>(resources->GetObject("miss"));
			}
			catch (...)
			{
				MessageBox::Show("Ошибка при загрузке игровых файлов!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				Application::Exit();
			}
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
			this->PVPMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SaveMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ProgramMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SpravkaMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AuthorMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->orientation_button = (gcnew System::Windows::Forms::Button());
			this->Placelabel = (gcnew System::Windows::Forms::Label());
			this->player1Fieldlabel = (gcnew System::Windows::Forms::Label());
			this->player2Fieldlabel = (gcnew System::Windows::Forms::Label());
			this->Countlabel = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->Clearbutton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer
			// 
			this->timer->Interval = 200;
			this->timer->Tick += gcnew System::EventHandler(this, &SeaBattle::timer_Tick);
			// 
			// pictureBox
			// 
			this->pictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox.BackgroundImage")));
			this->pictureBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox->Location = System::Drawing::Point(0, 27);
			this->pictureBox->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1083, 634);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SeaBattle::pictureBox_Paint);
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &SeaBattle::pictureBox_MouseClick);
			// 
			// menuStrip
			// 
			this->menuStrip->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->menuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->PlayMenuItem, this->FileMenuItem,
					this->ProgramMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip->Size = System::Drawing::Size(1085, 28);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// PlayMenuItem
			// 
			this->PlayMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->PVEMenuItem,
					this->PVPMenuItem
			});
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
			// PVPMenuItem
			// 
			this->PVPMenuItem->Name = L"PVPMenuItem";
			this->PVPMenuItem->Size = System::Drawing::Size(279, 26);
			this->PVPMenuItem->Text = L"Игрок против игрока";
			this->PVPMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::PVPMenuItem_Click);
			// 
			// FileMenuItem
			// 
			this->FileMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->SaveMenuItem,
					this->LoadMenuItem
			});
			this->FileMenuItem->Name = L"FileMenuItem";
			this->FileMenuItem->Size = System::Drawing::Size(108, 24);
			this->FileMenuItem->Text = L"Сохранение";
			// 
			// SaveMenuItem
			// 
			this->SaveMenuItem->Name = L"SaveMenuItem";
			this->SaveMenuItem->Size = System::Drawing::Size(201, 26);
			this->SaveMenuItem->Text = L"Сохранить игру";
			this->SaveMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::SaveMenuItem_Click);
			// 
			// LoadMenuItem
			// 
			this->LoadMenuItem->Name = L"LoadMenuItem";
			this->LoadMenuItem->Size = System::Drawing::Size(201, 26);
			this->LoadMenuItem->Text = L"Загрузить игру";
			this->LoadMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::LoadMenuItem_Click);
			// 
			// ProgramMenuItem
			// 
			this->ProgramMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->SpravkaMenuItem,
					this->AuthorMenuItem
			});
			this->ProgramMenuItem->Name = L"ProgramMenuItem";
			this->ProgramMenuItem->Size = System::Drawing::Size(118, 24);
			this->ProgramMenuItem->Text = L"О программе";
			// 
			// SpravkaMenuItem
			// 
			this->SpravkaMenuItem->Name = L"SpravkaMenuItem";
			this->SpravkaMenuItem->Size = System::Drawing::Size(224, 26);
			this->SpravkaMenuItem->Text = L"Справка";
			this->SpravkaMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::SpravkaMenuItem_Click);
			// 
			// AuthorMenuItem
			// 
			this->AuthorMenuItem->Name = L"AuthorMenuItem";
			this->AuthorMenuItem->Size = System::Drawing::Size(224, 26);
			this->AuthorMenuItem->Text = L"Об авторе";
			this->AuthorMenuItem->Click += gcnew System::EventHandler(this, &SeaBattle::AuthorMenuItem_Click);
			// 
			// orientation_button
			// 
			this->orientation_button->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->orientation_button->BackColor = System::Drawing::Color::White;
			this->orientation_button->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->orientation_button->Location = System::Drawing::Point(820, 347);
			this->orientation_button->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
			this->Placelabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Placelabel->BackColor = System::Drawing::Color::White;
			this->Placelabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Placelabel->Location = System::Drawing::Point(815, 50);
			this->Placelabel->Name = L"Placelabel";
			this->Placelabel->Size = System::Drawing::Size(215, 32);
			this->Placelabel->TabIndex = 3;
			this->Placelabel->Text = L"Расставьте корабли";
			this->Placelabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->Placelabel->Visible = false;
			// 
			// player1Fieldlabel
			// 
			this->player1Fieldlabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->player1Fieldlabel->BackColor = System::Drawing::Color::White;
			this->player1Fieldlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->player1Fieldlabel->Location = System::Drawing::Point(128, 43);
			this->player1Fieldlabel->Name = L"player1Fieldlabel";
			this->player1Fieldlabel->Size = System::Drawing::Size(212, 33);
			this->player1Fieldlabel->TabIndex = 4;
			this->player1Fieldlabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// player2Fieldlabel
			// 
			this->player2Fieldlabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->player2Fieldlabel->BackColor = System::Drawing::Color::White;
			this->player2Fieldlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->player2Fieldlabel->Location = System::Drawing::Point(508, 43);
			this->player2Fieldlabel->Name = L"player2Fieldlabel";
			this->player2Fieldlabel->Size = System::Drawing::Size(212, 33);
			this->player2Fieldlabel->TabIndex = 5;
			this->player2Fieldlabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Countlabel
			// 
			this->Countlabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Countlabel->BackColor = System::Drawing::Color::White;
			this->Countlabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Countlabel->Location = System::Drawing::Point(820, 442);
			this->Countlabel->Name = L"Countlabel";
			this->Countlabel->Size = System::Drawing::Size(208, 95);
			this->Countlabel->TabIndex = 6;
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->CreatePrompt = true;
			this->saveFileDialog->Filter = L"Bin files (.bin) | *.bin";
			this->saveFileDialog->InitialDirectory = L"C:";
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"Bin files (.bin) | *.bin";
			this->openFileDialog->InitialDirectory = L"C:";
			// 
			// Clearbutton
			// 
			this->Clearbutton->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Clearbutton->BackColor = System::Drawing::Color::White;
			this->Clearbutton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Clearbutton->Location = System::Drawing::Point(820, 391);
			this->Clearbutton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Clearbutton->Name = L"Clearbutton";
			this->Clearbutton->Size = System::Drawing::Size(208, 38);
			this->Clearbutton->TabIndex = 7;
			this->Clearbutton->Text = L"Очистить поле";
			this->Clearbutton->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->Clearbutton->UseVisualStyleBackColor = false;
			this->Clearbutton->Visible = false;
			this->Clearbutton->Click += gcnew System::EventHandler(this, &SeaBattle::Clearbutton_Click);
			// 
			// SeaBattle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1085, 661);
			this->Controls->Add(this->Clearbutton);
			this->Controls->Add(this->Countlabel);
			this->Controls->Add(this->player2Fieldlabel);
			this->Controls->Add(this->player1Fieldlabel);
			this->Controls->Add(this->Placelabel);
			this->Controls->Add(this->orientation_button);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MaximumSize = System::Drawing::Size(1103, 708);
			this->MinimumSize = System::Drawing::Size(1103, 708);
			this->Name = L"SeaBattle";
			this->Text = L"Морской бой";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: void DrawFields(Graphics^ g); //метод отрисовки игровых полей

	private: void DrawComponentsPVE(); //метод отрисовки элементов в режиме игрок против пк

	private: void DrawComponentsPVP(); //метод отрисовки элементов в режиме игрок против игрока

	private: void DrawPlacementShips(Graphics^ g); //метод отрисовки кораблей при ручной расстановке

	private: void DrawRemainingShips(Graphics^ g); //метод отрисовки количества оставшихся у игроков кораблей

	private: void PlaceShip(MouseEventArgs^ e); //метод реализации ручной расстановки корабля

	private: void UserClick(MouseEventArgs^ e); //метод обработки клика мышкой

	//отрисовка всех элементов игры
	private: System::Void pictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

		Graphics^ g = e->Graphics;
		if (gameMode == 1)
		{
			DrawFields(g);
			if (!rasstanovka)
				DrawRemainingShips(g);
			DrawPlacementShips(g);
		}
		if (gameMode == 2)
		{
			DrawFields(g);
			DrawRemainingShips(g);
		}
	}

		   //обработка нажатия на форму
	private: System::Void pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if(e->Clicks == 1 && e->Button == System::Windows::Forms::MouseButtons::Left)
			this->UserClick(e);
	}

		   //обработчик таймера
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		//проверка завершения игры
		if (game->IsEndGame() == 1)
		{
			timer->Stop();
			if (gameMode == 1)
				MessageBox::Show("Поздравляем! Вы победили!", "Победа", MessageBoxButtons::OK, MessageBoxIcon::Information);
			if (gameMode == 2)
				MessageBox::Show("Игрок 1 победил! Подравляем!", "Победа", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		if (game->IsEndGame() == 2)
		{
			timer->Stop();
			if (gameMode == 1)
				MessageBox::Show("К сожалению, Вы проиграли!", "Поражение", MessageBoxButtons::OK, MessageBoxIcon::Information);
			if (gameMode == 2)
				MessageBox::Show("Игрок 2 победил! Подравляем!", "Победа", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		if (rasstanovka)
			this->SaveMenuItem->Enabled = false;
		else
			this->SaveMenuItem->Enabled = true;
		if (gameMode == 1)
			DrawComponentsPVE();
		if (gameMode == 2)
			DrawComponentsPVP();

		this->pictureBox->Refresh();
	}

		   //выбор меню авторасстановка в игре против пк
	private: System::Void AutoPlacementMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 1;
		gamePVE = gcnew GamePVE();
		game = gamePVE;
		rasstanovka = 0;
		timer->Start();
		game->Start(rasstanovka);
	}

		   //выбор меню ручная расстановка в игре против пк
	private: System::Void UserPlacementMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 1;
		gamePVE = gcnew GamePVE();
		game = gamePVE;
		rasstanovka = 1;
		vert = 1;
		s4 = 1;
		s3 = 2;
		s2 = 3;
		s1 = 4;
		timer->Start();
		game->Start(rasstanovka);
	}

		   //выбор меню режим игрок против игрока
	private: System::Void PVPMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 2;
		gamePVP = gcnew GamePVP();
		game = gamePVP;
		timer->Start();
		game->Start(0);
	}

		   //выбор меню сохранить игру
	private: System::Void SaveMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			if (saveFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
			{
				String^ filename = saveFileDialog->FileName;
				FileStream^ fs = File::Create(filename);
				BinaryFormatter^ bf = gcnew BinaryFormatter();
				bf->Serialize(fs, game);
				fs->Close();
				saveFileDialog->FileName = "";
			}
		}
		catch (...)
		{
			MessageBox::Show("Возникла ошибка при сохранении игры!", "Ошибка сохранения", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

		   //выбор меню загрузить игру
	private: System::Void LoadMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			if (openFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
			{
				String^ filename = openFileDialog->FileName;
				FileStream^ fs = File::OpenRead(filename);
				BinaryFormatter^ bf = gcnew BinaryFormatter();
				game = (Game^)(bf->Deserialize(fs));
				if (dynamic_cast<GamePVE^>(game))
					gameMode = 1;
				if (dynamic_cast<GamePVP^>(game))
					gameMode = 2;
				fs->Close();
				openFileDialog->FileName = "";
				timer->Start();
				rasstanovka = 0;
			}
		}
		catch (...)
		{
			MessageBox::Show("Возникла ошибка при загрузке игры!", "Ошибка загрузки", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

		   //нажатие на кнопку очистить поле
	private: System::Void Clearbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		s4 = 1;
		s3 = 2;
		s2 = 3;
		s1 = 4;
		this->game->ClearFirstPlayerField();
	}

		   //нажатие на кнопку повернуть корабли
	private: System::Void orientation_button_Click(System::Object^ sender, System::EventArgs^ e) {
		vert = !vert;
	}

		   //Справка 
private: System::Void SpravkaMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Добро пожаловать в \"Морской бой\"!\n\nПравила игры:\nГлавной целью игры является уничтожение всех кораблей на поле противника.\
 Используйте левую кнопку мыши, чтобы совершить выстрел по выбранной ячейке. Если в ячейке отобразится желтый крестик - вы попали по палубе корабля\
противника и можете повторить ход.Если вы промахнулись, в ячейке отобразится синяя точка и ход перейдет сопернику. Побеждает тот, кто первым уничтожит все корабли противника.\
\n\nДля начала игры выберите в меню \"Играть\" один из доступных вариантов:\n1. Игрок против компьютера с авторасстановкой. Корабли на вашем поле будут расставлены\
 автоматически случайным способом.\n2. Игрок против компьютера с ручной расстановкой. Справа от игровых полей отобразятся корабли, которые вам необходимо расставить:\
 1 четырехпалубный, 2 трехпалубных, 3 двухпалубных, 4 однопалубных. Выберите левой кнопкой мыши корабль, который хотите раместить, затем разместите его на вашем\
 поле повторным кликом мыши. Размещать корабли за границей поля, или так, чтобы корабли касались друг друга нельзя! Как только вы разместите весь флот, стартует игра.\n\
3. Игрок против игрока. Этот режим предназначен для двух игроков. Корабли на обоих полях будут расставлены автоматически. Игроки поочередно совершают выстрелы по\
 полю противника. Имя атакующего игрока выделено зеленым цветом.\n\nВы можете сохранить ход любой игры, воспользовавшись меню \"Сохранить игру\", а затем\
 загрузить ее и продолжить играть с помощью меню \"Загрузить игру\".", "Справка");
}

	   //об авторе
private: System::Void AuthorMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Разработчик:\nСтудент группы ПИ-11 Тюкавкин И.А.\nАлтГТУ им. И.И. Ползунова\nБарнаул, 2022", "Автор");
}
};
}



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
	/// —водка дл€ SeaBattle
	/// </summary>
	public ref class SeaBattle : public System::Windows::Forms::Form
	{
	private:
		int DXY = 60, H = 30;
		Drawing::Rectangle R4, R3, R2, R1;
		Game^ game;
		Image ^wound, ^kill, ^deck, ^miss;
	private: System::Windows::Forms::PictureBox^ pictureBox;

	private: System::Windows::Forms::Timer^ timer;
	public:
		SeaBattle(void)
		{
			System::ComponentModel::ComponentResourceManager^ resourses = gcnew System::ComponentModel::ComponentResourceManager(SeaBattle::typeid);
			InitializeComponent();
			game = gcnew Game();
			game->PlayerField.FullAutoPlacement();
			game->compField.FullAutoPlacement();
			timer->Start();
			try {
				deck = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("deck"));
				kill = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("kill"));
				wound = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("wound"));
				miss = cli::safe_cast<System::Drawing::Image^>(resourses->GetObject("miss"));
			}
			catch (...)
			{
			}
		}
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
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
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// timer
			// 
			this->timer->Interval = 1;
			this->timer->Tick += gcnew System::EventHandler(this, &SeaBattle::timer_Tick);
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(0, -1);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1100, 600);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SeaBattle::pictureBox_Paint);
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &SeaBattle::pictureBox_MouseClick);
			// 
			// SeaBattle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1082, 553);
			this->Controls->Add(this->pictureBox);
			this->Name = L"SeaBattle";
			this->Text = L"SeaBattle";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void DrawFields(Graphics^ g);

	private: void DrawShips(Graphics^ g);
	

private: System::Void pictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;
	g->Clear(Color::White);
	DrawFields(g);
	DrawShips(g);
}

private: System::Void pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	int i, j;
	if (e->Button == System::Windows::Forms::MouseButtons::Left && e->Clicks == 1)
	{
		int MX = e->X;
		int MY = e->Y;
		if (MX > DXY + 13 * H && MY > DXY && MX < DXY + 23 * H && MY < DXY + 10 * H && game->IsEndGame() == 0) {
			i = (MX - (DXY + 13 * H)) / H;
			j = (MY - DXY) / H;
			if (game->compField.GetValue(i, j) >= -1 && game->compField.GetValue(i, j) <= 4) {
				game->PlayerMove(i, j);
			}

		}
	}
}

private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
	this->pictureBox->Invalidate();
}
};
}

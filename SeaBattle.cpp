#include "SeaBattle.h"

namespace CourseWork
{
	//метод отрисовки игровых полей
	void SeaBattle::DrawFields(Graphics^ g)
	{
		//отрисовка границ полей
		Pen^ pen = gcnew Pen(Color::Black, 2);
		Drawing::Font^ font = gcnew Drawing::Font("Segoe UI", 11, FontStyle::Bold);
		field1 = Rectangle(DXY, DXY, 10 * H, 10 * H);
		field2 = Rectangle(DXY + 13 * H, DXY, 10 * H, 10 * H);
		g->FillRectangle(gcnew SolidBrush(Color::White), field1);
		g->FillRectangle(gcnew SolidBrush(Color::White), field2);
		g->DrawRectangle(pen, field1);
		g->DrawRectangle(pen, field2);

		//отрисовка линий
		for (int i = DXY; i <= DXY + 10 * H; i += H)
		{
			g->DrawLine(Pens::Gray, DXY, i, DXY + 10 * H, i);
			g->DrawLine(Pens::Gray, i, DXY, i, DXY + 10 * H);
			g->DrawLine(Pens::Gray, DXY + 13 * H, i, DXY + 23 * H, i);
			g->DrawLine(Pens::Gray, i + 13 * H, DXY, i + 13 * H, DXY + 10 * H);
		}

		//отрисовка нумерации строк и столбцов
		for (int i = 0; i < 10; i++)
		{
			g->DrawString(symbols[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY + i * H + H / 5, DXY - H);
			g->DrawString(symbols[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY + 13 * H + i * H + H / 4, DXY - H);
			g->DrawString(numbers[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY - H - 6, DXY + i * H);
			g->DrawString(numbers[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY + 12 * H - 6, DXY + i * H);
		}

		//отрисовка ячеек полей на основании массивов
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (gameMode == 1 && game->FirstPlayerValue(i, j) >= 1 && game->FirstPlayerValue(i, j) <= 4)
					g->DrawImage(deck, DXY + H * i, DXY + H * j, H, H);
				if (game->FirstPlayerValue(i, j) >= 8 && game->FirstPlayerValue(i, j) <= 11)
					g->DrawImage(wound, DXY + H * i, DXY + H * j, H, H);
				if (game->FirstPlayerValue(i, j) >= 15 && game->FirstPlayerValue(i, j) <= 18)
					g->DrawImage(kill, DXY + H * i, DXY + H * j, H, H);
				if (game->FirstPlayerValue(i, j) == -2 || game->FirstPlayerValue(i, j) >= 5 && game->FirstPlayerValue(i, j) <= 7)
					g->DrawImage(miss, DXY + H * i, DXY + H * j, H, H);

				if (game->SecondPlayerValue(i, j) >= 8 && game->SecondPlayerValue(i, j) <= 11)
					g->DrawImage(wound, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->SecondPlayerValue(i, j) >= 15 && game->SecondPlayerValue(i, j) <= 18)
					g->DrawImage(kill, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->SecondPlayerValue(i, j) >= 5 && game->SecondPlayerValue(i, j) <= 7 || game->SecondPlayerValue(i, j) == -2)
					g->DrawImage(miss, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->IsEndGame() != 0 && game->SecondPlayerValue(i, j) >= 1 && game->SecondPlayerValue(i, j) <= 4)
					g->DrawImage(deck, DXY + 13 * H + H * i, DXY + H * j, H, H);
			}
	}

	//метод отрисовки элементов в режиме игрок против пк
	void SeaBattle::DrawComponentsPVE()
	{
		player1Fieldlabel->ForeColor = Color::Black;
		player2Fieldlabel->ForeColor = Color::Black;
		player1Fieldlabel->Text = "Игрок";
		player2Fieldlabel->Text = "Компьютер";
		player1Fieldlabel->Visible = true;
		player2Fieldlabel->Visible = true;
		if (!rasstanovka)
		{
			this->Countlabel->Visible = true;
			this->Countlabel->Text = "      Ходов сделано\nИгрок: " + Convert::ToString(game->GetFirstPlayerCount()) + "\nКомпьютер: " + Convert::ToString(game->GetSecondPlayerCount());
		}
		else
			this->Countlabel->Visible = false;
	}

	//метод отрисовки элементов в режиме игрок против игрока
	void SeaBattle::DrawComponentsPVP()
	{
		if (game->IsFirstPlayerMove())
		{
			this->player1Fieldlabel->ForeColor = Color::Green;
			this->player2Fieldlabel->ForeColor = Color::Black;
		}
		else
		{
			this->player1Fieldlabel->ForeColor = Color::Black;
			this->player2Fieldlabel->ForeColor = Color::Green;
		}
		player1Fieldlabel->Text = "Игрок 1";
		player2Fieldlabel->Text = "Игрок 2";
		this->Countlabel->Text = "      Ходов сделано\nИгрок 1: " + Convert::ToString(game->GetFirstPlayerCount()) + "\nИгрок 2: " + Convert::ToString(game->GetSecondPlayerCount());
		player1Fieldlabel->Visible = true;
		player2Fieldlabel->Visible = true;
		Countlabel->Visible = true;
	}

	//метод отрисовки кораблей при ручной расстановке
	void SeaBattle::DrawPlacementShips(Graphics^ g)
	{
		if (rasstanovka)
		{
			Placelabel->Visible = true;
			orientation_button->Visible = true;
			Clearbutton->Visible = true;
			SolidBrush^ brush = gcnew SolidBrush(Color::White);
			Pen^ pen = gcnew Pen(Color::Black, 2);
			Pen^ selectPen = gcnew Pen(Color::Green, 4);
			if (vert)
			{
				ship4 = Rectangle(DXY + 24 * H, DXY, 4 * H, H);
				ship3 = Rectangle(DXY + 24 * H, DXY + 2 * H, 3 * H, H);
				ship2 = Rectangle(DXY + 24 * H, DXY + 4 * H, 2 * H, H);
				ship1 = Rectangle(DXY + 24 * H, DXY + 6 * H, 1 * H, H);
			}
			else
			{
				ship4 = Rectangle(DXY + 24 * H, DXY, H, 4 * H);
				ship3 = Rectangle(DXY + 26 * H, DXY, H, 3 * H);
				ship2 = Rectangle(DXY + 28 * H, DXY, H, 2 * H);
				ship1 = Rectangle(DXY + 30 * H, DXY, H, 1 * H);
			}
			if (s4 != 0)
			{
				g->FillRectangle(brush, ship4);
				if (selectS4)
					g->DrawRectangle(selectPen, ship4);
				else
					g->DrawRectangle(pen, ship4);
			}
			if (s3 != 0)
			{
				g->FillRectangle(brush, ship3);
				if (selectS3)
					g->DrawRectangle(selectPen, ship3);
				else
					g->DrawRectangle(pen, ship3);
			}
			if (s2 != 0)
			{
				g->FillRectangle(brush, ship2);
				if (selectS2)
					g->DrawRectangle(selectPen, ship2);
				else
					g->DrawRectangle(pen, ship2);
			}
			if (s1 != 0)
			{
				g->FillRectangle(brush, ship1);
				if (selectS1)
					g->DrawRectangle(selectPen, ship1);
				else
					g->DrawRectangle(pen, ship1);
			}

			if (s1 + s2 + s3 + s4 == 0)
				rasstanovka = 0;
		}
		else
		{
			Placelabel->Visible = false;
			orientation_button->Visible = false;
			Clearbutton->Visible = false;
		}
	}

	//метод отрисовки количества оставшихся у игроков кораблей
	void SeaBattle::DrawRemainingShips(Graphics^ g)
	{
		Pen^ pen = gcnew Pen(Color::Black, 2);
		SolidBrush^ brush = gcnew SolidBrush(Color::White);
		Drawing::Font^ font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
		g->FillRectangle(brush, DXY, DXY + 11 * H, 4 * H, H);
		g->FillRectangle(brush, DXY, DXY + 12 * H + 10, 3 * H, H);
		g->FillRectangle(brush, DXY, DXY + 13 * H + 20, 2 * H, H);
		g->FillRectangle(brush, DXY, DXY + 14 * H + 30, H, H);
		g->DrawRectangle(pen, DXY, DXY + 11 * H, 4 * H, H);
		g->DrawRectangle(pen, DXY, DXY + 12 * H + 10, 3 * H, H);
		g->DrawRectangle(pen, DXY, DXY + 13 * H + 20, 2 * H, H);
		g->DrawRectangle(pen, DXY, DXY + 14 * H + 30, H, H);
		cli::array<int>^ playerCount = game->GetFirstPlayerKillCount();
		g->DrawEllipse(pen, DXY + 4 * H + H / 2, DXY + 11 * H, H, H);
		g->FillEllipse(brush, DXY + 4 * H + H / 2, DXY + 11 * H, H, H);
		g->DrawString(Convert::ToString(1 - playerCount[0]), font, gcnew SolidBrush(Color::Green), DXY + 4 * H + 20, DXY + 11 * H - 2);
		g->DrawEllipse(pen, DXY + 3 * H + H / 2, DXY + 12 * H + 10, H, H);
		g->FillEllipse(brush, DXY + 3 * H + H / 2, DXY + 12 * H + 10, H, H);
		g->DrawString(Convert::ToString(2 - playerCount[1]), font, gcnew SolidBrush(Color::Green), DXY + 3 * H + 20, DXY + 12 * H + 8);
		g->DrawEllipse(pen, DXY + 2 * H + H / 2, DXY + 13 * H + 20, H, H);
		g->FillEllipse(brush, DXY + 2 * H + H / 2, DXY + 13 * H + 20, H, H);
		g->DrawString(Convert::ToString(3 - playerCount[2]), font, gcnew SolidBrush(Color::Green), DXY + 2 * H + 20, DXY + 13 * H + 18);
		g->DrawEllipse(pen, DXY + H + H / 2, DXY + 14 * H + 30, H, H);
		g->FillEllipse(brush, DXY + H + H / 2, DXY + 14 * H + 30, H, H);
		g->DrawString(Convert::ToString(4 - playerCount[3]), font, gcnew SolidBrush(Color::Green), DXY + H + 20, DXY + 14 * H + 28);

		g->FillRectangle(brush, DXY + 13 * H, DXY + 11 * H, 4 * H, H);
		g->FillRectangle(brush, DXY + 13 * H, DXY + 12 * H + 10, 3 * H, H);
		g->FillRectangle(brush, DXY + 13 * H, DXY + 13 * H + 20, 2 * H, H);
		g->FillRectangle(brush, DXY + 13 * H, DXY + 14 * H + 30, H, H);
		g->DrawRectangle(pen, DXY + 13 * H, DXY + 11 * H, 4 * H, H);
		g->DrawRectangle(pen, DXY + 13 * H, DXY + 12 * H + 10, 3 * H, H);
		g->DrawRectangle(pen, DXY + 13 * H, DXY + 13 * H + 20, 2 * H, H);
		g->DrawRectangle(pen, DXY + 13 * H, DXY + 14 * H + 30, H, H);
		cli::array<int>^ compCount = game->GetSecondPlayerKillCount();
		g->DrawEllipse(pen, DXY + 17 * H + H / 2, DXY + 11 * H, H, H);
		g->FillEllipse(brush, DXY + 17 * H + H / 2, DXY + 11 * H, H, H);
		g->DrawString(Convert::ToString(1 - compCount[0]), font, gcnew SolidBrush(Color::Red), DXY + 17 * H + 20, DXY + 11 * H - 2);
		g->DrawEllipse(pen, DXY + 16 * H + H / 2, DXY + 12 * H + 10, H, H);
		g->FillEllipse(brush, DXY + 16 * H + H / 2, DXY + 12 * H + 10, H, H);
		g->DrawString(Convert::ToString(2 - compCount[1]), font, gcnew SolidBrush(Color::Red), DXY + 16 * H + 20, DXY + 12 * H + 8);
		g->DrawEllipse(pen, DXY + 15 * H + H / 2, DXY + 13 * H + 20, H, H);
		g->FillEllipse(brush, DXY + 15 * H + H / 2, DXY + 13 * H + 20, H, H);
		g->DrawString(Convert::ToString(3 - compCount[2]), font, gcnew SolidBrush(Color::Red), DXY + 15 * H + 20, DXY + 13 * H + 18);
		g->DrawEllipse(pen, DXY + 14 * H + H / 2, DXY + 14 * H + 30, H, H);
		g->FillEllipse(brush, DXY + 14 * H + H / 2, DXY + 14 * H + 30, H, H);
		g->DrawString(Convert::ToString(4 - compCount[3]), font, gcnew SolidBrush(Color::Red), DXY + 14 * H + 20, DXY + 14 * H + 28);
	}

	//метод реализации ручной расстановки корабля
	void SeaBattle::PlaceShip(MouseEventArgs^ e)
	{
		if (ship4.Contains(e->Location))
		{
			selectS4 = 1;
			selectS3 = 0;
			selectS2 = 0;
			selectS1 = 0;
		}
		if (ship3.Contains(e->Location))
		{
			selectS4 = 0;
			selectS3 = 1;
			selectS2 = 0;
			selectS1 = 0;
		}
		if (ship2.Contains(e->Location))
		{
			selectS4 = 0;
			selectS3 = 0;
			selectS2 = 1;
			selectS1 = 0;
		}
		if (ship1.Contains(e->Location))
		{
			selectS4 = 0;
			selectS3 = 0;
			selectS2 = 0;
			selectS1 = 1;
		}

		if (field1.Contains(e->Location))
		{
			int mX = e->X;
			int mY = e->Y;
			int i = (mX - (DXY)) / H;
			int j = (mY - DXY) / H;
			if (s4 != 0 && selectS4)
			{
				selectS4 = 0;
				if (game->FirstPlayerPlacement(i, j, 4, vert))
					s4--;
			}
			if (s3 != 0 && selectS3)
			{
				selectS3 = 0;
				if (game->FirstPlayerPlacement(i, j, 3, vert))
					s3--;
			}
			if (s2 != 0 && selectS2)
			{
				selectS2 = 0;
				if (game->FirstPlayerPlacement(i, j, 2, vert))
					s2--;
			}
			if (s1 != 0 && selectS1)
			{
				selectS1 = 0;
				if (game->FirstPlayerPlacement(i, j, 1, vert))
					s1--;
			}
		}
	}

	//метод обработки клика мышкой
	void SeaBattle::UserClick(MouseEventArgs^ e)
	{
		switch (gameMode)
		{
		case 1:
			if (game->IsEndGame() == 0 && !rasstanovka && game->IsFirstPlayerMove())
			{
				if (field2.Contains(e->Location))
				{
					int mX = e->X;
					int mY = e->Y;
					int i = (mX - (DXY + 13 * H)) / H;
					int j = (mY - DXY) / H;
					if (game->SecondPlayerValue(i, j) >= -1 && game->SecondPlayerValue(i, j) <= 4) {
						game->PlayerMove(i, j);
					}
				}
			}
			if (rasstanovka)
				PlaceShip(e);
			break;
		case 2:
			if (game->IsEndGame() == 0 && game->IsFirstPlayerMove() && field2.Contains(e->Location))
			{
				int mX = e->X;
				int mY = e->Y;
				int i = (mX - (DXY + 13 * H)) / H;
				int j = (mY - DXY) / H;
				game->PlayerMove(i, j);
			}
			if (game->IsEndGame() == 0 && game->IsSecondPlayerMove() && field1.Contains(e->Location))
			{
				int mX = e->X;
				int mY = e->Y;
				int i = (mX - DXY) / H;
				int j = (mY - DXY) / H;
				game->PlayerMove(i, j);
			}
			break;
		}
	}

	//отрисовка всех элементов игры
	System::Void SeaBattle::pictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

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
	System::Void SeaBattle::pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Clicks == 1 && e->Button == System::Windows::Forms::MouseButtons::Left)
			this->UserClick(e);
	}

	//обработчик таймера
	System::Void SeaBattle::timer_Tick(System::Object^ sender, System::EventArgs^ e) {
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
	System::Void SeaBattle::AutoPlacementMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 1;
		gamePVE = gcnew GamePVE();
		game = gamePVE;
		rasstanovka = 0;
		timer->Start();
		game->Start(rasstanovka);
	}

	//выбор меню ручная расстановка в игре против пк
	System::Void SeaBattle::UserPlacementMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
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
	System::Void SeaBattle::PVPMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		Placelabel->Visible = false;
		orientation_button->Visible = false;
		Clearbutton->Visible = false;
		gameMode = 2;
		gamePVP = gcnew GamePVP();
		game = gamePVP;
		timer->Start();
		game->Start(0);
	}

	//выбор меню сохранить игру
	System::Void SeaBattle::SaveMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
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
	System::Void SeaBattle::LoadMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
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
	System::Void SeaBattle::Clearbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		s4 = 1;
		s3 = 2;
		s2 = 3;
		s1 = 4;
		this->game->ClearFirstPlayerField();
	}

	//Справка 
	System::Void SeaBattle::SpravkaMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("Добро пожаловать в \"Морской бой\"!\n\nПравила игры:\nГлавной целью игры является уничтожение всех кораблей на поле противника.\
 Используйте левую кнопку мыши, чтобы совершить выстрел по выбранной ячейке. Если в ячейке отобразится желтый крестик - вы попали по палубе корабля\
 противника и можете повторить ход. Если вы промахнулись, в ячейке отобразится синяя точка и ход перейдет сопернику. Побеждает тот, кто первым уничтожит все корабли противника.\
\n\nДля начала игры выберите в меню \"Играть\" один из доступных вариантов:\n1. Игрок против компьютера с авторасстановкой. Корабли на вашем поле будут расставлены\
 автоматически случайным способом.\n2. Игрок против компьютера с ручной расстановкой. Справа от игровых полей отобразятся корабли, которые вам необходимо расставить:\
 1 четырехпалубный, 2 трехпалубных, 3 двухпалубных, 4 однопалубных. Выберите левой кнопкой мыши корабль, который хотите раместить, затем разместите его на вашем\
 поле повторным кликом мыши. Размещать корабли за границей поля, или так, чтобы корабли касались друг друга, нельзя! Как только вы разместите весь флот, стартует игра.\n\
3. Игрок против игрока. Этот режим предназначен для двух игроков. Корабли на обоих полях будут расставлены автоматически. Игроки поочередно совершают выстрелы по\
 полю противника. Имя атакующего игрока выделено зеленым цветом.\n\nВы можете сохранить ход любой игры, воспользовавшись меню \"Сохранить игру\", а затем\
 загрузить ее и продолжить играть с помощью меню \"Загрузить игру\".", "Справка");
	}

	//об авторе
	System::Void SeaBattle::AuthorMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("Разработчик:\nСтудент группы ПИ-11 Тюкавкин И.А.\nАлтГТУ им. И.И. Ползунова\nБарнаул, 2022", "Автор");
	}

}


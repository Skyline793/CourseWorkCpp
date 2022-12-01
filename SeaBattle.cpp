#include "SeaBattle.h"

namespace CourseWork
{
	void SeaBattle::DrawFields(Graphics^ g)
	{
		Pen^ pen = gcnew Pen(Color::Black, 2);
		field1 = Rectangle(DXY, DXY, 10 * H, 10 * H);
		Drawing::Font^ font = gcnew Drawing::Font("Segoe UI", 11, FontStyle::Bold);
		field2 = Rectangle(DXY + 13 * H, DXY, 10 * H, 10 * H);
		g->FillRectangle(gcnew SolidBrush(Color::White), field1);
		g->FillRectangle(gcnew SolidBrush(Color::White), field2);
		g->DrawRectangle(pen, field1);
		g->DrawRectangle(pen, field2);

		for (int i = DXY; i <= DXY + 10 * H; i += H)
		{
			g->DrawLine(Pens::Gray, DXY, i, DXY + 10 * H, i);
			g->DrawLine(Pens::Gray, i, DXY, i, DXY + 10 * H);
			g->DrawLine(Pens::Gray, DXY + 13 * H, i, DXY + 23 * H, i);
			g->DrawLine(Pens::Gray, i + 13 * H, DXY, i + 13 * H, DXY + 10 * H);
		}

		for (int i = 0; i < 10; i++)
		{
			g->DrawString(symbols[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY + i * H + H / 5, DXY - H);
			g->DrawString(symbols[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY + 13 * H + i * H + H / 4, DXY - H);
			g->DrawString(numbers[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY - H - 6, DXY + i * H);
			g->DrawString(numbers[i], font, gcnew Drawing::SolidBrush(Color::Black), DXY + 12 * H - 6, DXY + i * H);
		}
		if (!rasstanovka) 
		{
			this->Countlabel->Visible = true;
			this->Countlabel->Text = "      Ходов сделано\nИгрок: " + Convert::ToString(game->GetPlayerCount()) + "\nКомпьютер: " + Convert::ToString(game->GetCompCount());
		}
		else
			this->Countlabel->Visible = false;
	}

	void SeaBattle::DrawShips(Graphics^ g)
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				if (game->PlayerValue(i, j) >= 1 && game->PlayerValue(i, j) <= 4)
					g->DrawImage(deck, DXY + H * i, DXY + H * j, H, H);
				if (game->PlayerValue(i, j) >= 8 && game->PlayerValue(i, j) <= 11)
					g->DrawImage(wound, DXY + H * i, DXY + H * j, H, H);
				if (game->PlayerValue(i, j) >= 15 && game->PlayerValue(i, j) <= 18)
					g->DrawImage(kill, DXY + H * i, DXY + H * j, H, H);
				if (game->PlayerValue(i, j) == -2 || game->PlayerValue(i, j) >= 5 && game->PlayerValue(i, j) <= 7)
					g->DrawImage(miss, DXY + H * i, DXY + H * j, H, H);

				if (game->CompValue(i, j) >= 8 && game->CompValue(i, j) <= 11)
					g->DrawImage(wound, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->CompValue(i, j) >= 15 && game->CompValue(i, j) <= 18)
					g->DrawImage(kill, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->CompValue(i, j) >= 5 && game->CompValue(i, j) <= 7 || game->CompValue(i, j) == -2)
					g->DrawImage(miss, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->IsEndGame() != 0 && game->CompValue(i, j) >= 1 && game->CompValue(i, j) <= 4)
					g->DrawImage(deck, DXY + 13 * H + H * i, DXY + H * j, H, H);
			}
	}
	void SeaBattle::DrawPlacementShips(Graphics^ g)
	{
		if (rasstanovka)
		{
			Placelabel->Visible = true;
			orientation_button->Visible = true;
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

		}

	}
	void SeaBattle::SelectShip(MouseEventArgs^ e)
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
	}
	void SeaBattle::PlaceShip(MouseEventArgs^ e)
	{
		if (field1.Contains(e->Location))
		{
			int mX = e->X;
			int mY = e->Y;
			int i = (mX - (DXY)) / H;
			int j = (mY - DXY) / H;
			if (s4 != 0 && selectS4)
			{
				selectS4 = 0;
				if (game->PlayerPlacement(i, j, 4, vert))
					s4--;
			}
			if (s3 != 0 && selectS3)
			{
				selectS3 = 0;
				if (game->PlayerPlacement(i, j, 3, vert))
					s3--;
			}
			if (s2 != 0 && selectS2)
			{
				selectS2 = 0;
				if (game->PlayerPlacement(i, j, 2, vert))
					s2--;
			}
			if (s1 != 0 && selectS1)
			{
				selectS1 = 0;
				if (game->PlayerPlacement(i, j, 1, vert))
					s1--;
			}
		}
	}
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
		cli::array<int>^ playerCount = game->GetPlayerKillCount();
		g->DrawEllipse(pen, DXY + 4 * H + H / 2, DXY + 11 * H, H, H);
		g->FillEllipse(brush, DXY + 4 * H + H / 2, DXY + 11 * H, H, H);
		g->DrawString(Convert::ToString(1 - playerCount[0]), font, gcnew SolidBrush(Color::Green), DXY + 4 * H + 20, DXY + 11 * H-2);
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
		cli::array<int>^ compCount = game->GetCompKillCount();
		g->DrawEllipse(pen, DXY + 17 * H + H / 2, DXY + 11 * H, H, H);
		g->FillEllipse(brush, DXY + 17 * H + H / 2, DXY + 11 * H, H, H);
		g->DrawString(Convert::ToString(1 - compCount[0]), font, gcnew SolidBrush(Color::Red), DXY + 17 * H + 20, DXY + 11 * H-2);
		g->DrawEllipse(pen, DXY + 16 * H + H / 2, DXY + 12 * H+10, H, H);
		g->FillEllipse(brush, DXY + 16 * H + H / 2, DXY + 12 * H+10, H, H);
		g->DrawString(Convert::ToString(2 - compCount[1]), font, gcnew SolidBrush(Color::Red), DXY + 16 * H + 20, DXY + 12 * H+8);
		g->DrawEllipse(pen, DXY + 15 * H + H / 2, DXY + 13 * H+20, H, H);
		g->FillEllipse(brush, DXY + 15 * H + H / 2, DXY + 13 * H+20, H, H);
		g->DrawString(Convert::ToString(3 - compCount[2]), font, gcnew SolidBrush(Color::Red), DXY + 15 * H + 20, DXY + 13 * H+18);
		g->DrawEllipse(pen, DXY + 14 * H + H / 2, DXY + 14 * H+30, H, H);
		g->FillEllipse(brush, DXY + 14 * H + H / 2, DXY + 14 * H+30, H, H);
		g->DrawString(Convert::ToString(4 - compCount[3]), font, gcnew SolidBrush(Color::Red), DXY + 14 * H + 20, DXY + 14 * H+28);
	}
}

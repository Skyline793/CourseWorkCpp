#include "SeaBattle.h"

namespace CourseWork
{
	void SeaBattle::DrawFields(Graphics^ g)
	{
		Pen^ pen = gcnew Pen(Color::Black, 2);

		for (int i = DXY; i <= DXY + 10 * H; i += H)
		{
			g->DrawLine(Pens::Gray, DXY, i, DXY + 10 * H, i);
			g->DrawLine(Pens::Gray, i, DXY, i, DXY + 10 * H);
			g->DrawLine(Pens::Gray, DXY + 13 * H, i, DXY + 23 * H, i);
			g->DrawLine(Pens::Gray, i + 13 * H, DXY, i + 13 * H, DXY + 10 * H);
			g->DrawRectangle(pen, DXY, DXY, 10 * H, 10 * H);
			g->DrawRectangle(pen, DXY + 13 * H, DXY, 10 * H, 10 * H);
		}
	}

	void SeaBattle::DrawShips(Graphics^ g)
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				if (game->PlayerField.GetValue(i, j) >= 1 && game->PlayerField.GetValue(i, j) <= 4)
					g->DrawImage(deck, DXY + H * i, DXY + H * j, H, H);
				if (game->PlayerField.GetValue(i, j) >= 8 && game->PlayerField.GetValue(i, j) <= 11)
					g->DrawImage(wound, DXY + H * i, DXY + H * j, H, H);
				if (game->PlayerField.GetValue(i, j) >= 15 && game->PlayerField.GetValue(i, j) <= 18)
					g->DrawImage(kill, DXY + H * i, DXY + H * j, H, H);
				if (game->PlayerField.GetValue(i, j) == -2 || game->PlayerField.GetValue(i, j) >= 5 && game->PlayerField.GetValue(i, j) <= 7)
					g->DrawImage(miss, DXY + H * i, DXY + H * j, H, H);

				if (game->CompField.GetValue(i, j) >= 8 && game->CompField.GetValue(i, j) <= 11)
					g->DrawImage(wound, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->CompField.GetValue(i, j) >= 15 && game->CompField.GetValue(i, j) <= 18)
					g->DrawImage(kill, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->CompField.GetValue(i, j) >= 5 && game->CompField.GetValue(i, j) <= 7 || game->CompField.GetValue(i, j) == -2)
					g->DrawImage(miss, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->IsEndGame() != 0 && game->CompField.GetValue(i, j) >= 1 && game->CompField.GetValue(i, j) <= 4)
					g->DrawImage(deck, DXY + 13 * H + H * i, DXY + H * j, H, H);
			}
	}
	void SeaBattle::DrawPlacementShips(Graphics^ g)
	{
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
			if (selectS4)
				g->DrawRectangle(selectPen, ship4);
			else
				g->DrawRectangle(pen, ship4);
		}
		if (s3 != 0)
		{
			if (selectS3)
				g->DrawRectangle(selectPen, ship3);
			else
				g->DrawRectangle(pen, ship3);
		}
		if (s2 != 0)
		{
			if (selectS2)
				g->DrawRectangle(selectPen, ship2);
			else
				g->DrawRectangle(pen, ship2);
		}
		if (s1 != 0)
		{
			if (selectS1)
				g->DrawRectangle(selectPen, ship1);
			else
				g->DrawRectangle(pen, ship1);
		}

		if (s1 + s2 + s3 + s4 != 0)
		{
			Placelabel->Visible = true;
			orientation_button->Visible = true;
		}
		else
		{
			Placelabel->Visible = false;
			orientation_button->Visible = false;
			rasstanovka = 0;
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
		int mX = e->X;
		int mY = e->Y;
		int i = (mX - (DXY)) / H;
		int j = (mY - DXY) / H;
		if (i >= 0 && i < 10 && j >= 0 && j < 10)
		{
			if (s4 != 0 && selectS4)
			{
				selectS4 = 0;
				if (game->PlayerField.UserPlacement(i, j, 4, vert))
					s4--;
			}
			if (s3 != 0 && selectS3)
			{
				selectS3 = 0;
				if (game->PlayerField.UserPlacement(i, j, 3, vert))
					s3--;
			}
			if (s2 != 0 && selectS2)
			{
				selectS2 = 0;
				if (game->PlayerField.UserPlacement(i, j, 2, vert))
					s2--;
			}
			if (s1 != 0 && selectS1)
			{
				selectS1 = 0;
				if (game->PlayerField.UserPlacement(i, j, 1, vert))
					s1--;
			}
		}
	}
}

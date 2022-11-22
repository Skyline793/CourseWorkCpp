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

				if (game->compField.GetValue(i, j) >= 8 && game->compField.GetValue(i, j) <= 11)
					g->DrawImage(wound, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->compField.GetValue(i, j) >= 15 && game->compField.GetValue(i, j) <= 18)
					g->DrawImage(kill, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->compField.GetValue(i, j) >= 5 && game->compField.GetValue(i, j) <= 7 || game->compField.GetValue(i, j) == -2)
					g->DrawImage(miss, DXY + 13 * H + H * i, DXY + H * j, H, H);
				if (game->IsEndGame() != 0 && game->compField.GetValue(i, j) >= 1 && game->compField.GetValue(i, j) <= 4)
					g->DrawImage(deck, DXY + 13 * H + H * i, DXY + H * j, H, H);
			}
	}
}

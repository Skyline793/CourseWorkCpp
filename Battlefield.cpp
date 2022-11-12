#include "Battlefield.h"

Battlefield::Battlefield()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			field[i, j] = 0;
}

bool Battlefield::TestNewPaluba(int i, int j)
{
	try {
		if (field[i, j] == 0 || field[i, j] == -1) return 1;
		else return 0;
	}
	catch (IndexOutOfRangeException^ e) {
		return 0;
	}
}

void Battlefield::ShipAutoPlacement(int deckCount)
{
	srand(time(NULL));
	int i, j;
	int direction;
	bool flag = 0;
	while (true) {
		i = rand() % 10;
		j = rand() % 10;
		direction = rand() % 4; //0 вверх, 1 вправо, 2 вниз, 3 влево
		if (TestNewPaluba(i, j))
			switch (direction)
			{
			case 0:
				if (TestNewPaluba(i - deckCount, j))
					flag = 1;
				break;
			case 1:
				if (TestNewPaluba(i, j + deckCount))
					flag = 1;
				break;
			case 2:
				if (TestNewPaluba(i + deckCount, j))
					flag = 1;
				break;
			case 3:
				if (TestNewPaluba(i, j - deckCount))
					flag = 1;
				break;
			}
		if (flag) 
			break;
	}
	field[i, j] = deckCount;
	switch (direction)
	{
	case 0:
		for (int k = deckCount - 1; k >= 1; k--)
			field[i - k, j] = deckCount;
		break;
	case 1:
		for (int k = deckCount - 1; k >= 1; k--)
			field[i, j + k] = deckCount;
		break;
	case 2:
		for (int k = deckCount - 1; k >= 1; k--)
			field[i + k, j] = deckCount;
		break;
	case 3:
		for (int k = deckCount - 1; k >= 1; k--)
			field[i, j - k] = deckCount;
		break;
	}
}

void Battlefield::FullAutoPlacement()
{
	ShipAutoPlacement(4);
	for (int i = 1; i <=2; i++)
		ShipAutoPlacement(3);
	for (int i = 1; i <=3; i++)
		ShipAutoPlacement(2);
	for (int i = 1; i <=4; i++)
		ShipAutoPlacement(1);
}

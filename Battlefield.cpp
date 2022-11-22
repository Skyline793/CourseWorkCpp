#include "Battlefield.h"

Battlefield::Battlefield()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			field[i, j] = 0;
}

void Battlefield::Fire(int i, int j)
{
	field[i, j] += 7;
}

int Battlefield::GetValue(int i, int j)
{
	return field[i, j];
}

bool Battlefield::InField(int i, int j)
{
	if (i >= 0 && i < N && j >= 0 && j < N)
		return 1;
	else
		return 0;
}

void Battlefield::TestKilled(int i, int j)
{
	if (field[i, j] == 8) { //Если однопалубный
		field[i, j] += 7; //прибавляем к убитому +7
		SurroundKilledDeck(i, j);//Уменьшаем окружение убитого на 1
	}
	else if (field[i, j] == 9) {
		AnalizeKill(i, j, 2);
	}
	else if (field[i, j] == 10) {
		AnalizeKill(i, j, 3);
	}
	else if (field[i, j] == 11) {
		AnalizeKill(i, j, 4);
	}
}

void Battlefield::AnalizeKill(int i, int j, int deckCount)
{
	int woundCount = 0;
	for (int x = i - (deckCount - 1); x <= i + (deckCount - 1); x++)
		for (int y = j - (deckCount - 1); y <= j + (deckCount - 1); y++) 
		{
			if (InField(x, y) && field[x, y] == deckCount + 7)
				woundCount++;
		}
	if (woundCount == deckCount)
		for (int x = i - (deckCount - 1); x <= i + (deckCount - 1); x++)
			for (int y = j - (deckCount - 1); y <= j + (deckCount - 1); y++)
			{
				if (InField(x, y) && field[x, y] == deckCount + 7)
				{
					field[x, y] += 7;
					SurroundKilledDeck(x, y);
				}
					
			}
}

void Battlefield::SetSurroundingKilled(int i, int j)
{
	try
	{
		if (field[i, j] == -1 || field[i, j] == 6)
			field[i, j]--;
	}
	catch (...)
	{
	}
}

void Battlefield::SurroundKilledDeck(int i, int j)
{
	SetSurroundingKilled(i - 1, j - 1);
	SetSurroundingKilled(i - 1, j);
	SetSurroundingKilled(i - 1, j + 1);
	SetSurroundingKilled(i, j + 1);
	SetSurroundingKilled(i + 1, j + 1);
	SetSurroundingKilled(i + 1, j);
	SetSurroundingKilled(i + 1, j - 1);
	SetSurroundingKilled(i, j - 1);
}

bool Battlefield::TestNewPaluba(int i, int j)
{
	try {
		if (field[i, j] == 0 || field[i, j] == -2) return 1;
		else return 0;
	}
	catch (...) {
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
	SurroundPlacedDeck(i, j);
	switch (direction)
	{
	case 0:
		for (int k = deckCount - 1; k >= 1; k--) 
		{
			field[i - k, j] = deckCount;
			SurroundPlacedDeck(i - k, j);
		}
		break;
	case 1:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i, j + k] = deckCount;
			SurroundPlacedDeck(i, j + k);
		}
		break;
	case 2:
		for (int k = deckCount - 1; k >= 1; k--) 
		{
			field[i + k, j] = deckCount;
			SurroundPlacedDeck(i + k, j);
		}
		break;
	case 3:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i, j - k] = deckCount;
			SurroundPlacedDeck(i, j - k);
		}
		break;
	}
	FinishSurrounding();
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

void Battlefield::SetSurroundingPlaced(int i, int j)
{
	try {
		if (field[i, j] == 0)
			field[i, j] = -2;
	}
	catch (...)
	{
	}
}

void Battlefield::SurroundPlacedDeck(int i, int j)
{
	SetSurroundingPlaced(i - 1, j - 1);
	SetSurroundingPlaced(i - 1, j);
	SetSurroundingPlaced(i - 1, j + 1);
	SetSurroundingPlaced(i, j + 1);
	SetSurroundingPlaced(i + 1, j + 1);
	SetSurroundingPlaced(i + 1, j);
	SetSurroundingPlaced(i + 1, j - 1);
	SetSurroundingPlaced(i, j - 1);
}

void Battlefield::FinishSurrounding()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (field[i, j] == -2)
				field[i, j]++;
}

bool Battlefield::UserPlacement(int i, int j, int deckCount, int direction)
{
	bool flag = 0;
	if (TestNewPaluba(i, j))
	{
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
	}
	if (flag == 0) return 0;
	field[i, j] = deckCount;
	SurroundPlacedDeck(i, j);
	switch (direction)
	{
	case 0:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i - k, j] = deckCount;
			SurroundPlacedDeck(i - k, j);
		}
		break;
	case 1:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i, j + k] = deckCount;
			SurroundPlacedDeck(i, j + k);
		}
		break;
	case 2:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i + k, j] = deckCount;
			SurroundPlacedDeck(i + k, j);
		}
		break;
	case 3:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i, j - k] = deckCount;
			SurroundPlacedDeck(i, j - k);
		}
		break;
	}
	FinishSurrounding();
	return 1;
}

int Battlefield::SumKilled()
{
	int Sum = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (field[i, j] >= 15)
				Sum += field[i, j];
	return Sum;
}

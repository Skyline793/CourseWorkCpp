#include "Battlefield.h"

//конструктор
Battlefield::Battlefield()
{
	field = gcnew cli::array<int, 2>(10, 10);
}

/*метод симуляции выстрела по полю
@param i - номер строки 
@param j - номер столбца*/
void Battlefield::Fire(int i, int j)
{
	field[i, j] += 7;
}

/*метод получения значения ячейки поля
@param i - номер строки
@param j - номер столбца
@return значение ячейки*/
int Battlefield::GetValue(int i, int j)
{
	return field[i, j];
}

/*метод, проверяющий принадлежит ли ячейка с заданными координатами полю
@param i - номер строки
@param j - номер столбца
@return 1, если принадлежит, 0, если нет*/
bool Battlefield::InField(int i, int j)
{
	if (i >= 0 && i < 10 && j >= 0 && j < 10)
		return 1;
	else
		return 0;
}

/*метод, проверяющий уничтожение корабля
@param i - номер строки
@param j - номер столбца*/
void Battlefield::TestKilled(int i, int j)
{
	if (field[i, j] == 8)
	{
		field[i, j] += 7; 
		SurroundKilledDeck(i, j);
	}
	if (field[i, j] == 9)
		AnalizeKill(i, j, 2);
	if (field[i, j] == 10)
		AnalizeKill(i, j, 3);
	if (field[i, j] == 11)
		AnalizeKill(i, j, 4);
}

/*метод, анализирующий, убит ли корабль, координаты подбитой палубы которого передаются через параметры
@param i - номер строки
@param j - номер столбца*
@param deckCount - количество палуб корабля*/
void Battlefield::AnalizeKill(int i, int j, int deckCount)
{
	int woundCount = 0; //число подбитых палуб
	//считаем количество раненых палуб
	for (int x = i - (deckCount - 1); x <= i + (deckCount - 1); x++)
		for (int y = j - (deckCount - 1); y <= j + (deckCount - 1); y++)
		{
			if (InField(x, y))
				if (field[x, y] == deckCount + 7)
					woundCount++;
		}
	if (woundCount == deckCount) //если число подбитых палуб равно общему числу палуб
		//преобразуем корабль в убитый и изменяем окружение
		for (int x = i - (deckCount - 1); x <= i + (deckCount - 1); x++)
			for (int y = j - (deckCount - 1); y <= j + (deckCount - 1); y++)
			{
				if (InField(x, y))
					if (field[x, y] == deckCount + 7)
					{
						field[x, y] += 7;
						SurroundKilledDeck(x, y);
					}
			}
}

/*метод, уменьшающий окружение убитой палубы на 1 с помощью метода SetSurroundingKilled
@param i - номер строки
@param j - номер столбца*/
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

/*метод, уменьшающий значение ячейки поля на 1, если оно равно -1 или 6
@param i - номер строки
@param j - номер столбца*/
void Battlefield::SetSurroundingKilled(int i, int j)
{
	if (InField(i, j))
		if (field[i, j] == -1 || field[i, j] == 6)
			field[i, j]--;
}

/*метод, проверяющий, можно ли расположить в заданной ячейке новую палубу
@param i - номер строки
@param j - номер столбца
@return - 1, если можно, 0, если нельзя*/
bool Battlefield::TestNewDeck(int i, int j)
{
	if (InField(i, j))
	{
		if (field[i, j] == 0 || field[i, j] == -2)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

/*метод для случайной генерации корабля с заданным числом палуб
@param deckCount - число палуб корабля*/
void Battlefield::ShipAutoPlacement(int deckCount)
{
	srand(time(NULL));
	int i, j; //координаты начала корабля
	int direction; //ориентация корабля
	bool flag = 0; //флаг проверки возможности расположить палубу
	while (true)
	{
		i = rand() % 10;
		j = rand() % 10;
		direction = rand() % 4; //0 вверх, 1 вправо, 2 вниз, 3 влево
		if (TestNewDeck(i, j))
			switch (direction)
			{
			case 0:
				if (TestNewDeck(i - deckCount - 1, j))
					flag = 1;
				break;
			case 1:
				if (TestNewDeck(i, j + deckCount - 1))
					flag = 1;
				break;
			case 2:
				if (TestNewDeck(i + deckCount - 1, j))
					flag = 1;
				break;
			case 3:
				if (TestNewDeck(i, j - deckCount - 1))
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

/*метод, выполняющий полную генерацию игрового поля с помощью метода ShipAutoPlacement*/
void Battlefield::FullAutoPlacement()
{
	ShipAutoPlacement(4); 
	for (int i = 1; i <= 2; i++)
		ShipAutoPlacement(3);
	for (int i = 1; i <= 3; i++)
		ShipAutoPlacement(2);
	for (int i = 1; i <= 4; i++)
		ShipAutoPlacement(1);
}

/*метод, изменяющий значение ячейки поля на -2, если оно равно 0 (пустое пространство)
@param i - номер строки
@param j - номер столбца*/
void Battlefield::SetSurroundingPlaced(int i, int j)
{
	if (InField(i, j))
		if (field[i, j] == 0)
			field[i, j] = -2;
}

/*метод, изменяющий окружение размещенной палубы
@param i - номер строки
@param j - номер столбца*/
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

/*метод, завершающий расстановку корабля*/
void Battlefield::FinishSurrounding()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (field[i, j] == -2)
				field[i, j]++;
}

/*метод ручной расстановки корабля
@param i - номер строки
@param j - номер столбца
@param deckCount - количество палуб корабля
@param direction -  ориетация корабля
@return - 1, если корабль размещен, 0, если нет*/
bool Battlefield::UserPlacement(int i, int j, int deckCount, bool direction)
{
	bool flag = 0; //флаг проверки возможности разместить палубу
	if (TestNewDeck(i, j))
	{
		switch (direction)
		{
		case 0:
			if (TestNewDeck(i, j + deckCount - 1))
				flag = 1;
			break;
		case 1:
			if (TestNewDeck(i + deckCount - 1, j))
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
			field[i, j + k] = deckCount;
			SurroundPlacedDeck(i, j + k);
		}
		break;
	case 1:
		for (int k = deckCount - 1; k >= 1; k--)
		{
			field[i + k, j] = deckCount;
			SurroundPlacedDeck(i + k, j);
		}
		break;
	}
	FinishSurrounding();
	return 1;
}

/*метод получения суммы значений убитых палуб
@return - сумма значений убитых палуб*/
int Battlefield::SumKilled()
{
	int Sum = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (field[i, j] >= 15)
				Sum += field[i, j];
	return Sum;
}

/*метод очистки поля*/
void Battlefield::Clear()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			field[i, j] = 0;
}

/*метод получения количества убитых кораблей каждого типа
@return - массив количества убитых корабей каждого типа*/
cli::array<int>^ Battlefield::GetKillCount()
{
	cli::array<int>^ count;
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			if (field[i, j] == 15)
				s1++;
			if (field[i, j] == 16)
				s2++;
			if (field[i, j] == 17)
				s3++;
			if (field[i, j] == 18)
				s4++;
		}
	s2 /= 2;
	s3 /= 3;
	s4 /= 4;
	count = gcnew cli::array<int> {s4, s3, s2, s1};
	return count;
}

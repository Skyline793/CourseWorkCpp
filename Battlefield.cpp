#include "Battlefield.h"

//�����������
Battlefield::Battlefield()
{
	field = gcnew cli::array<int, 2>(10, 10);
}

/*����� ��������� �������� �� ����
@param i - ����� ������ 
@param j - ����� �������*/
void Battlefield::Fire(int i, int j)
{
	field[i, j] += 7;
}

/*����� ��������� �������� ������ ����
@param i - ����� ������
@param j - ����� �������
@return �������� ������*/
int Battlefield::GetValue(int i, int j)
{
	return field[i, j];
}

/*�����, ����������� ����������� �� ������ � ��������� ������������ ����
@param i - ����� ������
@param j - ����� �������
@return 1, ���� �����������, 0, ���� ���*/
bool Battlefield::InField(int i, int j)
{
	if (i >= 0 && i < 10 && j >= 0 && j < 10)
		return 1;
	else
		return 0;
}

/*�����, ����������� ����������� �������
@param i - ����� ������
@param j - ����� �������*/
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

/*�����, �������������, ���� �� �������, ���������� �������� ������ �������� ���������� ����� ���������
@param i - ����� ������
@param j - ����� �������*
@param deckCount - ���������� ����� �������*/
void Battlefield::AnalizeKill(int i, int j, int deckCount)
{
	int woundCount = 0; //����� �������� �����
	//������� ���������� ������� �����
	for (int x = i - (deckCount - 1); x <= i + (deckCount - 1); x++)
		for (int y = j - (deckCount - 1); y <= j + (deckCount - 1); y++)
		{
			if (InField(x, y))
				if (field[x, y] == deckCount + 7)
					woundCount++;
		}
	if (woundCount == deckCount) //���� ����� �������� ����� ����� ������ ����� �����
		//����������� ������� � ������ � �������� ���������
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

/*�����, ����������� ��������� ������ ������ �� 1 � ������� ������ SetSurroundingKilled
@param i - ����� ������
@param j - ����� �������*/
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

/*�����, ����������� �������� ������ ���� �� 1, ���� ��� ����� -1 ��� 6
@param i - ����� ������
@param j - ����� �������*/
void Battlefield::SetSurroundingKilled(int i, int j)
{
	if (InField(i, j))
		if (field[i, j] == -1 || field[i, j] == 6)
			field[i, j]--;
}

/*�����, �����������, ����� �� ����������� � �������� ������ ����� ������
@param i - ����� ������
@param j - ����� �������
@return - 1, ���� �����, 0, ���� ������*/
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

/*����� ��� ��������� ��������� ������� � �������� ������ �����
@param deckCount - ����� ����� �������*/
void Battlefield::ShipAutoPlacement(int deckCount)
{
	srand(time(NULL));
	int i, j; //���������� ������ �������
	int direction; //���������� �������
	bool flag = 0; //���� �������� ����������� ����������� ������
	while (true)
	{
		i = rand() % 10;
		j = rand() % 10;
		direction = rand() % 4; //0 �����, 1 ������, 2 ����, 3 �����
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

/*�����, ����������� ������ ��������� �������� ���� � ������� ������ ShipAutoPlacement*/
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

/*�����, ���������� �������� ������ ���� �� -2, ���� ��� ����� 0 (������ ������������)
@param i - ����� ������
@param j - ����� �������*/
void Battlefield::SetSurroundingPlaced(int i, int j)
{
	if (InField(i, j))
		if (field[i, j] == 0)
			field[i, j] = -2;
}

/*�����, ���������� ��������� ����������� ������
@param i - ����� ������
@param j - ����� �������*/
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

/*�����, ����������� ����������� �������*/
void Battlefield::FinishSurrounding()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (field[i, j] == -2)
				field[i, j]++;
}

/*����� ������ ����������� �������
@param i - ����� ������
@param j - ����� �������
@param deckCount - ���������� ����� �������
@param direction -  ��������� �������
@return - 1, ���� ������� ��������, 0, ���� ���*/
bool Battlefield::UserPlacement(int i, int j, int deckCount, bool direction)
{
	bool flag = 0; //���� �������� ����������� ���������� ������
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

/*����� ��������� ����� �������� ������ �����
@return - ����� �������� ������ �����*/
int Battlefield::SumKilled()
{
	int Sum = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (field[i, j] >= 15)
				Sum += field[i, j];
	return Sum;
}

/*����� ������� ����*/
void Battlefield::Clear()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			field[i, j] = 0;
}

/*����� ��������� ���������� ������ �������� ������� ����
@return - ������ ���������� ������ ������� ������� ����*/
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

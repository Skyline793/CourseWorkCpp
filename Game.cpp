#include "Game.h"

Game::Game()
{
}

void Game::Start(int rasstanovka)
{
	endGame = 0;
	playerCount = 0;
	compCount = 0;
	playerMove = 1;
	compMove = 0;
	PlayerField.Clear();
	CompField.Clear();
	if (!rasstanovka)
		PlayerField.FullAutoPlacement();
	CompField.FullAutoPlacement();
}

bool Game::CompMove()
{
	compCount++;
	srand(time(NULL));
	bool hit = 0;
	bool wound = 0;
	bool kill = 0;
	bool horiz = 0;
	bool vert = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (PlayerField.GetValue(i, j) >= 9 && PlayerField.GetValue(i, j) <= 11) //���� ������ ��������� �������
			{
				wound = 1;
				//����� ������ �������� ����� ������� �� ���������
				if ((PlayerField.InField(i, j - 1) && PlayerField.GetValue(i, j - 1) >= 9 && PlayerField.GetValue(i, j - 1) <= 11)
					|| (PlayerField.InField(i, j + 1) && PlayerField.GetValue(i, j + 1) >= 9 && PlayerField.GetValue(i, j + 1) <= 11)
					|| (PlayerField.InField(i, j - 2) && PlayerField.GetValue(i, j - 2) >= 9 && PlayerField.GetValue(i, j - 2) <= 11)
					|| (PlayerField.InField(i, j + 2) && PlayerField.GetValue(i, j + 2) >= 9 && PlayerField.GetValue(i, j + 2) <= 11)
					|| (PlayerField.InField(i, j - 3) && PlayerField.GetValue(i, j - 3) >= 9 && PlayerField.GetValue(i, j - 3) <= 11)
					|| (PlayerField.InField(i, j + 3) && PlayerField.GetValue(i, j + 3) >= 9 && PlayerField.GetValue(i, j + 3) <= 11))
					vert = 1;
				if (vert)
				{
					if (PlayerField.InField(i, j + 1) && PlayerField.GetValue(i, j + 1) <= 4 && PlayerField.GetValue(i, j + 1) != -2)
					{
						//������ �������
						PlayerField.Fire(i, j + 1);
						//���������, ��� ����
						PlayerField.TestKilled(i, j + 1);
						// ���� ��������� ���������
						if (PlayerField.GetValue(i, j + 1) >= 8)
							hit = 1;
						goto exit;
					}
					if (PlayerField.InField(i, j - 1) && PlayerField.GetValue(i, j - 1) <= 4 && PlayerField.GetValue(i, j - 1) != -2)
					{
						//������ �������
						PlayerField.Fire(i, j - 1);
						//���������, ��� ����
						PlayerField.TestKilled(i, j - 1);
						// ���� ��������� ���������
						if (PlayerField.GetValue(i, j - 1) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//����� ������ �������� ����� ������� �� ���������, ���� �� ������� �� �����������
				if ((PlayerField.InField(i - 1, j) && PlayerField.GetValue(i - 1, j) >= 9 && PlayerField.GetValue(i - 1, j) <= 11)
					|| (PlayerField.InField(i + 1, j) && PlayerField.GetValue(i + 1, j) >= 9 && PlayerField.GetValue(i + 1, j) <= 11)
					|| (PlayerField.InField(i - 2, j) && PlayerField.GetValue(i - 2, j) >= 9 && PlayerField.GetValue(i - 2, j) <= 11)
					|| (PlayerField.InField(i + 2, j) && PlayerField.GetValue(i + 2, j) >= 9 && PlayerField.GetValue(i + 2, j) <= 11)
					|| (PlayerField.InField(i - 3, j) && PlayerField.GetValue(i - 3, j) >= 9 && PlayerField.GetValue(i - 3, j) <= 11)
					|| (PlayerField.InField(i + 3, j) && PlayerField.GetValue(i + 3, j) >= 9 && PlayerField.GetValue(i + 3, j) <= 11))
					horiz = 1;
				if (horiz)
				{ //�� �����������
					if (PlayerField.InField(i - 1, j) && PlayerField.GetValue(i - 1, j) <= 4 && PlayerField.GetValue(i - 1, j) != -2)
					{
						//������ �������
						PlayerField.Fire(i - 1, j);
						//���������, ��� ����
						PlayerField.TestKilled(i - 1, j);
						// ���� ��������� ���������
						if (PlayerField.GetValue(i - 1, j) >= 8)
							hit = 1;
						goto exit;
					}
					if (PlayerField.InField(i + 1, j) && PlayerField.GetValue(i + 1, j) <= 4 && PlayerField.GetValue(i + 1, j) != -2)
					{
						//������ �������
						PlayerField.Fire(i + 1, j);
						//���������, ��� ����
						PlayerField.TestKilled(i + 1, j);
						// ���� ��������� ���������
						if (PlayerField.GetValue(i + 1, j) >= 8)
							hit = 1;
						goto exit;
					}
				}
				if (horiz == 0 && vert == 0)//���� ������ �� ������� �������� ������
					while (1) //����������� ���� ��������� ���������� ����������� �����
					{
						int dir = rand() % 4;
						if (dir == 0 && PlayerField.InField(i - 1, j) && PlayerField.GetValue(i - 1, j) <= 4 && PlayerField.GetValue(i - 1, j) != -2)
						{
							//������ �������
							PlayerField.Fire(i - 1, j);
							//���������, ��� ����
							PlayerField.TestKilled(i - 1, j);
							// ���� ��������� ���������
							if (PlayerField.GetValue(i - 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 1 && PlayerField.InField(i, j + 1) && PlayerField.GetValue(i, j + 1) <= 4 && PlayerField.GetValue(i, j + 1) != -2)
						{
							//������ �������
							PlayerField.Fire(i, j + 1);
							//���������, ��� ����
							PlayerField.TestKilled(i, j + 1);
							// ���� ��������� ���������
							if (PlayerField.GetValue(i, j + 1) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 2 && PlayerField.InField(i + 1, j) && PlayerField.GetValue(i + 1, j) <= 4 && PlayerField.GetValue(i + 1, j) != -2)
						{
							//������ �������
							PlayerField.Fire(i + 1, j);
							//���������, ��� ����
							PlayerField.TestKilled(i + 1, j);
							// ���� ��������� ���������
							if (PlayerField.GetValue(i + 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 0 && PlayerField.InField(i, j - 1) && PlayerField.GetValue(i, j - 1) <= 4 && PlayerField.GetValue(i, j - 1) != -2)
						{
							//������ �������
							PlayerField.Fire(i, j - 1);
							//���������, ��� ����
							PlayerField.TestKilled(i, j - 1);
							// ���� ��������� ���������
							if (PlayerField.GetValue(i, j - 1) >= 8)
								hit = 1;
							goto exit;
						}
					}
			}
	if (wound == 0)
	{
		while (1)
		{
			// ������� ��������� ������� �� ������� ����
			int i = rand() % 10;
			int j = rand() % 10;
			//���������, ��� ����� ������� �������
			if ((PlayerField.GetValue(i, j) <= 4) && (PlayerField.GetValue(i, j) != -2))
			{
				//������ �������
				PlayerField.Fire(i, j);
				//���������, ��� ����
				PlayerField.TestKilled(i, j);
				// ���� ��������� ���������
				if (PlayerField.GetValue(i, j) >= 8)
					hit = 1;
				//������� ���������
				wound = 1;
				//��������� ����
				break;
			}
		}
	}
exit:
	return hit;
}

void Game::PlayerMove(int i, int j)
{
	playerCount++;
	CompField.Fire(i, j);
	CompField.TestKilled(i, j);
	IsEndGame();
	if (CompField.GetValue(i, j) < 8)
	{
		playerMove = 0;
		compMove = 1;
		while (compMove)
		{
			compMove = CompMove();
		}
		playerMove = 1;
	}
}

int Game::IsEndGame()
{
	if (CompField.SumKilled() == 330) endGame = 1;
	if (PlayerField.SumKilled() == 330) endGame = 2;
	if (endGame == 1)
	{
		playerMove = 0;
		compMove = 0;

	}
	else if (endGame == 2)
	{
		playerMove = 0;
		compMove = 0;
	}
	return endGame;
}

int Game::GetPlayerCount()
{
	return playerCount;
}

int Game::GetCompCount()
{
	return compCount;
}

bool Game::IsPlayerMove()
{
	return playerMove;
}

bool Game::IsCompMove()
{
	return compMove;
}

int Game::PlayerValue(int i, int j)
{
	return PlayerField.GetValue(i, j);
}

int Game::CompValue(int i, int j)
{
	return CompField.GetValue(i, j);
}

bool Game::PlayerPlacement(int i, int j, int deckCount, bool direction)
{
	return PlayerField.UserPlacement(i, j, deckCount, direction);
}

cli::array<int>^ Game::GetPlayerKillCount()
{
	cli::array<int>^ count = PlayerField.GetKillCount();
	return count;
}

cli::array<int>^ Game::GetCompKillCount()
{
	cli::array<int>^ count = CompField.GetKillCount();
	return count;
}

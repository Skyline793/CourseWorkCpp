#include "Game.h"

/*метод начала игры
@param rasstanovka - включен ли режим расстановки*/
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

/*метод хода компьютера
@return - 1, если ход произведен успешно, 0, если нет*/
bool Game::CompMove()
{
	compCount++;
	srand(time(NULL));
	bool hit = 0; //логическая переменная означающая попадание по кораблю
	bool wound = 0; //логическая переменная означающая подбитую палубу
	bool horiz = 0; //флаг поиска корабля по горизонтали
	bool vert = 0; //флаг поиска корабля по вертикали
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (PlayerField.GetValue(i, j) >= 9 && PlayerField.GetValue(i, j) <= 11) //если ячейка подбитого корабля
			{
				wound = 1;
				//поиск других подбитых палуб корабля по вертикали
				if ((PlayerField.InField(i, j - 1) && PlayerField.GetValue(i, j - 1) >= 9 && PlayerField.GetValue(i, j - 1) <= 11)
					|| (PlayerField.InField(i, j + 1) && PlayerField.GetValue(i, j + 1) >= 9 && PlayerField.GetValue(i, j + 1) <= 11)
					|| (PlayerField.InField(i, j - 2) && PlayerField.GetValue(i, j - 2) >= 9 && PlayerField.GetValue(i, j - 2) <= 11)
					|| (PlayerField.InField(i, j + 2) && PlayerField.GetValue(i, j + 2) >= 9 && PlayerField.GetValue(i, j + 2) <= 11)
					|| (PlayerField.InField(i, j - 3) && PlayerField.GetValue(i, j - 3) >= 9 && PlayerField.GetValue(i, j - 3) <= 11)
					|| (PlayerField.InField(i, j + 3) && PlayerField.GetValue(i, j + 3) >= 9 && PlayerField.GetValue(i, j + 3) <= 11))
					vert = 1;
				//если по вертикали найдена подбитая палуба
				if (vert)
				{
					if (PlayerField.InField(i, j + 1) && PlayerField.GetValue(i, j + 1) <= 4 && PlayerField.GetValue(i, j + 1) != -2)
					{
						PlayerField.Fire(i, j + 1);
						PlayerField.TestKilled(i, j + 1);
						if (PlayerField.GetValue(i, j + 1) >= 8)
							hit = 1;
						goto exit;
					}
					if (PlayerField.InField(i, j - 1) && PlayerField.GetValue(i, j - 1) <= 4 && PlayerField.GetValue(i, j - 1) != -2)
					{
						PlayerField.Fire(i, j - 1);
						PlayerField.TestKilled(i, j - 1);
						if (PlayerField.GetValue(i, j - 1) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//поиск других подбитых палуб корабля по горизонтали, если не найдены по вертикали
				if ((PlayerField.InField(i - 1, j) && PlayerField.GetValue(i - 1, j) >= 9 && PlayerField.GetValue(i - 1, j) <= 11)
					|| (PlayerField.InField(i + 1, j) && PlayerField.GetValue(i + 1, j) >= 9 && PlayerField.GetValue(i + 1, j) <= 11)
					|| (PlayerField.InField(i - 2, j) && PlayerField.GetValue(i - 2, j) >= 9 && PlayerField.GetValue(i - 2, j) <= 11)
					|| (PlayerField.InField(i + 2, j) && PlayerField.GetValue(i + 2, j) >= 9 && PlayerField.GetValue(i + 2, j) <= 11)
					|| (PlayerField.InField(i - 3, j) && PlayerField.GetValue(i - 3, j) >= 9 && PlayerField.GetValue(i - 3, j) <= 11)
					|| (PlayerField.InField(i + 3, j) && PlayerField.GetValue(i + 3, j) >= 9 && PlayerField.GetValue(i + 3, j) <= 11))
					horiz = 1;
				if (horiz)
				{ 
					if (PlayerField.InField(i - 1, j) && PlayerField.GetValue(i - 1, j) <= 4 && PlayerField.GetValue(i - 1, j) != -2)
					{
						PlayerField.Fire(i - 1, j);
						PlayerField.TestKilled(i - 1, j);
						if (PlayerField.GetValue(i - 1, j) >= 8)
							hit = 1;
						goto exit;
					}
					if (PlayerField.InField(i + 1, j) && PlayerField.GetValue(i + 1, j) <= 4 && PlayerField.GetValue(i + 1, j) != -2)
					{
						PlayerField.Fire(i + 1, j);
						PlayerField.TestKilled(i + 1, j);
						if (PlayerField.GetValue(i + 1, j) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//если вокруг не найдены подбитые палубы
				if (horiz == 0 && vert == 0)
					while (1) //бесконечный цикл генерации случайного направления удара
					{
						int dir = rand() % 4; //0 вверх, 1 вправо, 2 вниз, 3 влево
						if (dir == 0 && PlayerField.InField(i - 1, j) && PlayerField.GetValue(i - 1, j) <= 4 && PlayerField.GetValue(i - 1, j) != -2)
						{
							PlayerField.Fire(i - 1, j);
							PlayerField.TestKilled(i - 1, j);
							if (PlayerField.GetValue(i - 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 1 && PlayerField.InField(i, j + 1) && PlayerField.GetValue(i, j + 1) <= 4 && PlayerField.GetValue(i, j + 1) != -2)
						{
							PlayerField.Fire(i, j + 1);
							PlayerField.TestKilled(i, j + 1);
							if (PlayerField.GetValue(i, j + 1) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 2 && PlayerField.InField(i + 1, j) && PlayerField.GetValue(i + 1, j) <= 4 && PlayerField.GetValue(i + 1, j) != -2)
						{
							PlayerField.Fire(i + 1, j);
							PlayerField.TestKilled(i + 1, j);
							if (PlayerField.GetValue(i + 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 3 && PlayerField.InField(i, j - 1) && PlayerField.GetValue(i, j - 1) <= 4 && PlayerField.GetValue(i, j - 1) != -2)
						{
							PlayerField.Fire(i, j - 1);
							PlayerField.TestKilled(i, j - 1);
							if (PlayerField.GetValue(i, j - 1) >= 8)
								hit = 1;
							goto exit;
						}
					}
			}
		//если на поле не найдено подбитых палуб
	if (wound == 0)
	{
		while (1)
		{
			// Находим случайную позицию на игровом поле
			int i = rand() % 10;
			int j = rand() % 10;
			//Проверяем, что можно сделать выстрел
			if ((PlayerField.GetValue(i, j) <= 4) && (PlayerField.GetValue(i, j) != -2))
			{
				PlayerField.Fire(i, j);
				PlayerField.TestKilled(i, j);
				if (PlayerField.GetValue(i, j) >= 8) {
					hit = 1;
				}
				break;
			}
		}
	}
exit:
	return hit; 
}

/*метод хода игрока
@param i - номер строки
@param j - номер столбца*/
void Game::PlayerMove(int i, int j)
{
	playerCount++;
	CompField.Fire(i, j);
	CompField.TestKilled(i, j);
	Thread^ thread = gcnew Thread(gcnew ThreadStart(this, &Game::Run)); //создаем новый поток, в котором будет происходить ход пк

	if (CompField.GetValue(i, j) < 8) //если игрок не попал
	{
		thread->Start(); //запкустить поток
	}
}

//метод-делегает для потока хода компьютера
void Game::Run()
{
	Thread^ current = Thread::CurrentThread;
	playerMove = 0;
	compMove = 1;
	while (compMove)
	{
		current->Sleep(600); //сделать паузу перед ходом пк
		compMove = CompMove(); //ход пк
	}
	playerMove = 1;
}

/*метод проверки окончания игры
@return - 0 - игра продолжается, 1 - победил игрок, 2 - победил пк*/
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

/*метод, возвращающий количество сделанных игроком ходов*/
int Game::GetPlayerCount()
{
	return playerCount;
}

/*метод, возвращающий количество сделанных пк ходов*/
int Game::GetCompCount()
{
	return compCount;
}

/*метод, проверяющий ход ли игрока
@return - 1, если ход игрока, 0, если ход пк*/
bool Game::IsPlayerMove()
{
	return playerMove;
}

/*метод, проверяющий ход ли пк
@return - 1, если ход пк, 0, если ход игрока*/
bool Game::IsCompMove()
{
	return compMove;
}

//метод очистки поля игрока
void Game::ClearPlayerField()
{
	PlayerField.Clear();
}

/*метод получения значения ячейки поля игрока
@param i - номер строки
@param j - номер столбца
@return - значение ячейки [i][j] поля игрока*/
int Game::PlayerValue(int i, int j)
{
	return PlayerField.GetValue(i, j);
}

/*метод получения значения ячейки поля пк
@param i - номер строки
@param j - номер столбца
@return - значение ячейки [i][j] поля пк*/
int Game::CompValue(int i, int j)
{
	return CompField.GetValue(i, j);
}

/*метод ручного размещения корабля на поле игрока
@param i - номер строки
@param j - номер столбца
@param deckCount - количество палуб
@param direction - направление расстановки
@return - 1, если корабль размещен, 0, если нет*/
bool Game::PlayerPlacement(int i, int j, int deckCount, bool direction)
{
	return PlayerField.UserPlacement(i, j, deckCount, direction);
}

/*метод получения числа убитых кораблей каждого типа на поле игрока
@return - массив количеств убитых кораблей*/
cli::array<int>^ Game::GetPlayerKillCount()
{
	cli::array<int>^ count = PlayerField.GetKillCount();
	return count;
}

/*метод получения числа убитых кораблей каждого типа на поле пк
@return - массив количеств убитых кораблей*/
cli::array<int>^ Game::GetCompKillCount()
{
	cli::array<int>^ count = CompField.GetKillCount();
	return count;
}

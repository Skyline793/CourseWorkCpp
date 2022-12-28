#include "GamePVE.h"

/*метод хода компьютера
@return - 1, если ход произведен успешно, 0, если нет*/
bool GamePVE::PCMove()
{
	secondPlayerCount++;
	srand(time(NULL));
	bool hit = 0; //логическая переменная означающая попадание по кораблю
	bool wound = 0; //логическая переменная означающая подбитую палубу
	bool horiz = 0; //флаг поиска корабля по горизонтали
	bool vert = 0; //флаг поиска корабля по вертикали
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (firstPlayerField.GetValue(i, j) >= 9 && firstPlayerField.GetValue(i, j) <= 11) //если ячейка подбитого корабля
			{
				wound = 1;
				//поиск других подбитых палуб корабля по вертикали
				if ((firstPlayerField.InField(i, j - 1) && firstPlayerField.GetValue(i, j - 1) >= 9 && firstPlayerField.GetValue(i, j - 1) <= 11)
					|| (firstPlayerField.InField(i, j + 1) && firstPlayerField.GetValue(i, j + 1) >= 9 && firstPlayerField.GetValue(i, j + 1) <= 11)
					|| (firstPlayerField.InField(i, j - 2) && firstPlayerField.GetValue(i, j - 2) >= 9 && firstPlayerField.GetValue(i, j - 2) <= 11)
					|| (firstPlayerField.InField(i, j + 2) && firstPlayerField.GetValue(i, j + 2) >= 9 && firstPlayerField.GetValue(i, j + 2) <= 11)
					|| (firstPlayerField.InField(i, j - 3) && firstPlayerField.GetValue(i, j - 3) >= 9 && firstPlayerField.GetValue(i, j - 3) <= 11)
					|| (firstPlayerField.InField(i, j + 3) && firstPlayerField.GetValue(i, j + 3) >= 9 && firstPlayerField.GetValue(i, j + 3) <= 11))
					vert = 1;
				//если по вертикали найдена подбитая палуба
				if (vert)
				{
					if (firstPlayerField.InField(i, j + 1) && firstPlayerField.GetValue(i, j + 1) <= 4 && firstPlayerField.GetValue(i, j + 1) != -2)
					{
						firstPlayerField.Fire(i, j + 1);
						firstPlayerField.TestKilled(i, j + 1);
						if (firstPlayerField.GetValue(i, j + 1) >= 8)
							hit = 1;
						goto exit;
					}
					if (firstPlayerField.InField(i, j - 1) && firstPlayerField.GetValue(i, j - 1) <= 4 && firstPlayerField.GetValue(i, j - 1) != -2)
					{
						firstPlayerField.Fire(i, j - 1);
						firstPlayerField.TestKilled(i, j - 1);
						if (firstPlayerField.GetValue(i, j - 1) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//поиск других подбитых палуб корабля по горизонтали, если не найдены по вертикали
				if ((firstPlayerField.InField(i - 1, j) && firstPlayerField.GetValue(i - 1, j) >= 9 && firstPlayerField.GetValue(i - 1, j) <= 11)
					|| (firstPlayerField.InField(i + 1, j) && firstPlayerField.GetValue(i + 1, j) >= 9 && firstPlayerField.GetValue(i + 1, j) <= 11)
					|| (firstPlayerField.InField(i - 2, j) && firstPlayerField.GetValue(i - 2, j) >= 9 && firstPlayerField.GetValue(i - 2, j) <= 11)
					|| (firstPlayerField.InField(i + 2, j) && firstPlayerField.GetValue(i + 2, j) >= 9 && firstPlayerField.GetValue(i + 2, j) <= 11)
					|| (firstPlayerField.InField(i - 3, j) && firstPlayerField.GetValue(i - 3, j) >= 9 && firstPlayerField.GetValue(i - 3, j) <= 11)
					|| (firstPlayerField.InField(i + 3, j) && firstPlayerField.GetValue(i + 3, j) >= 9 && firstPlayerField.GetValue(i + 3, j) <= 11))
					horiz = 1;
				if (horiz)
				{
					if (firstPlayerField.InField(i - 1, j) && firstPlayerField.GetValue(i - 1, j) <= 4 && firstPlayerField.GetValue(i - 1, j) != -2)
					{
						firstPlayerField.Fire(i - 1, j);
						firstPlayerField.TestKilled(i - 1, j);
						if (firstPlayerField.GetValue(i - 1, j) >= 8)
							hit = 1;
						goto exit;
					}
					if (firstPlayerField.InField(i + 1, j) && firstPlayerField.GetValue(i + 1, j) <= 4 && firstPlayerField.GetValue(i + 1, j) != -2)
					{
						firstPlayerField.Fire(i + 1, j);
						firstPlayerField.TestKilled(i + 1, j);
						if (firstPlayerField.GetValue(i + 1, j) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//если вокруг не найдены подбитые палубы
				if (horiz == 0 && vert == 0)
					while (1) //бесконечный цикл генерации случайного направления удара
					{
						int dir = rand() % 4; //0 вверх, 1 вправо, 2 вниз, 3 влево
						if (dir == 0 && firstPlayerField.InField(i - 1, j) && firstPlayerField.GetValue(i - 1, j) <= 4 && firstPlayerField.GetValue(i - 1, j) != -2)
						{
							firstPlayerField.Fire(i - 1, j);
							firstPlayerField.TestKilled(i - 1, j);
							if (firstPlayerField.GetValue(i - 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 1 && firstPlayerField.InField(i, j + 1) && firstPlayerField.GetValue(i, j + 1) <= 4 && firstPlayerField.GetValue(i, j + 1) != -2)
						{
							firstPlayerField.Fire(i, j + 1);
							firstPlayerField.TestKilled(i, j + 1);
							if (firstPlayerField.GetValue(i, j + 1) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 2 && firstPlayerField.InField(i + 1, j) && firstPlayerField.GetValue(i + 1, j) <= 4 && firstPlayerField.GetValue(i + 1, j) != -2)
						{
							firstPlayerField.Fire(i + 1, j);
							firstPlayerField.TestKilled(i + 1, j);
							if (firstPlayerField.GetValue(i + 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 3 && firstPlayerField.InField(i, j - 1) && firstPlayerField.GetValue(i, j - 1) <= 4 && firstPlayerField.GetValue(i, j - 1) != -2)
						{
							firstPlayerField.Fire(i, j - 1);
							firstPlayerField.TestKilled(i, j - 1);
							if (firstPlayerField.GetValue(i, j - 1) >= 8)
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
			if ((firstPlayerField.GetValue(i, j) <= 4) && (firstPlayerField.GetValue(i, j) != -2))
			{
				firstPlayerField.Fire(i, j);
				firstPlayerField.TestKilled(i, j);
				if (firstPlayerField.GetValue(i, j) >= 8) {
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
void GamePVE::PlayerMove(int i, int j)
{
	firstPlayerCount++;
	secondPlayerField.Fire(i, j);
	secondPlayerField.TestKilled(i, j);
	Thread^ thread = gcnew Thread(gcnew ThreadStart(this, &GamePVE::Run)); //создаем новый поток, в котором будет происходить ход пк

	if (secondPlayerField.GetValue(i, j) < 8) //если игрок не попал
	{
		thread->Start(); //запкустить поток
	}
}

//метод-делегает для потока хода компьютера
void GamePVE::Run()
{
	Thread^ current = Thread::CurrentThread;
	firstPlayerMove = 0;
	secondPlayerMove = 1;
	while (secondPlayerMove)
	{
		current->Sleep(600); //сделать паузу перед ходом пк
		secondPlayerMove = PCMove(); //ход пк
	}
	firstPlayerMove = 1;
}

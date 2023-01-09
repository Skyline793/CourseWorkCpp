#include "Game.h"

/*метод начала игры
@param rasstanovka - включен ли режим расстановки*/
void Game::Start(bool rasstanovka)
{
	endGame = 0;
	firstPlayerCount = 0;
	secondPlayerCount = 0;
	firstPlayerMove = 1;
	secondPlayerMove = 0;
	firstPlayerField.Clear();
	secondPlayerField.Clear();
	if (!rasstanovka)
		firstPlayerField.FullAutoPlacement();
	secondPlayerField.FullAutoPlacement();
}

/*метод проверки окончания игры
@return - 0 - игра продолжается, 1 - победил игрок 1, 2 - победил игрок 2*/
int Game::IsEndGame()
{
	if (secondPlayerField.SumKilled() == 330) endGame = 1;
	if (firstPlayerField.SumKilled() == 330) endGame = 2;
	if (endGame == 1 || endGame == 2)
	{
		firstPlayerMove = 0;
		secondPlayerMove = 0;

	}
	return endGame;
}

/*метод, возвращающий количество сделанных игроком 1 ходов*/
int Game::GetFirstPlayerCount()
{
	return firstPlayerCount;
}

/*метод, возвращающий количество сделанных игроком 2 ходов*/
int Game::GetSecondPlayerCount()
{
	return secondPlayerCount;
}

/*метод, проверяющий ход ли игрока 1
@return - 1, если ход игрока 1, 0, если ход игрока 2*/
bool Game::IsFirstPlayerMove()
{
	return firstPlayerMove;
}

/*метод, проверяющий ход ли игрока 2
@return - 1, если ход игрока 2, 0, если ход игрока 1*/
bool Game::IsSecondPlayerMove()
{
	return secondPlayerMove;
}

//метод очистки поля игрока 1
void Game::ClearFirstPlayerField()
{
	firstPlayerField.Clear();
}

/*метод получения значения ячейки поля игрока 1
@param i - номер строки
@param j - номер столбца
@return - значение ячейки [i][j] поля игрока 1*/
int Game::FirstPlayerValue(int i, int j)
{
	return firstPlayerField.GetValue(i, j);
}

/*метод получения значения ячейки поля игрока 2
@param i - номер строки
@param j - номер столбца
@return - значение ячейки [i][j] поля игрока 2*/
int Game::SecondPlayerValue(int i, int j)
{
	return secondPlayerField.GetValue(i, j);
}

/*метод ручного размещения корабля на поле игрока 1
@param i - номер строки
@param j - номер столбца
@param deckCount - количество палуб
@param direction - направление расстановки
@return - 1, если корабль размещен, 0, если нет*/
bool Game::FirstPlayerPlacement(int i, int j, int deckCount, bool direction)
{
	return firstPlayerField.UserPlacement(i, j, deckCount, direction);
}

/*метод получения числа убитых кораблей каждого типа на поле игрока 1
@return - массив количеств убитых кораблей*/
cli::array<int>^ Game::GetFirstPlayerKillCount()
{
	cli::array<int>^ count = firstPlayerField.GetKillCount();
	return count;
}

/*метод получения числа убитых кораблей каждого типа на поле игрока 2
@return - массив количеств убитых кораблей*/
cli::array<int>^ Game::GetSecondPlayerKillCount()
{
	cli::array<int>^ count = secondPlayerField.GetKillCount();
	return count;
}

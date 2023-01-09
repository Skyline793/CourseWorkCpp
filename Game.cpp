#include "Game.h"

/*����� ������ ����
@param rasstanovka - ������� �� ����� �����������*/
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

/*����� �������� ��������� ����
@return - 0 - ���� ������������, 1 - ������� ����� 1, 2 - ������� ����� 2*/
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

/*�����, ������������ ���������� ��������� ������� 1 �����*/
int Game::GetFirstPlayerCount()
{
	return firstPlayerCount;
}

/*�����, ������������ ���������� ��������� ������� 2 �����*/
int Game::GetSecondPlayerCount()
{
	return secondPlayerCount;
}

/*�����, ����������� ��� �� ������ 1
@return - 1, ���� ��� ������ 1, 0, ���� ��� ������ 2*/
bool Game::IsFirstPlayerMove()
{
	return firstPlayerMove;
}

/*�����, ����������� ��� �� ������ 2
@return - 1, ���� ��� ������ 2, 0, ���� ��� ������ 1*/
bool Game::IsSecondPlayerMove()
{
	return secondPlayerMove;
}

//����� ������� ���� ������ 1
void Game::ClearFirstPlayerField()
{
	firstPlayerField.Clear();
}

/*����� ��������� �������� ������ ���� ������ 1
@param i - ����� ������
@param j - ����� �������
@return - �������� ������ [i][j] ���� ������ 1*/
int Game::FirstPlayerValue(int i, int j)
{
	return firstPlayerField.GetValue(i, j);
}

/*����� ��������� �������� ������ ���� ������ 2
@param i - ����� ������
@param j - ����� �������
@return - �������� ������ [i][j] ���� ������ 2*/
int Game::SecondPlayerValue(int i, int j)
{
	return secondPlayerField.GetValue(i, j);
}

/*����� ������� ���������� ������� �� ���� ������ 1
@param i - ����� ������
@param j - ����� �������
@param deckCount - ���������� �����
@param direction - ����������� �����������
@return - 1, ���� ������� ��������, 0, ���� ���*/
bool Game::FirstPlayerPlacement(int i, int j, int deckCount, bool direction)
{
	return firstPlayerField.UserPlacement(i, j, deckCount, direction);
}

/*����� ��������� ����� ������ �������� ������� ���� �� ���� ������ 1
@return - ������ ��������� ������ ��������*/
cli::array<int>^ Game::GetFirstPlayerKillCount()
{
	cli::array<int>^ count = firstPlayerField.GetKillCount();
	return count;
}

/*����� ��������� ����� ������ �������� ������� ���� �� ���� ������ 2
@return - ������ ��������� ������ ��������*/
cli::array<int>^ Game::GetSecondPlayerKillCount()
{
	cli::array<int>^ count = secondPlayerField.GetKillCount();
	return count;
}

#pragma once
#include "Battlefield.h"
#include<iostream>

using namespace std;
using System::SerializableAttribute;
using namespace System::Threading;

[Serializable]
ref class Game //абстрактный класс класс, реализующий ход игры
{
protected:
	Battlefield firstPlayerField, secondPlayerField; //объекты поля игроков
	int endGame; //0 игра идет, 1 игрок победил, 2 компьютер победил
	int firstPlayerCount; //число ходов игрока 1
	int secondPlayerCount; //число ходов игрока 2
	bool firstPlayerMove; //логическая переменная, означающая время хода игрока 1
	bool secondPlayerMove; //логическая переменная, означающая время хода игрока 2
public:
	virtual void PlayerMove(int i, int j) = 0; //виртуальный метод хода игрока
	void Start(int rasstanovka); //метод начала игры
	int IsEndGame(); //метод проверки окончания игры
	int GetFirstPlayerCount(); /*метод, возвращающий количество сделанных первым игроком ходов*/
	int GetSecondPlayerCount(); /*метод, возвращающий количество сделанных вторым игроком (пк) ходов*/
	bool IsFirstPlayerMove(); //метод, проверяющий ход ли игрока 1
	bool IsSecondPlayerMove(); //метод, проверяющий ход ли игрока 2 (пк)
	void ClearFirstPlayerField(); //метод очистки поля игрока 1
	int FirstPlayerValue(int i, int j); //метод получения значения ячейки поля игрока 1 
	int SecondPlayerValue(int i, int j); //метод получения значения ячейки поля игрока 2 (пк)
	bool FirstPlayerPlacement(int i, int j, int deckCount, bool direction); //метод ручного размещения корабля на поле игрока 1
	cli::array<int>^ GetFirstPlayerKillCount(); //метод получения числа убитых кораблей каждого типа на поле игрока 1
	cli::array<int>^ GetSecondPlayerKillCount(); //метод получения числа убитых кораблей каждого типа на поле игрока 2
};


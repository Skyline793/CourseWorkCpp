#pragma once
#include "Battlefield.h"
#include<iostream>

using namespace std;
using System::SerializableAttribute;
using namespace System::Threading;

[Serializable]
ref class Game //класс, реализующий ход игры
{
	Battlefield PlayerField, CompField; //объекты поле игрока и поле пк
	int endGame; //0 игра идет, 1 игрок победил, 2 компьютер победил
	int playerCount; //число ходов игрока
	int compCount; //число ходов пк
	bool playerMove; //логическа€ переменна€, означающа€ ход игрока
	bool compMove; //логическа€ переменна€, означающа€ ход пк
	bool CompMove(); //метод хода компьютера
	void Run(); //метод-делегает дл€ потока хода компьютера
public:
	void Start(int rasstanovka); //метод начала игры
	void PlayerMove(int i, int j); //метод хода игрока
	int IsEndGame(); //метод проверки окончани€ игры
	int GetPlayerCount(); /*метод, возвращающий количество сделанных игроком ходов*/
	int GetCompCount(); /*метод, возвращающий количество сделанных пк ходов*/
	bool IsPlayerMove(); //метод, провер€ющий ход ли игрока
	bool IsCompMove(); //метод, провер€ющий ход ли пк
	void ClearPlayerField(); //метод очистки пол€ игрока
	int PlayerValue(int i, int j); //метод получени€ значени€ €чейки пол€ игрока
	int CompValue(int i, int j); //метод получени€ значени€ €чейки пол€ пк
	bool PlayerPlacement(int i, int j, int deckCount, bool direction); //метод ручного размещени€ корабл€ на поле игрока
	cli::array<int>^ GetPlayerKillCount(); //метод получени€ числа убитых кораблей каждого типа на поле игрока
	cli::array<int>^ GetCompKillCount(); //метод получени€ числа убитых кораблей каждого типа на поле пк
};


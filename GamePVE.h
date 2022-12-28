#include "Game.h"

#pragma once
using System::SerializableAttribute;

[Serializable]
ref class GamePVE : public Game //класс, реализующий ход игры в режиме игрок против пк
{
public:
	bool PCMove(); //метод хода компьютера
	void PlayerMove(int i, int j) override; //метод хода игрока
	void Run(); //метод-делегает для потока хода компьютера

};


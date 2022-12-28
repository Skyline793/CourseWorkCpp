#pragma once
#include "Game.h"
using System::SerializableAttribute;

[Serializable]
ref class GamePVP : public Game //класс, реализующий хож игры в режиме игрок против игрока
{
public:
	void PlayerMove(int i, int j) override; //метод хода игрока
};


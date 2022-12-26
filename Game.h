#pragma once
#include "Battlefield.h"
#include<iostream>

using namespace std;
using System::SerializableAttribute;

[Serializable]
ref class Game
{
	Battlefield PlayerField, CompField;
	int endGame; //0 игра идет, 1 игрок победил, 2 компьютер победил
	int playerCount, compCount;
	bool playerMove, compMove;
public:
	
	Game();
	void Start(int rasstanovka);
	bool CompMove();
	void PlayerMove(int i, int j);
	int IsEndGame();
	int GetPlayerCount();
	int GetCompCount();
	bool IsPlayerMove();
	bool IsCompMove();
	void ClearPlayerField();
	int PlayerValue(int i, int j);
	int CompValue(int i, int j);
	bool PlayerPlacement(int i, int j, int deckCount, bool direction);
	cli::array<int>^ GetPlayerKillCount();
	cli::array<int>^ GetCompKillCount();
};


#pragma once
#include "Battlefield.h"
#include<iostream>

using namespace std;

ref class Game
{
	Battlefield PlayerField, CompField;
	int endGame; //0 игра идет, 1 игрок победил, 2 компьютер победил
	int P1, P2, P3, P4;
	int C1, C2, C3, C4;
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
	int PlayerValue(int i, int j);
	int CompValue(int i, int j);
	bool PlayerPlacement(int i, int j, int deckCount, bool direction);
	cli::array<int>^ GetPlayerKillCount();
	cli::array<int>^ GetCompKillCount();
};


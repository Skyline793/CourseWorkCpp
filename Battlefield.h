#pragma once
#include <iostream>
using namespace std;


ref class Battlefield
{
private:
	cli::array<int, 2>^ field = gcnew cli::array<int, 2>(N, N);
public:
	static const int N = 10;
	Battlefield();
	void Fire(int i, int j);
	int GetValue(int i, int j);
	bool InField(int i, int j);
	void TestKilled(int i, int j);
	void AnalizeKill(int i, int j, int deckCount);
	void SetSurroundingKilled(int i, int j);
	void SurroundKilledDeck(int i, int j);
	bool TestNewDeck(int i, int j);
	void ShipAutoPlacement(int deckCount);
	void FullAutoPlacement();
	void SetSurroundingPlaced(int i, int j);
	void SurroundPlacedDeck(int i, int j);
	void FinishSurrounding();
	bool UserPlacement(int i, int j, int deckCount, bool direction);
	int SumKilled();
	void Clear();
};


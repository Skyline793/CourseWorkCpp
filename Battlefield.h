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
	void Display() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%2d  ", field[i, j]);
			cout << endl << endl;
		}
	}
	void Fire(int i, int j);
	int GetValue(int i, int j);
	bool InField(int i, int j);
	void TestKilled(int i, int j);
	void AnalizeKill(int i, int j, int deckCount);
	void SetSurroundingKilled(int i, int j);
	void SurroundKilledDeck(int i, int j);
	bool TestNewPaluba(int i, int j);
	void ShipAutoPlacement(int deckCount);
	void FullAutoPlacement();
	void SetSurroundingPlaced(int i, int j);
	void SurroundPlacedDeck(int i, int j);
	void FinishSurrounding();
	bool UserPlacement(int i, int j, int deckCount, int direction);
	int SumKilled();
};


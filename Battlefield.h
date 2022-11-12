#pragma once
#include <iostream>
using namespace std;
using namespace System;


ref class Battlefield
{
private:
	const int N = 10;
	cli::array<int, 2>^ field = gcnew cli::array<int, 2>(N, N);
public:
	Battlefield();
	void Display() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%2d  ", field[i, j]);
			cout << endl << endl;
		}
	}
	bool TestNewPaluba(int i, int j);
	void ShipAutoPlacement(int deckCount);
	void FullAutoPlacement();
	void SetSurrounding(int i, int j);
	void SurroundDeck(int i, int j);
	void FinishSurrounding();
	bool PlayerPlacement(int i, int j, int deckCount, int direction);
};


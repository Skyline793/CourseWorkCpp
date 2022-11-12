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
				Console::Write(field[i, j] + " ");
			Console::WriteLine();
		}
	}
	bool TestNewPaluba(int i, int j);
	void ShipAutoPlacement(int deckCount);
	void FullAutoPlacement();

};


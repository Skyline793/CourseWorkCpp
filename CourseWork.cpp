#include <iostream>
#include "Battlefield.h"
#include "Game.h"
using namespace std;

int main() {
	Game g;

	/*g.PlayerField.PlayerPlacement(4,0, 4, 2);
	g.PlayerField.IncreaseValue(4,0, 7);*/
	g.PlayerField.FullAutoPlacement();
	g.compField.FullAutoPlacement();
	//g.PlayerField.Display();
	cout << endl;
	int x, y;
	for (int i = 0; i < 100; i++) {
		cout << "Player:" << endl;
		g.PlayerField.Display();
		cout << "PC:" << endl;
		g.compField.Display();
		cout << "Move: ";
		cin >> x >> y;
		g.PlayerMove(x, y);
		
	}

	cin.get();
}
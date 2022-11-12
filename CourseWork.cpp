#include <iostream>
#include "Battlefield.h"
using namespace std;

int main() {
	Battlefield a;
	int i, j, dir;
	a.PlayerPlacement(0, 0, 4, 2);
	a.Display();
	cin.get();
}
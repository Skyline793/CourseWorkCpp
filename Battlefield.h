#pragma once
#include <iostream>
using namespace std;
using System::SerializableAttribute;

[Serializable]
ref class Battlefield //класс игровое поле
{
private:
	cli::array<int, 2>^ field; //игровое поле

	void AnalizeKill(int i, int j, int deckCount); //метод, анализирующий, убит ли корабль, координаты подбитой палубы которого передаются через параметры
	void SetSurroundingKilled(int i, int j); //метод, уменьшающий значение ячейки поля на 1, если оно равно -1 или 6
	void SurroundKilledDeck(int i, int j); //метод, уменьшающий окружение убитой палубы на 1 с помощью метода SetSurroundingKilled
	bool TestNewDeck(int i, int j); //метод, проверяющий, можно ли расположить в заданной ячейке новую палубу
	void ShipAutoPlacement(int deckCount); //метод для случайной генерации корабля с заданным числом палуб
	void SetSurroundingPlaced(int i, int j); //метод, изменяющий значение ячейки поля на -2, если оно равно 0 (пустое пространство)
	void SurroundPlacedDeck(int i, int j); //метод, изменяющий окружение размещенной палубы
	void FinishSurrounding(); //метод, завершающий расстановку корабля
public:
	Battlefield(); //конструктор
	void Fire(int i, int j); //метод симуляции выстрела по полю
	int GetValue(int i, int j); //метод получения значения ячейки поля
	bool InField(int i, int j); //метод, проверяющий принадлежит ли ячейка с заданными координатами полю
	void TestKilled(int i, int j); //метод, проверяющий уничтожение корабля
	void FullAutoPlacement(); //метод, выполняющий полную генерацию игрового поля с помощью метода ShipAutoPlacement
	bool UserPlacement(int i, int j, int deckCount, bool direction); //метод ручной расстановки корабля
	int SumKilled(); //метод получения суммы значений убитых палуб
	void Clear(); //метод очистки поля
	cli::array<int>^ GetKillCount(); //метод получения количества убитых кораблей каждого типа
};


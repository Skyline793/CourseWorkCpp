#pragma once
#include <iostream>
using namespace std;
using System::SerializableAttribute;

[Serializable]
ref class Battlefield //����� ������� ����
{
private:
	cli::array<int, 2>^ field; //������� ����

	void AnalizeKill(int i, int j, int deckCount); //�����, �������������, ���� �� �������, ���������� �������� ������ �������� ���������� ����� ���������
	void SetSurroundingKilled(int i, int j); //�����, ����������� �������� ������ ���� �� 1, ���� ��� ����� -1 ��� 6
	void SurroundKilledDeck(int i, int j); //�����, ����������� ��������� ������ ������ �� 1 � ������� ������ SetSurroundingKilled
	bool TestNewDeck(int i, int j); //�����, �����������, ����� �� ����������� � �������� ������ ����� ������
	void ShipAutoPlacement(int deckCount); //����� ��� ��������� ��������� ������� � �������� ������ �����
	void SetSurroundingPlaced(int i, int j); //�����, ���������� �������� ������ ���� �� -2, ���� ��� ����� 0 (������ ������������)
	void SurroundPlacedDeck(int i, int j); //�����, ���������� ��������� ����������� ������
	void FinishSurrounding(); //�����, ����������� ����������� �������
public:
	Battlefield(); //�����������
	void Fire(int i, int j); //����� ��������� �������� �� ����
	int GetValue(int i, int j); //����� ��������� �������� ������ ����
	bool InField(int i, int j); //�����, ����������� ����������� �� ������ � ��������� ������������ ����
	void TestKilled(int i, int j); //�����, ����������� ����������� �������
	void FullAutoPlacement(); //�����, ����������� ������ ��������� �������� ���� � ������� ������ ShipAutoPlacement
	bool UserPlacement(int i, int j, int deckCount, bool direction); //����� ������ ����������� �������
	int SumKilled(); //����� ��������� ����� �������� ������ �����
	void Clear(); //����� ������� ����
	cli::array<int>^ GetKillCount(); //����� ��������� ���������� ������ �������� ������� ����
};


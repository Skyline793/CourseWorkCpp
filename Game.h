#pragma once
#include "Battlefield.h"
#include<iostream>

using namespace std;
using System::SerializableAttribute;
using namespace System::Threading;

[Serializable]
ref class Game //����������� ����� �����, ����������� ��� ����
{
protected:
	Battlefield firstPlayerField, secondPlayerField; //������� ���� �������
	int endGame; //0 ���� ����, 1 ����� �������, 2 ��������� �������
	int firstPlayerCount; //����� ����� ������ 1
	int secondPlayerCount; //����� ����� ������ 2
	bool firstPlayerMove; //���������� ����������, ���������� ����� ���� ������ 1
	bool secondPlayerMove; //���������� ����������, ���������� ����� ���� ������ 2
public:
	virtual void PlayerMove(int i, int j) = 0; //����������� ����� ���� ������
	void Start(int rasstanovka); //����� ������ ����
	int IsEndGame(); //����� �������� ��������� ����
	int GetFirstPlayerCount(); /*�����, ������������ ���������� ��������� ������ ������� �����*/
	int GetSecondPlayerCount(); /*�����, ������������ ���������� ��������� ������ ������� (��) �����*/
	bool IsFirstPlayerMove(); //�����, ����������� ��� �� ������ 1
	bool IsSecondPlayerMove(); //�����, ����������� ��� �� ������ 2 (��)
	void ClearFirstPlayerField(); //����� ������� ���� ������ 1
	int FirstPlayerValue(int i, int j); //����� ��������� �������� ������ ���� ������ 1 
	int SecondPlayerValue(int i, int j); //����� ��������� �������� ������ ���� ������ 2 (��)
	bool FirstPlayerPlacement(int i, int j, int deckCount, bool direction); //����� ������� ���������� ������� �� ���� ������ 1
	cli::array<int>^ GetFirstPlayerKillCount(); //����� ��������� ����� ������ �������� ������� ���� �� ���� ������ 1
	cli::array<int>^ GetSecondPlayerKillCount(); //����� ��������� ����� ������ �������� ������� ���� �� ���� ������ 2
};


#pragma once
#include "Battlefield.h"
#include<iostream>

using namespace std;
using System::SerializableAttribute;
using namespace System::Threading;

[Serializable]
ref class Game //�����, ����������� ��� ����
{
	Battlefield PlayerField, CompField; //������� ���� ������ � ���� ��
	int endGame; //0 ���� ����, 1 ����� �������, 2 ��������� �������
	int playerCount; //����� ����� ������
	int compCount; //����� ����� ��
	bool playerMove; //���������� ����������, ���������� ��� ������
	bool compMove; //���������� ����������, ���������� ��� ��
	bool CompMove(); //����� ���� ����������
	void Run(); //�����-�������� ��� ������ ���� ����������
public:
	void Start(int rasstanovka); //����� ������ ����
	void PlayerMove(int i, int j); //����� ���� ������
	int IsEndGame(); //����� �������� ��������� ����
	int GetPlayerCount(); /*�����, ������������ ���������� ��������� ������� �����*/
	int GetCompCount(); /*�����, ������������ ���������� ��������� �� �����*/
	bool IsPlayerMove(); //�����, ����������� ��� �� ������
	bool IsCompMove(); //�����, ����������� ��� �� ��
	void ClearPlayerField(); //����� ������� ���� ������
	int PlayerValue(int i, int j); //����� ��������� �������� ������ ���� ������
	int CompValue(int i, int j); //����� ��������� �������� ������ ���� ��
	bool PlayerPlacement(int i, int j, int deckCount, bool direction); //����� ������� ���������� ������� �� ���� ������
	cli::array<int>^ GetPlayerKillCount(); //����� ��������� ����� ������ �������� ������� ���� �� ���� ������
	cli::array<int>^ GetCompKillCount(); //����� ��������� ����� ������ �������� ������� ���� �� ���� ��
};


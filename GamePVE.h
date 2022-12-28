#include "Game.h"

#pragma once
using System::SerializableAttribute;

[Serializable]
ref class GamePVE : public Game //�����, ����������� ��� ���� � ������ ����� ������ ��
{
public:
	bool PCMove(); //����� ���� ����������
	void PlayerMove(int i, int j) override; //����� ���� ������
	void Run(); //�����-�������� ��� ������ ���� ����������

};


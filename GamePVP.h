#pragma once
#include "Game.h"
using System::SerializableAttribute;

[Serializable]
ref class GamePVP : public Game //�����, ����������� ��� ���� � ������ ����� ������ ������
{
public:
	void PlayerMove(int i, int j) override; //����� ���� ������
};


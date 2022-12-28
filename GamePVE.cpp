#include "GamePVE.h"

/*����� ���� ����������
@return - 1, ���� ��� ���������� �������, 0, ���� ���*/
bool GamePVE::PCMove()
{
	secondPlayerCount++;
	srand(time(NULL));
	bool hit = 0; //���������� ���������� ���������� ��������� �� �������
	bool wound = 0; //���������� ���������� ���������� �������� ������
	bool horiz = 0; //���� ������ ������� �� �����������
	bool vert = 0; //���� ������ ������� �� ���������
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (firstPlayerField.GetValue(i, j) >= 9 && firstPlayerField.GetValue(i, j) <= 11) //���� ������ ��������� �������
			{
				wound = 1;
				//����� ������ �������� ����� ������� �� ���������
				if ((firstPlayerField.InField(i, j - 1) && firstPlayerField.GetValue(i, j - 1) >= 9 && firstPlayerField.GetValue(i, j - 1) <= 11)
					|| (firstPlayerField.InField(i, j + 1) && firstPlayerField.GetValue(i, j + 1) >= 9 && firstPlayerField.GetValue(i, j + 1) <= 11)
					|| (firstPlayerField.InField(i, j - 2) && firstPlayerField.GetValue(i, j - 2) >= 9 && firstPlayerField.GetValue(i, j - 2) <= 11)
					|| (firstPlayerField.InField(i, j + 2) && firstPlayerField.GetValue(i, j + 2) >= 9 && firstPlayerField.GetValue(i, j + 2) <= 11)
					|| (firstPlayerField.InField(i, j - 3) && firstPlayerField.GetValue(i, j - 3) >= 9 && firstPlayerField.GetValue(i, j - 3) <= 11)
					|| (firstPlayerField.InField(i, j + 3) && firstPlayerField.GetValue(i, j + 3) >= 9 && firstPlayerField.GetValue(i, j + 3) <= 11))
					vert = 1;
				//���� �� ��������� ������� �������� ������
				if (vert)
				{
					if (firstPlayerField.InField(i, j + 1) && firstPlayerField.GetValue(i, j + 1) <= 4 && firstPlayerField.GetValue(i, j + 1) != -2)
					{
						firstPlayerField.Fire(i, j + 1);
						firstPlayerField.TestKilled(i, j + 1);
						if (firstPlayerField.GetValue(i, j + 1) >= 8)
							hit = 1;
						goto exit;
					}
					if (firstPlayerField.InField(i, j - 1) && firstPlayerField.GetValue(i, j - 1) <= 4 && firstPlayerField.GetValue(i, j - 1) != -2)
					{
						firstPlayerField.Fire(i, j - 1);
						firstPlayerField.TestKilled(i, j - 1);
						if (firstPlayerField.GetValue(i, j - 1) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//����� ������ �������� ����� ������� �� �����������, ���� �� ������� �� ���������
				if ((firstPlayerField.InField(i - 1, j) && firstPlayerField.GetValue(i - 1, j) >= 9 && firstPlayerField.GetValue(i - 1, j) <= 11)
					|| (firstPlayerField.InField(i + 1, j) && firstPlayerField.GetValue(i + 1, j) >= 9 && firstPlayerField.GetValue(i + 1, j) <= 11)
					|| (firstPlayerField.InField(i - 2, j) && firstPlayerField.GetValue(i - 2, j) >= 9 && firstPlayerField.GetValue(i - 2, j) <= 11)
					|| (firstPlayerField.InField(i + 2, j) && firstPlayerField.GetValue(i + 2, j) >= 9 && firstPlayerField.GetValue(i + 2, j) <= 11)
					|| (firstPlayerField.InField(i - 3, j) && firstPlayerField.GetValue(i - 3, j) >= 9 && firstPlayerField.GetValue(i - 3, j) <= 11)
					|| (firstPlayerField.InField(i + 3, j) && firstPlayerField.GetValue(i + 3, j) >= 9 && firstPlayerField.GetValue(i + 3, j) <= 11))
					horiz = 1;
				if (horiz)
				{
					if (firstPlayerField.InField(i - 1, j) && firstPlayerField.GetValue(i - 1, j) <= 4 && firstPlayerField.GetValue(i - 1, j) != -2)
					{
						firstPlayerField.Fire(i - 1, j);
						firstPlayerField.TestKilled(i - 1, j);
						if (firstPlayerField.GetValue(i - 1, j) >= 8)
							hit = 1;
						goto exit;
					}
					if (firstPlayerField.InField(i + 1, j) && firstPlayerField.GetValue(i + 1, j) <= 4 && firstPlayerField.GetValue(i + 1, j) != -2)
					{
						firstPlayerField.Fire(i + 1, j);
						firstPlayerField.TestKilled(i + 1, j);
						if (firstPlayerField.GetValue(i + 1, j) >= 8)
							hit = 1;
						goto exit;
					}
				}
				//���� ������ �� ������� �������� ������
				if (horiz == 0 && vert == 0)
					while (1) //����������� ���� ��������� ���������� ����������� �����
					{
						int dir = rand() % 4; //0 �����, 1 ������, 2 ����, 3 �����
						if (dir == 0 && firstPlayerField.InField(i - 1, j) && firstPlayerField.GetValue(i - 1, j) <= 4 && firstPlayerField.GetValue(i - 1, j) != -2)
						{
							firstPlayerField.Fire(i - 1, j);
							firstPlayerField.TestKilled(i - 1, j);
							if (firstPlayerField.GetValue(i - 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 1 && firstPlayerField.InField(i, j + 1) && firstPlayerField.GetValue(i, j + 1) <= 4 && firstPlayerField.GetValue(i, j + 1) != -2)
						{
							firstPlayerField.Fire(i, j + 1);
							firstPlayerField.TestKilled(i, j + 1);
							if (firstPlayerField.GetValue(i, j + 1) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 2 && firstPlayerField.InField(i + 1, j) && firstPlayerField.GetValue(i + 1, j) <= 4 && firstPlayerField.GetValue(i + 1, j) != -2)
						{
							firstPlayerField.Fire(i + 1, j);
							firstPlayerField.TestKilled(i + 1, j);
							if (firstPlayerField.GetValue(i + 1, j) >= 8)
								hit = 1;
							goto exit;
						}
						if (dir == 3 && firstPlayerField.InField(i, j - 1) && firstPlayerField.GetValue(i, j - 1) <= 4 && firstPlayerField.GetValue(i, j - 1) != -2)
						{
							firstPlayerField.Fire(i, j - 1);
							firstPlayerField.TestKilled(i, j - 1);
							if (firstPlayerField.GetValue(i, j - 1) >= 8)
								hit = 1;
							goto exit;
						}
					}
			}
	//���� �� ���� �� ������� �������� �����
	if (wound == 0)
	{
		while (1)
		{
			// ������� ��������� ������� �� ������� ����
			int i = rand() % 10;
			int j = rand() % 10;
			//���������, ��� ����� ������� �������
			if ((firstPlayerField.GetValue(i, j) <= 4) && (firstPlayerField.GetValue(i, j) != -2))
			{
				firstPlayerField.Fire(i, j);
				firstPlayerField.TestKilled(i, j);
				if (firstPlayerField.GetValue(i, j) >= 8) {
					hit = 1;
				}
				break;
			}
		}
	}
exit:
	return hit;
}

/*����� ���� ������
@param i - ����� ������
@param j - ����� �������*/
void GamePVE::PlayerMove(int i, int j)
{
	firstPlayerCount++;
	secondPlayerField.Fire(i, j);
	secondPlayerField.TestKilled(i, j);
	Thread^ thread = gcnew Thread(gcnew ThreadStart(this, &GamePVE::Run)); //������� ����� �����, � ������� ����� ����������� ��� ��

	if (secondPlayerField.GetValue(i, j) < 8) //���� ����� �� �����
	{
		thread->Start(); //���������� �����
	}
}

//�����-�������� ��� ������ ���� ����������
void GamePVE::Run()
{
	Thread^ current = Thread::CurrentThread;
	firstPlayerMove = 0;
	secondPlayerMove = 1;
	while (secondPlayerMove)
	{
		current->Sleep(600); //������� ����� ����� ����� ��
		secondPlayerMove = PCMove(); //��� ��
	}
	firstPlayerMove = 1;
}

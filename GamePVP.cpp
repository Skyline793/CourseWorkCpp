#include "GamePVP.h"

/*����� ���� ������
@param i - ����� ������
@param j - ����� �������*/
void GamePVP::PlayerMove(int i, int j)
{
    if (IsFirstPlayerMove() && secondPlayerField.GetValue(i,j) >= -1 && secondPlayerField.GetValue(i, j) <= 4) //���� ����� ���� ������ 1 � ����� ����
    {
        firstPlayerCount++;
        secondPlayerField.Fire(i, j);
        secondPlayerField.TestKilled(i, j);
        if (secondPlayerField.GetValue(i, j) < 8) //���� ����� 1 �� �����
        {
            
            firstPlayerMove = 0;
            secondPlayerMove = 1;
        }
    }
    else if (IsSecondPlayerMove() && firstPlayerField.GetValue(i, j) >= -1 && firstPlayerField.GetValue(i, j) <= 4) //���� ����� ���� ������ 2 � ����� ����
    {
        secondPlayerCount++;
        firstPlayerField.Fire(i, j);
        firstPlayerField.TestKilled(i, j);
        if (firstPlayerField.GetValue(i, j) < 8) //���� ����� 2 �� �����
        {
            secondPlayerMove = 0;
            firstPlayerMove = 1;
        }
    }
}

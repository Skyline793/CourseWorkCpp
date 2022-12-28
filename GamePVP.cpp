#include "GamePVP.h"

/*метод хода игрока
@param i - номер строки
@param j - номер столбца*/
void GamePVP::PlayerMove(int i, int j)
{
    if (IsFirstPlayerMove()) //если время хода игрока 1
    {
        firstPlayerCount++;
        secondPlayerField.Fire(i, j);
        secondPlayerField.TestKilled(i, j);
        if (secondPlayerField.GetValue(i, j) < 8) //если игрок 1 не попал
        {
            
            firstPlayerMove = 0;
            secondPlayerMove = 1;
        }
    }
    else if (IsSecondPlayerMove()) //если время хода игрока 2
    {
        secondPlayerCount++;
        firstPlayerField.Fire(i, j);
        firstPlayerField.TestKilled(i, j);
        if (firstPlayerField.GetValue(i, j) < 8) //если игрок 2 не попал
        {
            secondPlayerMove = 0;
            firstPlayerMove = 1;
        }
    }
}

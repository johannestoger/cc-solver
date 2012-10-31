#include <iostream>
#include "Board.hpp"

int main()
{
    Board board("gamedata/board");

    for (int ii = 0; ii < 12; ii++)
    {
        board.barray(3, 4+ii) = ii;
    }

    cout << board << endl;
}

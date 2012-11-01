#include <iostream>

#include "Board.hpp"
#include "Piece.hpp"
#include "readpieces.hpp"

int main()
{
    Board board("gamedata/board");

    vector<vector<Piece> > pieces = readpieces();

    board.placePiece(pieces[6][1], 0, 0);
    board.placePiece(pieces[2][1], 0, 2);
    board.placePiece(pieces[7][2], 0, 4);
    board.placePiece(pieces[8][3], 0, 5);
    board.placePiece(pieces[3][3], 1, 0);
    board.placePiece(pieces[1][1], 1, 2);
    board.placePiece(pieces[10][2], 2, 0);
    board.placePiece(pieces[11][3], 3, 0);
    board.placePiece(pieces[9][7], 2, 2);
    board.placePiece(pieces[5][1], 2, 3);
    board.placePiece(pieces[0][2], 2, 5);
    board.placePiece(pieces[4][0], 3, 3);

    cout << endl;
    cout << board << endl;
}

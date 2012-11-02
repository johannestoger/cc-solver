#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <Eigen/Core>

#include "Piece.hpp"

using namespace std;

/*
   Stores a board, including placed pieces.
 */
class Board
{
    public:
        Board(string boardfilename = string("gamedata/board"));

        bool placePiece(Piece pc, int row, int col);

        /*
        The state of the board is stored in the array barray
        as follows:

        Value   Meaning
        0-11    Pieces A-L
        12      border/forbidden
        13      empty

        We add a buffer on the right and lower edges so that
        we can place pieces without taking care of the boundaries.
        */
        enum {BORDER = 12, EMPTY = 13};

        static const int rows = 14;
        static const int cols = 20;
        static const int buffer = 8;
        Matrix<int8_t, rows+buffer, cols+buffer> barray;

        /* Keep track of which pieces we have placed. */
        bool pieceplaced[12];
};

ostream& operator<<(ostream& os, const Board& p);

#endif

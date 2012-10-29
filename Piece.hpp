#ifndef PIECE_H
#define PIECE_H

#include "stdint.h"
#include "stdio.h"
#include <string>

#include "Eigen/Core"

using namespace Eigen;
using namespace std;

typedef Matrix<int16_t, Dynamic, Dynamic> MatrixXi16;

class Piece
{
    public:
        Piece();

        string name;
        uint8_t color; /* XX in \033[48;5;XXm (ANSI escape code) */
        MatrixXi16 shape;

        void rotate();  /* Rotate 90 degrees counter-clockwise */
        void flip();    /* Flip along vertical axis */
};

ostream& operator<<(ostream& os, Piece& p);

#endif

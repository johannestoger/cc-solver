#ifndef PIECE_H
#define PIECE_H

#include "stdint.h"
#include "stdio.h"
#include <string>

#include "Eigen/Core"

using namespace Eigen;
using namespace std;

typedef Matrix<int8_t, Dynamic, Dynamic> MatXi8;

class Piece
{
    public:
        Piece();

        string name;
        uint8_t color; /* XX in \033[48;5;XXm (ANSI escape code) */
        MatXi8 shape;

        void rot90();  /* Rotate 90 degrees counter-clockwise */
        void flip();    /* Flip along vertical axis */

        bool operator<(const Piece& rhs) const;
        bool operator==(const Piece& rhs) const;
};

ostream& operator<<(ostream& os, const Piece& p);

#endif

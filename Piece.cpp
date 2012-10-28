#include <iostream>

#include "Piece.hpp"

Piece::Piece()
{
    shape = MatrixXi16::Zero(8,5);
    color = 10;
}

void Piece::rotate()
{
    /* TODO: Do this for real. */
    shape.transposeInPlace();
}

ostream& operator<<(ostream& os, Piece& p)
{
    char colbuf[100];
    sprintf(colbuf, "\033[48;5;%im", p.color);
    string ansicolor(colbuf);

    for(int row = 0; row < p.shape.rows(); row++)
    {
        for(int col = 0; col < p.shape.cols(); col++)
        {
            if (p.shape(row,col) == 0)
                os << ' ';
            else
                os << ansicolor << "." << "\033[0m";
        }

        os << std::endl;
    }

    return os;
}

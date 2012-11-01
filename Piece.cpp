#include <iostream>

#include "Piece.hpp"

Piece::Piece()
{
    shape = MatXi8::Zero(8,5);
    color = 10;
    number = 0;
}

void Piece::flip()
{
    MatXi8 tmp = shape.colwise().reverse();
    shape = tmp;
}

void Piece::rot90()
{
    MatXi8 tmp1 = shape.transpose();
    MatXi8 tmp2 = tmp1.colwise().reverse();
    shape = tmp2;
}

bool Piece::operator<(const Piece& rhs) const
{
    Matrix<uint8_t, 5*8, 1> sortvector;
    int dr = shape.rows() - rhs.shape.rows();
    if (dr < 0)
        return true;
    else if (dr > 0)
        return false;

    int dc = shape.cols() - rhs.shape.cols();
    if (dc < 0)
        return true;
    else if (dr > 0)
        return false;

    /* Matrices have the same size, check elements */
    int mm = shape.rows();
    int nn = shape.cols();

    for (int ii = 0; ii < mm; ii++)
        for (int jj = 0; jj < nn; jj++)
            if (shape(ii,jj) < rhs.shape(ii,jj))
                return true;
            else if (shape(ii,jj) > rhs.shape(ii,jj))
                return false;

    /* *this and rhs are equal */
    return false;
}

bool Piece::operator==(const Piece& rhs) const
{
    if (shape.cols() != rhs.shape.cols())
        return false;

    if (shape.rows() != rhs.shape.rows())
        return false;

    for (int ii = 0; ii < shape.rows(); ii++)
        for (int jj = 0; jj < shape.cols(); jj++)
            if (shape(ii,jj) != rhs.shape(ii,jj))
                return false;

    return true;
}

ostream& operator<<(ostream& os, const Piece& p)
{
    char colbuf[100];
    sprintf(colbuf, "\033[48;5;%im", p.color);
    string ansicolor(colbuf);

    for(int row = 0; row < p.shape.rows(); row++)
    {
        for(int col = 0; col < p.shape.cols(); col++)
        {
            if (p.shape(row,col) == 0)
                os << "  ";
            else if (row == 2 && col == 2)
                os << ansicolor << "oo" << "\033[0m";
            else
                os << ansicolor << "  " << "\033[0m";

        }

        os << std::endl;
    }

    return os;
}

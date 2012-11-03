#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Board.hpp"
#include "colors.hpp"

using namespace std;

const int Board::rows;
const int Board::cols;
const int Board::buffer;

Board::Board(string boardfilename)
{
    barray.setConstant(BORDER);

    ifstream boardfile(boardfilename.c_str());

    // Read shape of the board from file
    int row = 0;
    char linebuf[100];
    while(boardfile.getline(linebuf, 100) && row < 14)
    {
        string line(linebuf);
        for(int col = 0; col < min(20, (int)line.length()); col++)
        {
            if (line.at(col) == 'X')
                barray(row, col) = BORDER;
            else
                barray(row, col) = EMPTY;
        }
        row++;
    }

    for (int ii = 0; ii < 12; ii++)
        pieceplaced[ii] = false;
}

bool Board::placePiece(Piece pc, int crow, int ccol)
{
    /*
     * crow, ccol: coarse row, col. Corresponds to the dots
     * in gamedata/board.
     *
     * If the piece Piece can be placed at (row,col),
     * change the state of the board and return true.
     *
     * Otherwise, the board remains unchanged and false
     * is returned.
     *
     * */

    /* Test if the piece can be placed. */
    if (pieceplaced[pc.number])
        return false;

    int m = pc.shape.rows();
    int n = pc.shape.cols();

    for (int ii = 0; ii < m; ii++)
    {
        for (int jj = 0; jj <n; jj++)
        {
            int row = 3*crow+ii;
            int col = 3*ccol+jj;
            if (pc.shape(ii,jj) == 1 && barray(row,col) != Board::EMPTY)
                return false; // collision found.
        }
    }

    // Piece fits, place it
    for (int ii = 0; ii < m; ii++)
    {
        for (int jj = 0; jj <n; jj++)
        {
            int row = 3*crow+ii;
            int col = 3*ccol+jj;
            if (pc.shape(ii,jj) == 1)
                barray(row,col) = pc.number;
        }
    }
    pieceplaced[pc.number] = true;

    return true;
}

bool Board::isFull()
{
    bool full = true;
    for (int ii = 0; ii < 12; ii++)
        full = full && pieceplaced[ii];

    return full;
}

Matrix<int8_t, 4, 6> Board::freeSpaces()
{
    Matrix<int8_t, 4, 6> freesp;

    for (int crow = 0; crow < 4; crow++)
        for (int ccol = 0; ccol < 6; ccol++)
            if (barray(2+3*crow, 2+3*ccol) == EMPTY)
                freesp(crow,ccol) = 0;
            else
                freesp(crow,ccol) = 1;

    return freesp;
}

bool Board::operator<(const Board& rhs) const
{
    Matrix<uint8_t, 5*8, 1> sortvector;
    int dr = barray.rows() - rhs.barray.rows();
    if (dr < 0)
        return true;
    else if (dr > 0)
        return false;

    int dc = barray.cols() - rhs.barray.cols();
    if (dc < 0)
        return true;
    else if (dr > 0)
        return false;

    /* Matrices have the same size, check elements */
    int mm = barray.rows();
    int nn = barray.cols();

    for (int ii = 0; ii < mm; ii++)
        for (int jj = 0; jj < nn; jj++)
            if (barray(ii,jj) < rhs.barray(ii,jj))
                return true;
            else if (barray(ii,jj) > rhs.barray(ii,jj))
                return false;

    /* *this and rhs are equal */
    return false;
}

bool Board::operator==(const Board& rhs) const
{
    if (barray.cols() != rhs.barray.cols())
        return false;

    if (barray.rows() != rhs.barray.rows())
        return false;

    for (int ii = 0; ii < barray.rows(); ii++)
        for (int jj = 0; jj < barray.cols(); jj++)
            if (barray(ii,jj) != rhs.barray(ii,jj))
                return false;

    return true;
}

ostream& operator<<(ostream& os, const Board& board)
{
    for(int row = 0; row < board.rows; row++)
    {
        for(int col = 0; col < board.cols; col++)
        {
            uint8_t thissq = board.barray(row,col);
            switch (thissq)
            {
                case Board::EMPTY:
                    os << "  "; break;
                case Board::BORDER:
                    os << "XX"; break;
                default:
                    if (thissq <= 11)
                    {
                        char colbuf[20];
                        sprintf(colbuf, "\033[48;5;%im", COLORS[thissq]);
                        string ansicolor(colbuf);
                        os << ansicolor << "  " << "\033[0m";
                    }
            }
        }
        os << std::endl;
    }

    return os;
}


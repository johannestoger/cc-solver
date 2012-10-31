#include <fstream>
#include <iostream>

#include "Board.hpp"
#include "colors.hpp"

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

const int Board::rows;
const int Board::cols;
const int Board::buffer;

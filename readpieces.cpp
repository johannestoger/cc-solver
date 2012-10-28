/*
 * Read pieces from text files, and do some operations on them.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Core"

#include "Piece.hpp"

using namespace std;

int main()
{
    int N_pieces = 12;
    string piecenames("ABCDEFGHIJKL");

    vector<Piece> pieces(N_pieces);

    for (int ii = 0; ii < N_pieces; ii++)
    {
        Piece pbuf;
        pbuf.name = piecenames.at(ii);
        char linebuf[100];

        // Read piece from file
        ostringstream filename;
        filename << "gamedata/" << piecenames.at(ii);

        cout << filename.str() << endl;
        ifstream piecefile(filename.str().c_str());

        // First line is symmetry info
        piecefile.getline(linebuf, 100);
        cout << linebuf << endl;

        // Second line: ANSI color
        piecefile.getline(linebuf, 100);
        istringstream colstream(linebuf);
        int color;
        colstream >> color;
        pbuf.color = color;
        cout << "Color: " << (int)pbuf.color << endl;

        // The rest of the file is the shape of the piece
        int row = 0;
        while(piecefile.getline(linebuf, 100) && row < 9)
        {
            string line(linebuf);

            for(int col = 0; col < min(5, (int)line.length()); col++)
            {
                if (line.at(col) == ' ')
                    pbuf.shape(row, col) = 0;
                else
                    pbuf.shape(row, col) = ii+1;
            }
            row++;
        }
        piecefile.close();

        pbuf.rotate();
        cout << pbuf;
        cout << endl;
    }
}


/*
 * Read pieces from text files, and do some operations on them.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Eigen/Core"

#include "Piece.hpp"

using namespace std;

Piece readpiecefromfile(string filename);

int main()
{
    int N_pieces = 12;
    string piecenames("ABCDEFGHIJKL");

    // Read pieces from files
    for (int ii = 0; ii < N_pieces; ii++)
    {
        ostringstream filename;
        filename << "gamedata/" << piecenames.at(ii);

        cout << filename.str() << endl;

        Piece pbuf = readpiecefromfile(filename.str());
        pbuf.name = piecenames.at(ii);

        set<Piece> pset;

        pset.insert(pbuf);
        for (int kk = 0; kk < 3; kk++)
        {
            pbuf.rot90();
            pset.insert(pbuf);
        }
        pbuf.flip();
        pset.insert(pbuf);
        for (int kk = 0; kk < 3; kk++)
        {
            pbuf.rot90();
            pset.insert(pbuf);
        }

        for (set<Piece>::iterator sit = pset.begin(); sit != pset.end(); sit++)
            cout << *sit << endl;
    }
}

Piece readpiecefromfile(string filename)
{
    ifstream piecefile(filename.c_str());

    Piece pbuf;
    char linebuf[100];

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
                pbuf.shape(row, col) = 1;
        }
        row++;
    }
    piecefile.close();

    return pbuf;
}

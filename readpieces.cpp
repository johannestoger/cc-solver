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

#include "Colors.hpp"
#include "Piece.hpp"

using namespace std;

Piece readpiecefromfile(string filename);
vector<vector<Piece> > readpieces();

int main()
{
    vector<vector<Piece> > pieces = readpieces();
    for (int ii = 0; ii < pieces.size(); ii++)
    {
        for (int jj = 0; jj < pieces[ii].size(); jj++)
        {
            Piece thispiece = pieces[ii][jj];
            cout << thispiece.name << jj << endl;
            cout << thispiece;
            cout << endl;
        }
    }
}

vector<vector<Piece> > readpieces()
{
    int N_pieces = 12;
    string piecenames("ABCDEFGHIJKL");
    //int colors[] = {208, 196, 17, 212, 22, 15, 14, 127, 226, 53, 46, 240};

    vector<vector<Piece> > pieces(N_pieces, vector<Piece>());

    for (int ii = 0; ii < N_pieces; ii++)
    {
        // Read piece from files
        ostringstream filename;
        filename << "gamedata/" << piecenames.at(ii);

        Piece pbuf = readpiecefromfile(filename.str());
        pbuf.name = piecenames.at(ii);
        pbuf.color = COLORS[ii];

        // Find all rotations, flips etc.
        // This relies on std::set, Piece::operator<() and operator==().
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

        pieces[ii].assign(pset.begin(), pset.end());
    }

    return pieces;
}

Piece readpiecefromfile(string filename)
{
    ifstream piecefile(filename.c_str());

    Piece pbuf;
    char linebuf[100];

    // Read shape of the piece from file
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

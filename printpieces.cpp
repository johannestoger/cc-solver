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

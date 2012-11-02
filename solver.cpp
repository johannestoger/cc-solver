#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <utility>

#include "Board.hpp"
#include "Piece.hpp"
#include "readstuff.hpp"

using namespace std;

vector<vector<Piece> > pieces;

int tries;

void solve(Board board, set<Board>& visited)
{
    /* Don't go down this path if we've already been here. */
    if (visited.find(board) != visited.end())
        return;
    else
        visited.insert(board);

    /* See if this is a solution */
    if (board.isFull())
    {
        cout << board << endl;
    }

    /* Check free spaces */
    vector<pair<int,int> > freesp = board.freeSpaces();

    /* TODO:
     *
     * 1. Check if there are any isolated coarse blocks.
     * 2. Check if there are any isolated fine blocks.
     * 3. Find more things that we can exit on early.
     * 4. Find 'constraints' and save them in some way - i.e. if piece X
     *    is placed here, then piece Y must be over there.
     * 5. Save something smaller than the full Board object in
     *    the visited cache to save space.
     *
     * */

    /* For each free space, try to place all possible pieces
     * and orientations. Recurse on all feasible placements. */
    for (int ii = 0; ii < 12; ii++)
    {
        if (board.pieceplaced[ii]) // don't place a piece twice
            continue;

        bool couldplacepiece = false;

        // for all piece orientations
        for (int jj = 0; jj < pieces[ii].size(); jj++)
        {
            // for all empty spaces
            for (int kk = 0; kk < freesp.size(); kk++)
            {
                tries++;
                int crow = freesp[kk].first;
                int ccol = freesp[kk].second;

                Board tryboard = board;
                bool pieceok =
                    tryboard.placePiece(pieces[ii][jj], crow, ccol);

                if (pieceok) // recurse
                {
                    couldplacepiece = true;
                    solve(tryboard, visited);
                }
            }
        }

        if (!couldplacepiece)
            break;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << endl;
        cout << "Please specify a board file to solve." << endl;
        cout << "Usage: solve <filename>" << endl;
        return 0;
    }

    pieces = readpieces();

    /* First argument is the file name. */
    string filename(argv[1]);
    Board startboard = readboard(filename);

    cout << endl << filename << endl << endl;
    cout << startboard << endl;

    tries = 0;
    set<Board> visited;
    solve(startboard, visited);

    cout << "Done. Tried " << tries << " positions, recursed on " << visited.size() << "." << endl;
}


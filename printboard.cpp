#include <fstream>
#include <iostream>
#include <string>

#include "Board.hpp"
#include "Piece.hpp"
#include "readstuff.hpp"

/*
 * Command line: printboard <filename>
 * */

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << endl;
        cout << "Please specify a board file to print." << endl;
        cout << "Usage: printboard <filename>" << endl;
        return 0;
    }

    /* First argument is the file name. */
    string filename(argv[1]);
    Board board = readboard(filename);

    cout << board << endl;
}

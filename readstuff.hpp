#ifndef READSTUFF_HPP
#define READSTUFF_HPP

#include <string>
#include <vector>

#include "Board.hpp"
#include "Piece.hpp"

vector<vector<Piece> > readpieces();
Board readboard(string filename);

#endif

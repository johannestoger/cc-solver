COMPILER=clang++
EIGEN=../eigen

default: all

all: piecenames

piecenames: readpieces.cpp Piece.cpp Piece.hpp
	${COMPILER} -Wall -I${EIGEN} -O2 readpieces.cpp Piece.cpp -o readpieces

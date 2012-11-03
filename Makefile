COMPILER=clang++
EIGEN=../eigen

COMPILE=${COMPILER} -Wall -O3 -I${EIGEN}

default: all

all: printpieces printboard solver

%.o: %.cpp
	${COMPILE} -c $<

printpieces: colors.o Board.o Piece.o readstuff.o printpieces.o
	${COMPILE} $^ -o printpieces

printboard: printboard.o colors.o Piece.o Board.o readstuff.o
	${COMPILE} $^ -o printboard

solver: colors.o Piece.o Board.o readstuff.o solver.o
	${COMPILE} $^ -o solver

clean:
	rm -f *.o
	rm -f printpieces
	rm -f testboard
	rm -f printboard

# Compiles with g++ 4.2 or clang++ 3.1 (and probably some more)
COMPILER=clang++

# Eigen 3.0, http://eigen.tuxfamily.org
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
	rm -f printboard
	rm -f solver

COMPILER=clang++
EIGEN=../eigen

COMPILE=${COMPILER} -Wall -O2 -I${EIGEN}

default: all

all: printpieces printboard

%.o: %.cpp
	${COMPILE} -c $<

printpieces: colors.o Board.o Piece.o readstuff.o printpieces.o
	${COMPILE} $^ -o printpieces

printboard: printboard.o colors.o Piece.o Board.o readstuff.o
	${COMPILE} $^ -o printboard

clean:
	rm -f *.o
	rm -f printpieces
	rm -f testboard
	rm -f printboard

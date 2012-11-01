COMPILER=clang++
EIGEN=../eigen

COMPILE=${COMPILER} -Wall -O2 -I${EIGEN}

default: all

all: printpieces testboard

%.o: %.cpp
	${COMPILE} -c $<

printpieces: colors.o Piece.o readpieces.o printpieces.o
	${COMPILE} $^ -o printpieces

testboard: colors.o testboard.o Piece.o Board.o readpieces.o
	${COMPILE} $^ -o testboard

clean:
	rm -f *.o
	rm -f printpieces
	rm -f testboard

COMPILER=clang++
EIGEN=../eigen

COMPILE=${COMPILER} -Wall -O2 -I${EIGEN}

default: all

all: readpieces testboard

%.o: %.cpp
	${COMPILE} -c $<

readpieces: colors.o Piece.o readpieces.o
	${COMPILE} $^ -o readpieces

testboard: colors.o testboard.o Board.o
	${COMPILE} $^ -o testboard

clean:
	rm -f *.o
	rm -f readpieces
	rm -f testboard

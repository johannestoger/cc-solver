COMPILER=clang++
EIGEN=../eigen

COMPILE=${COMPILER} -Wall -O2 -I${EIGEN}

default: all

all: readpieces

%.o: %.cpp
	${COMPILE} -c $<

readpieces: Piece.o readpieces.o
	${COMPILE} $? -o readpieces

clean:
	rm -f *.o
	rm -f readpieces

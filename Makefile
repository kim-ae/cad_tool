CC = g++
CFLAGS = -c -Wall
NOUSEDFLAG=-Wunused-variable
STD = -std=c++11

all: cad

cad: aig.o aagReader.o main.o
	${CC} aig.o aagReader.o main.o -o cad_tool
	rm *.o

aig.o:
	${CC} ${STD} ${CFLAGS} ${NOUSEDFLAG} src/aig.cpp

aagReader.o:
	${CC} ${STD} ${CFLAGS} ${NOUSEDFLAG} src/aagReader.cpp

main.o:
	${CC} ${STD} ${CFLAGS} ${NOUSEDFLAG} src/main.cpp
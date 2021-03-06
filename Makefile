CC = g++
CFLAGS = -c -Wall
NOUSEDFLAG=-c -Wunused-variable
STD = -std=c++11

all: cad

cad: aig.o aagReader.o aigBuilder.o main.o
	${CC} aig.o aagReader.o aigBuilder.o main.o -o cad_tool
	rm *.o

aig.o:
	${CC} ${STD} ${NOUSEDFLAG} src/aig.cpp

aagReader.o:
	${CC} ${STD} ${NOUSEDFLAG} src/aagReader.cpp

aigBuilder.o:
	${CC} ${STD} ${NOUSEDFLAG} src/aigBuilder.cpp

main.o:
	${CC} ${STD} ${NOUSEDFLAG} src/main.cpp


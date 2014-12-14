CC = g++
CFLAGS = -c -Wall
NOUSEDFLAG=-c -Wunused-variable
STD = -std=c++11

all: cad

cad: path.o aig.o aagReader.o main.o
	${CC} path.o aig.o aagReader.o main.o -o cad_tool
	rm *.o
path.o:
	${CC} ${STD} ${NOUSEDFLAG} src/path.cpp

aig.o:
	${CC} ${STD} ${NOUSEDFLAG} src/aig.cpp

aagReader.o:
	${CC} ${STD} ${NOUSEDFLAG} src/aagReader.cpp

main.o:
	${CC} ${STD} ${NOUSEDFLAG} src/main.cpp


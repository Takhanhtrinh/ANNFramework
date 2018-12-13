CC = gcc 
FLAG = -g -Wall 
matrix: matrix.cpp 
	$(CC) $(FLAG) -c matrix.cpp -o matrix.o

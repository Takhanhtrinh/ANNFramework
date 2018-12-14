CC = gcc 
FLAG = -g -Wall 
MATRIX_C = matrix.c
TEST_MATRIX = testMatrix.c 
matrix.o: $(MATRIX_C)
	$(CC) $(FLAG) -c $(MATRIX_C) -o matrix.o
testMatrix: matrix.o $(TEST_MATRIX)
	$(CC) $(FLAG) $(TEST_MATRIX) -o testMatrix matrix.o
clean:
	rm *.o

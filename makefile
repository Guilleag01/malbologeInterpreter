CC = gcc

compilar: malbolge.c
	clear

	$(CC) malbolge.c -o malbolge.out -lm
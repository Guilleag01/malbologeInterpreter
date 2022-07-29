CC = gcc

compilar: malbolge.c
	clear

	$(CC) malbolge.c -o malbolge.out -lm
	$(CC) createCode.c -o createCode.out
all:
	gcc -Wall -g -o main *.c

valgrind:
	valgrind --track-origins=yes --leak-check=full ./main
WWW = -std=c11 -pedantic -Wall -Werror -Wextra

all: s21_grep

s21_grep: grep.o main.o
	gcc $(WWW) main.o grep.o -o ../../build/s21_grep

grep.o: grep.c
	gcc $(WWW) -c grep.c

main.o: main.c
	gcc $(WWW) -c main.c

clean:
	rm -rf *.o main
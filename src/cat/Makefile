WWW = -std=c11 -pedantic -Wall -Werror -Wextra

all: s21_cat

s21_cat: cat.o main.o
	gcc $(WWW) main.o cat.o -o ../../build/s21_cat

cat.o: cat.c
	gcc $(WWW) -c cat.c

main.o: main.c
	gcc $(WWW) -c main.c

clean:
	rm -rf *.o main

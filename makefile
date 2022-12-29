gra2048: gra2048.c main.c
	gcc -o gra2048 gra2048.o main.o -lncurses -lm

gra2048.o: gra2048.c gra2048.h
	gcc -c gra2048.c

main.o: main.c gra2048.h
	gcc -c main.c

clean:
	rm gra2048.o main.o gra2048

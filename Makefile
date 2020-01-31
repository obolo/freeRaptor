test: test.c gf2matrix.o raptor10.o
	gcc -std=c11 -I. -L. -lm -o test test.c gf2matrix.o	

gf2matrix.o: gf2matrix.h gf2matrix.c
	gcc -c gf2matrix.c -I.

raptor10.o: raptor10.h raptor10.c gf2matrix.o
	gcc -c raptor10.c gf2matrix.c -I.

clean:
	rm test

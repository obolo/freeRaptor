test: raptor10.o gf2matrix.o raptor_consts.o
	gcc -std=c11 -I. -L. -g -o test test.c raptor10.o raptor_consts.o gf2matrix.o -lm

raptor10.o: raptor10.c raptor_consts.c
	gcc -c -g -fPIC gf2matrix.c raptor_consts.c raptor10.c -I. -lm

gf2matrix.o: gf2matrix.c
	gcc -c -g -fPIC gf2matrix.c -I. -lm

clean:
	rm test raptor10.o gf2matrix.o

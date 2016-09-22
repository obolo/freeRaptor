<<<<<<< HEAD
test: test_raptor1.cpp LT.cpp Rcodec.cpp
	g++ -std=c++11 -g -o test test_raptor1.cpp LT.cpp Rcodec.cpp -I.
=======
test: test_raptor.cpp LT.cpp Rcodec.cpp
	g++ -g -std=c++11 -o test test_raptor.cpp LT.cpp Rcodec.cpp -I.

>>>>>>> c38989e3b7da3058f7d255fdf66c26313b7413ba
clean:
	rm -f test

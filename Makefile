test: test_raptor.cpp LT.cpp Rcodec.cpp
	g++ -g -std=c++11 -o test test_raptor.cpp LT.cpp Rcodec.cpp -I.

clean:
	rm -f test

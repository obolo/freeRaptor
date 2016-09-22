test: test_raptor1.cpp LT.cpp Rcodec.cpp
	g++ -std=c++11 -g -o test test_raptor1.cpp LT.cpp Rcodec.cpp -I.
clean:
	rm -f test

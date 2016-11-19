test: test_libR10.cpp libR10.cpp
	g++ -std=c++11 -I/usr/local/include -L/usr/local/lib -g -o test_libR10 test_libR10.cpp libR10.cpp -I.

clean:
	rm -f test_libR10

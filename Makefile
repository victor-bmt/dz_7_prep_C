a.out : main.o testString.o
	g++ -std=gnu++11 main.o testString.o -o a.out 

main.o : main.cpp testString.h
	g++ -std=gnu++11 -c main.cpp

testString.o : testString.cpp testString.h
	g++ -std=gnu++11 -c testString.cpp



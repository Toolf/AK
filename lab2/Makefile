CXX = g++

CFLAGS = -c -Wall

.PHONY all: lab2

lab2: main.o Lexer.o
	$(CXX) main.o Lexer.o -o lab2

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp

Lexer.o:
	$(CXX) $(CFLAGS) Lexer.cpp

clean:
	rm -rf *.o lab2

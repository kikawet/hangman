
SOURCES=libs/Timer.h libs/WordMap.h libs/WordMap.cpp

build/hangman: build main.cpp $(SOURCES)
	g++ -Wall -Wextra -Wpedantic -std=c++17 main.cpp $(SOURCES) -o build/hangman

build:
	mkdir -p build
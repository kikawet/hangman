
SOURCES=libs/IWordMap.h libs/Timer.h libs/WordMap_MultiMap.h libs/WordMap_MultiMap.cpp libs/WordMap_Vector.cpp

build/hangman: build main.cpp $(SOURCES)
	g++ -Wall -Wextra -Wpedantic -std=c++17 main.cpp $(SOURCES) -o build/hangman

build:
	mkdir -p build
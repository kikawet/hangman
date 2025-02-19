cmake_minimum_required(VERSION 3.31)

project(HANGMAN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3")
# add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3)


include_directories(HANGMAN src)

# HANGMAN
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(hangman main.cpp ${SOURCES})


# TESTS
file(GLOB TST_SOURCES "test/*.cpp")
add_executable(test EXCLUDE_FROM_ALL test/main.c ${TST_SOURCES} ${SOURCES})

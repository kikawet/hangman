
#include <istream>
#include <string>
#include <vector>
#include "Random.h"

#ifndef GAME_H
#define GAME_H

#ifndef ALPHABET
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#endif // ALPHABET

class Game
{
public:
    Game() = delete;
    Game(const std::vector<std::string> &lexicon);
    ~Game();

    bool guess(char c);
    int get_total_guess();
    std::vector<char> guesses();
    std::string guessed(char unkown = '_');

private:
    int total_guess;
    bool *alphabet_guessed;
    std::string alphabet;
    std::string solution;
    Random rand;
};

std::vector<std::string> loadLexicon(std::string lexiconPath);
bool validate_word(const std::string &word, const std::string &alphabet, std::size_t *err_pos);

#endif // GAME_H


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
    std::size_t get_failed_count();
    std::vector<char> guesses();
    std::string guessed(char unkown = '_');
    std::string_view give_up();

private:
    std::size_t failed_count;
    std::size_t success_count;
    bool *alphabet_guessed;
    std::string alphabet;
    std::string solution;
    Random rand;
};

std::vector<std::string> loadLexicon(std::string lexiconPath);
bool validate_word(const std::string &word, const std::string &alphabet, std::size_t *err_pos);

constexpr const std::string_view hangman_visuals [] = {
    "   ╭───╮  \n"
    "   │   │  \n"
    "       │  \n"
    "       │  \n"
    "       │  \n"
    "       │  \n"
    " ══════╧══\n",

    "   ╭───╮  \n"
    "   │   │  \n"
    "   @   │  \n"
    "       │  \n"
    "       │  \n"
    "       │  \n"
    " ══════╧══\n",

    "   ╭───╮  \n"
    "   │   │  \n"
    "   @   │  \n"
    "   │   │  \n"
    "       │  \n"
    "       │  \n"
    " ══════╧══\n",

    "   ╭───╮  \n"
    "   │   │  \n"
    "   @   │  \n"
    "  🯑│   │  \n"
    "       │  \n"
    "       │  \n"
    " ══════╧══\n",

    "   ╭───╮  \n"
    "   │   │  \n"
    "   @   │  \n"
    "  🯑│🯒  │  \n"
    "       │  \n"
    "       │  \n"
    " ══════╧══\n",

    "   ╭───╮  \n"
    "   │   │  \n"
    "   @   │  \n"
    "  🯑│🯒  │  \n"
    "  🯑    │  \n"
    "       │  \n"
    " ══════╧══\n",

    "   ╭───╮  \n"
    "   │   │  \n"
    "   @   │  \n"
    "  🯑│🯒  │  \n"
    "  🯑 🯒  │  \n"
    "       │  \n"
    " ══════╧══\n"
};

#endif // GAME_H

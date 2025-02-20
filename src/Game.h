
#include <istream>
#include <string>
#include <vector>
#include "Random.h"

#ifndef GAME_H
#define GAME_H

#ifndef ALPHABET
#define ALPHABET U"ABCDEFGHIJKLMNOPQRSTUVWXYZÑÁÉÍÓÚÜ"
#endif // ALPHABET

class Game
{
public:
    Game() = delete;
    Game(const std::vector<std::u32string> &lexicon);
    ~Game();

    bool guess(char32_t c);
    std::size_t get_failed_count();
    std::vector<char32_t> guesses();
    std::u32string guessed(char32_t unkown = '_');
    std::u32string give_up();

private:
    std::size_t failed_count;
    std::size_t success_count;
    bool *alphabet_guessed;
    std::u32string alphabet;
    std::u32string solution;
    Random rand;
};

std::vector<std::u32string> loadLexicon(std::string lexiconPath);
bool validate_word(const std::u32string &word, const std::u32string &alphabet, std::size_t *err_pos);

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

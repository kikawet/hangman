
#include <fstream>
#include <algorithm>
#include <iostream>
#include <codecvt>
#include <locale>
#include "Game.h"

Game::Game(const std::vector<std::u32string> &lexicon) : failed_count(0),
                                                         success_count(0),
                                                         alphabet(ALPHABET),
                                                         solution(),
                                                         rand()
{
    if (lexicon.empty())
        throw std::runtime_error("Unable to initialize Game with empty lexicon");

    for (const std::u32string &word : lexicon)
        if (!validate_word(word, alphabet, nullptr))
            throw std::runtime_error("Invalid lexicon does not match alphabet");

    solution = rand.next_item(lexicon);

    alphabet_guessed = new bool[alphabet.size()];
    for (std::size_t i = 0; i < alphabet.size(); i++)
        alphabet_guessed[i] = false;
}

Game::~Game()
{
    if (alphabet_guessed != nullptr)
    {
        delete[] alphabet_guessed;
        alphabet_guessed = nullptr;
    }
}

void throw_u32string(std::u32string msg)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    throw std::runtime_error(converter.to_bytes(msg));
}

bool Game::guess(char32_t c)
{
    if (success_count == solution.size())
        return true;

    bool valid = false;
    for (std::size_t i = 0; i < alphabet.size(); i++)
        if (alphabet[i] == c)
        {
            if (alphabet_guessed[i])
                return false;

            alphabet_guessed[i] = true;
            valid = true;
        }

    if (!valid)
        throw_u32string(U"Invalid character " + std::u32string(1, c));

    bool in_solution = false;
    for (std::size_t i = 0; i < solution.size(); i++)
    {
        if (solution[i] == c)
        {
            success_count++;
            in_solution = true;
        }
    }

    if (in_solution && success_count == solution.size())
        return true;

    if (!in_solution)
        failed_count++;

    return false;
}

std::size_t Game::get_failed_count()
{
    return failed_count;
}

std::vector<char32_t> Game::guesses()
{
    std::vector<char32_t> checked;
    checked.reserve(alphabet.size());

    for (std::size_t i = 0; i < alphabet.size(); i++)
        if (alphabet_guessed[i])
            checked.push_back(alphabet[i]);

    return checked;
}

std::u32string Game::guessed(char32_t unkown)
{
    for (std::size_t i = 0; i < alphabet.size(); i++)
        if (alphabet[i] == unkown)
            throw_u32string(U"Unable to generate guessed because '" + std::u32string(1, unkown) + U"' is in the alphabet");

    std::u32string hidden(solution);

    for (std::size_t i = 0; i < solution.size(); i++)
    {
        if (hidden[i] == unkown)
            continue;

        bool cover = false;
        for (std::size_t j = 0; j < alphabet.size(); j++)
            if (hidden[i] == alphabet[j])
            {
                cover = alphabet_guessed[j];
                break;
            }

        if (!cover)
            for (std::size_t j = i; j < hidden.size(); j++)
                if (hidden[j] == solution[i])
                    hidden[j] = unkown;
    }

    return hidden;
}

std::u32string Game::give_up()
{
    return solution;
}

bool validate_word(const std::u32string &word, const std::u32string &alphabet, std::size_t *err_pos)
{
    for (std::size_t i = 0; i < word.size(); i++)
    {
        bool found = false;
        for (std::size_t j = 0; j < alphabet.size(); j++)
            if (word[i] == alphabet[j])
            {
                found = true;
                break;
            }

        if (!found)
        {
            if (err_pos)
                *err_pos = i;
            return false;
        }
    }

    return true;
}

std::vector<std::u32string> loadLexicon(std::string lexiconPath)
{
    std::ifstream file(lexiconPath);
    std::vector<std::u32string> lexicon;

    if (!file.is_open())
        throw std::runtime_error("Error opening file: " + lexiconPath);

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::string word;

    while (!file.eof())
    {
        file >> word;
        lexicon.emplace_back(converter.from_bytes(word));
    }

    return lexicon;
}

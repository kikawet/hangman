
#include "Game.h"
#include <fstream>
#include <algorithm>
#include <iostream>

Game::Game(const std::vector<std::string> &lexicon) : failed_count(0),
                                                      success_count(0),
                                                      alphabet(ALPHABET),
                                                      solution(),
                                                      rand()
{
    if (lexicon.empty())
        throw std::runtime_error("Unable to initialize Game with empty lexicon");

    for (const std::string &word : lexicon)
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

bool Game::guess(char c)
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
        throw std::runtime_error("Invalid character " + std::string(1, c));

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

std::vector<char> Game::guesses()
{
    std::vector<char> checked;
    checked.reserve(alphabet.size());

    for (std::size_t i = 0; i < alphabet.size(); i++)
        if (alphabet_guessed[i])
            checked.push_back(alphabet[i]);

    return checked;
}

std::string Game::guessed(char unkown)
{
    for (std::size_t i = 0; i < alphabet.size(); i++)
        if (alphabet[i] == unkown)
            throw std::runtime_error("Unable to generate guessed if '" + std::string(1, unkown) + "' is in the alphabet");

    std::string hidden(solution);

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

std::string_view Game::give_up()
{
    return solution;
}

bool validate_word(const std::string &word, const std::string &alphabet, std::size_t *err_pos)
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

std::vector<std::string> loadLexicon(std::string lexiconPath)
{
    std::ifstream file(lexiconPath);
    std::vector<std::string> lexicon;

    if (!file.is_open())
        throw std::runtime_error("Error opening file: " + lexiconPath);

    std::string word;

    while (!file.eof())
    {
        file >> word;
        lexicon.emplace_back(word);
    }

    return lexicon;
}


#include "Game.h"
#include <fstream>
#include <algorithm>

Game::Game(const std::vector<std::string> &lexicon) : total_guess(0),
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
    bool valid = false;
    for (std::size_t i = 0; i < alphabet.size(); i++)
        if (alphabet[i] == c)
        {
            alphabet_guessed[i] = true;
            valid = true;
        }

    if (!valid)
        throw std::runtime_error("Invalid character " + std::string(1, c));

    total_guess++;
    for (std::size_t i = 0; i < solution.size(); i++)
        if (solution[i] == c)
            return true;

    return false;
}

int Game::get_total_guess()
{
    return total_guess;
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

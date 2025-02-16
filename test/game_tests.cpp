
#include <vector>
#include "ctest.h"
#include "Game.h"

#define C_STR(char) std::string(1, (char)).c_str()

std::vector<std::string> lexicon{"WORD", "HOME", "ATOM"};

CTEST(Game, constructor)
{
    Game g(lexicon);

    ASSERT_EQUAL(0, g.get_total_guess());
    ASSERT_TRUE(g.guesses().empty());
}

CTEST(Game, no_char)
{
    Game g(lexicon);

    try
    {
        g.guess('?');
        ASSERT_FAIL();
    }
    catch (const std::runtime_error &e)
    {
        return;
    }

    ASSERT_FAIL();
}

CTEST(Game, guess)
{
    Game g(lexicon);

    g.guess(ALPHABET[0]);

    ASSERT_EQUAL(1, g.get_total_guess());
    ASSERT_STR(C_STR(ALPHABET[0]), C_STR(g.guesses()[0]));
}

CTEST(Game, guessed)
{
    std::string solution = "HOT";
    std::vector test_dict{solution};
    Game g(test_dict);

    ASSERT_EQUAL(solution.size(), g.guessed().size());

    ASSERT_TRUE(g.guess(solution[0]));

    ASSERT_STR(C_STR(solution[0]), C_STR(g.guessed()[0]));

    for (std::size_t i = 1; i < solution.size(); i++)
    {
        ASSERT_NOT_STR(C_STR(solution[i]), C_STR(g.guessed()[i]));
    }
}

CTEST(Game, repeated_guessed)
{
    std::string solution = "HOTTER";
    std::vector test_dict{solution};
    Game g(test_dict);

    ASSERT_EQUAL(solution.size(), g.guessed().size());
    ASSERT_STR("......", g.guessed('.').c_str());

    ASSERT_TRUE(g.guess('T'));

    ASSERT_STR("..TT..", g.guessed('.').c_str());
}

CTEST(Game, validate_all_dicts)
{
    std::vector<std::string> paths{"words_alpha_xl.txt", "words_alpha_xs.txt"};

    for (const std::string &path : paths)
    {
        std::vector<std::string> lex = loadLexicon("../lexicons/" + path);

        for (const std::string &word : lex)
            if (!validate_word(word, ALPHABET, nullptr))
                CTEST_ERR("File %s does not follow alphabet '%s' in word %s", path.c_str(), ALPHABET, word.c_str());
    }
}

CTEST(Game, validate_word)
{
    // Invalid string
    std::string word = "****";
    std::size_t err_pos = 99;
    bool valid = validate_word(word, ALPHABET, &err_pos);

    ASSERT_FALSE(valid);
    ASSERT_EQUAL(0, err_pos);

    // Valid string
    word = std::string(ALPHABET).substr(0, 5);
    err_pos = 99;
    valid = validate_word(word, ALPHABET, &err_pos);

    ASSERT_TRUE(valid);
    ASSERT_EQUAL(99, err_pos);

    // Invalid string but no err_pos
    word = "****";
    valid = validate_word(word, ALPHABET, nullptr);

    ASSERT_FALSE(valid);

    // Only last char is invalid
    word = std::string(ALPHABET) + "****";
    err_pos = 0;
    valid = validate_word(word, ALPHABET, &err_pos);

    ASSERT_FALSE(valid);
    ASSERT_EQUAL(std::string(ALPHABET).size(), err_pos);
}
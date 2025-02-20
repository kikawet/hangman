
#include <vector>
#include "test_common.h"
#include "Game.h"

std::vector<std::u32string> game_lexicon{U"WORD", U"HOME", U"ATOM"};

CTEST(Game, constructor)
{
    Game g(game_lexicon);

    ASSERT_EQUAL(0, g.get_failed_count());
    ASSERT_TRUE(g.guesses().empty());
}

CTEST(Game, no_char)
{
    Game g(game_lexicon);

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
    std::vector test_dict{game_lexicon[0]};
    Game g(test_dict);

    g.guess(ALPHABET[0]);

    ASSERT_EQUAL(1, g.get_failed_count());
    ASSERT_CHAR(ALPHABET[0], g.guesses()[0]);
}

CTEST(Game, guessed)
{
    std::u32string solution = U"HOT";
    std::vector test_dict{solution};
    Game g(test_dict);

    ASSERT_EQUAL(solution.size(), g.guessed().size());

    ASSERT_FALSE(g.guess(solution[0]));

    ASSERT_CHAR(solution[0], g.guessed()[0]);

    for (std::size_t i = 1; i < solution.size(); i++)
    {
        ASSERT_NOT_CHAR(solution[i], g.guessed()[i]);
    }
}

CTEST(Game, repeated_guessed)
{
    std::u32string solution = U"HOTTER";
    std::vector test_dict{solution};
    Game g(test_dict);

    ASSERT_EQUAL(solution.size(), g.guessed().size());
    ASSERT_U32STR(U"......", g.guessed('.'));

    ASSERT_FALSE(g.guess('T'));

    ASSERT_U32STR(U"..TT..", g.guessed('.'));

    ASSERT_FALSE(g.guess('T'));

    ASSERT_U32STR(U"..TT..", g.guessed('.'));
}

CTEST(Game, solve)
{
    std::u32string solution = U"HOTTOH";
    std::vector test_dict{solution};
    Game g(test_dict);

    ASSERT_EQUAL(solution.size(), g.guessed().size());
    ASSERT_U32STR(U"......", g.guessed('.'));

    ASSERT_FALSE(g.guess('T'));
    ASSERT_U32STR(U"..TT..", g.guessed('.'));

    ASSERT_FALSE(g.guess('O'));
    ASSERT_U32STR(U".OTTO.", g.guessed('.'));

    ASSERT_TRUE(g.guess('H'));
    ASSERT_U32STR(U"HOTTOH", g.guessed('.'));
}

CTEST(Game, validate_all_dicts)
{
    std::vector<std::string> paths{"words_en_xl.txt", "words_en_xs.txt", "words_es_xl.txt", "words_es_xs.txt"};

    for (const std::string &path : paths)
    {
        std::vector<std::u32string> lex = loadLexicon("../lexicons/" + path);

        for (const std::u32string &word : lex)
            if (!validate_word(word, ALPHABET, nullptr))
                CTEST_ERR("File %s does not follow alphabet '%s' in word %s", path.c_str(), TO_STR(ALPHABET).c_str(), TO_STR(word).c_str());
    }
}

CTEST(Game, validate_word)
{
    // Invalid string
    std::u32string word = U"****";
    std::size_t err_pos = 99;
    bool valid = validate_word(word, ALPHABET, &err_pos);

    ASSERT_FALSE(valid);
    ASSERT_EQUAL(0, err_pos);

    // Valid string
    word = std::u32string(ALPHABET).substr(0, 5);
    err_pos = 99;
    valid = validate_word(word, ALPHABET, &err_pos);

    ASSERT_TRUE(valid);
    ASSERT_EQUAL(99, err_pos);

    // Invalid string but no err_pos
    word = U"****";
    valid = validate_word(word, ALPHABET, nullptr);

    ASSERT_FALSE(valid);

    // Only last char is invalid
    word = std::u32string(ALPHABET) + U"****";
    err_pos = 0;
    valid = validate_word(word, ALPHABET, &err_pos);

    ASSERT_FALSE(valid);
    ASSERT_EQUAL(std::u32string(ALPHABET).size(), err_pos);
}